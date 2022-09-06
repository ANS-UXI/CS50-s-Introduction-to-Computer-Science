# TODO
from cs50 import get_string
text = get_string("Text: ")
d = {"letters": 0, "words": 1, "sentences": 0}
sen = [".", "!", "?"]
for i in text:
    if i.isalpha():
        d["letters"] += 1
    elif i == " ":
        d["words"] += 1
    elif i in sen:
        d["sentences"] += 1
# Average number of letters per 100 words
L = (d["letters"] / float(d["words"])) * 100.0
# Average number of sentences per 100 words
S = (d["sentences"] / float(d["words"])) * 100.0
# Coleman-Liau index
index = round((0.0588 * L) - (0.296 * S) - 15.8)
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade ", index)