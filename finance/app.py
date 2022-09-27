import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]

    # User's information
    user_info = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])

    # Current Shares holding by the user
    info = db.execute("SELECT symbol, SUM(shares) AS shares FROM purchases WHERE username=? GROUP BY symbol", user)

    sum = 0
    for i in info:
        x = lookup(i["symbol"])
        i["name"] = x["name"]
        i["current_price"] = x["price"]
        i["total"] = float(i["shares"]) * float(x["price"])
        sum = sum + float(i["total"])
    sum = sum + float(user_info[0]["cash"])
    return render_template("index.html", info=info, user_info=user_info, sum=sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # Ensure whether a post or get request
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stocks symbol", 400)

        # Ensure symbol is valid
        elif not lookup(request.form.get("symbol")):
            return apology("not a valid stocks symbol", 400)

        symbol = request.form.get("symbol").upper().strip()
        shares = request.form.get("shares", type=int)

        # Ensure shares is provided
        if shares == None:
            return apology("must provide shares", 400)

        # Ensure shares is a positive integer
        elif int(shares) < 1:
            return apology("must provide valid shares", 400)
        info_shares = lookup(symbol)

        # Calculate net worth the user holds
        total_price = float(shares) * float(info_shares["price"])

        # Get user's session id
        user = session["user_id"]

        user_cash = db.execute("SELECT cash FROM users WHERE id=?", user)
        cash_left = user_cash[0]["cash"] - total_price

        # Ensure user have enough cash
        if total_price > user_cash[0]["cash"]:
            apology("you don't have enough cash", 400)

        # Get current date and time of purchase
        now = datetime.now()
        date_time = now.strftime("%d/%m/%Y %H:%M:%S")

        # Keep a log of purchases
        db.execute("INSERT INTO purchases VALUES (?, ?, ?, ?, ?, ?)", db.execute("SELECT username FROM users WHERE id=?", user)[0]["username"], symbol, shares, info_shares["price"], total_price, date_time)

        # Cash left after purchase
        cash_left = user_cash[0]["cash"] - total_price

        db.execute("UPDATE users SET cash=? WHERE username=?", cash_left, db.execute("SELECT username FROM users WHERE id=?", user)[0]["username"])
        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get username
    user = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]

    # Get user's history of purchases
    info = db.execute("SELECT * FROM purchases WHERE username=?", user)

    return render_template("history.html", info=info)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Ensure whether a post or get method
    if request.method == "POST":

        # Ensure symbol is provided
        if not request.form.get("symbol"):
            return apology("must provide stocks symbol", 400)

        # Ensure symbol is valid
        info = lookup(request.form.get("symbol").upper())
        if info == None:
            return apology("stock not found", 400)

        return render_template("quoted.html", info=info)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # Ensure it's a post request
    if request.method == "POST":

        # Ensure username not blank
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure username is distinct
        elif db.execute("SELECT * FROM users WHERE username=?",request.form.get("username")):
            return apology("username already exists", 400)

        # Ensure password not blank
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must re-enter password", 400)

        # Ensure both passwords are the same
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords dont match", 400)

        # Generate a hash equivalent to password
        hash = generate_password_hash(request.form.get("password"))

        # Insert new user to users in the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), hash)

        # Log User In
        row = db.execute("SELECT * FROM users WHERE username=?",request.form.get("username"))
        session["user_id"] = row[0]["id"]
    else:
        return render_template("register.html")
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Ensure whether a post or get request
    if request.method == "POST":

        # Ensure share is provided
        if not request.form.get("shares"):
            return apology("must provide shares", 400)

        # Ensure symbol is provided
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        info_shares = lookup(symbol)

        # Get shares a user holds
        user_shares = db.execute("SELECT SUM(shares) AS shares FROM purchases WHERE username=? AND symbol=?", db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"], symbol)

        # Check whether the user have enough shares to sell
        if shares > int(user_shares[0]["shares"]):
            return apology("NOT ENOUGH SHARES", 400)

        # Get current date and time of selling
        now = datetime.now()
        date_time = now.strftime("%d/%m/%Y %H:%M:%S")

        # Get username
        user = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]

        # Keep a log of activity
        db.execute("INSERT INTO purchases VALUES(?, ?, ?, ?, ?, ?)", user, symbol, 0 - int(shares), info_shares["price"], 0 - (int(shares) * info_shares["price"]), date_time)

        # Get current cash the user have
        user_cash = db.execute("SELECT cash FROM users WHERE username=?", user)[0]["cash"]

        # Update users cash
        db.execute("UPDATE users SET cash=? WHERE username=?", user_cash + (int(shares) * info_shares["price"]), user)

        flash("Sold!")
        return redirect("/")
    else:

        # List all shares the user have
        user = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]
        shares = []
        for i in db.execute("SELECT DISTINCT symbol FROM purchases WHERE username=?", user):
            shares.append(i["symbol"])
        return render_template("sell.html", shares=shares)

# Personal Touch


@app.route("/password", methods=["GET", "POST"])
def password():
    """Change password"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure old password was submitted
        if not request.form.get("old_pass"):
            return apology("must old password", 403)

        # Ensure new password was submitted
        elif not request.form.get("new_pass"):
            return apology("must provide new password", 403)
        elif not request.form.get("re-new_pass"):
            return apology("must retype new password", 403)
        elif not request.form.get("new_pass") == request.form.get("re-new_pass"):
            return apology("two passwords must match", 403)

         # Generate a hash equivalent to password
        hash = generate_password_hash(request.form.get("old_pass"))
        old = db.execute("SELECT hash FROM users WHERE id=?", session["user_id"])

        if not check_password_hash(old[0]["hash"], request.form.get("old_pass")):
            return apology("wrong exisiting password", 403)

        db.execute("UPDATE users SET hash=? WHERE id=?", generate_password_hash(request.form.get("new_pass")), session["user_id"])

        return render_template("change_pass.html", flag=True)
    else:
        return render_template("change_pass.html", flag=False)