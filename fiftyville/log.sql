-- Keep a log of any SQL queries you execute as you solve the mystery.

-- (1) Know the database and its table definiton
.schema

-- (2) Query to see whats in the table crime_scene_reports
SELECT * FROM crime_scene_reports;

-- (3) Query to see what happened at Humphrey Street on 28th July
SELECT description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- (4) Query to read the interview transcripts
SELECT * FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- (5) Query to see license plate of cars that left the pakring lot
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28;

-- Theft of the CS50 duck took place at 10:15am

--| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
    -- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
    -- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
    -- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
    -- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
    -- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
    -- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
    -- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
    -- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |

--| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's
--bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

    -- +---------+
    -- |  name   |
    -- +---------+
    -- | Bruce   | (S)
    -- | Diana   | (S)
    -- +---------+

--| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person
--on the other end of the phone to purchase the flight ticket. |

    -- +-----+----------------+----------------+------+-------+-----+----------+
    -- | id  |     caller     |    receiver    | year | month | day | duration |
    -- +-----+----------------+----------------+------+-------+-----+----------+
    -- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       | (Bruce)
    -- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       | (Diana)
    -- +-----+----------------+----------------+------+-------+-----+----------+

-- (6) Query to find out the names of the suspects
SELECT name, license_plate FROM people
WHERE license_plate in ("5P2BI95","94KL13X","6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

-- SUS = ("Iman", "Sofia", "Diana", "Kelsey", "Vanessa", "Barry", "Luca", "Bruce")

-- (7) Query to see transaction history of the atm located at Leggett Street
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";

-- (8) Query to names of the suspects through bank accounts
SELECT people.name FROM people
JOIN atm_transactions ON atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street"
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number AND bank_accounts.person_id = people.id;

-- (9) Query to see who talked for less than 1 minute
SELECT * FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- (10) Query to see which flights are available on 29/7/21
SELECT * FROM flights
WHERE year = 2021 AND month = 7 AND day = 29;

-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
-- | 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | (THIS PLANE)
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
-- | 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- (11) Query to passport number of Bruce and Diana
SELECT name, passport_number FROM people
WHERE name in ("Bruce", "Diana");

-- +-------+-----------------+
-- | name  | passport_number |
-- +-------+-----------------+
-- | Diana | 3592750733      |
-- | Bruce | 5773159633      | (Thief) Travelling to NYC
-- +-------+-----------------+

-- (12) Query to check who is travelling the earliest on 29th
SELECT * FROM passengers
WHERE passport_number IN (3592750733, 5773159633);

-- (13) Query to one who helped the Bruce (Robin)
SELECT name FROM people
WHERE phone_number = "(375) 555-8161";