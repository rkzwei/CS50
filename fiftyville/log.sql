-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports; -- Read all crime scene reports that occurred

SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 07 AND street = 'Humphrey Street'; -- Specific to Humphrey Street in july

SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 07 AND day = 28 AND hour = 10; -- Get security log from bakery

SELECT * FROM interviews WHERE year = 2021 AND month = 07 AND day = 28 AND transcript LIKE '%bakery%'; -- Get description for more clues

-- Got annoyed with the amount of intersecting data

SELECT * FROM flights WHERE year = 2021 AND month = 07 AND day = 29 ORDER BY hour; -- Get earliest flight ID

SELECT * FROM passengers WHERE flight_id = 36; -- Get details from flight

SELECT DISTINCT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36); -- Shortlist of passengers on earliest flight

SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 07 AND day = 28 AND hour = 10 AND minute < 30 AND minute > 14; -- Precision into bakery logs

SELECT DISTINCT license_plate FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36) -- Intersect previous 2 commands for match on THIEF

INTERSECT

SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 07
AND day = 28
AND hour = 10
AND minute < 30
AND minute > 14;

-- LICENSE PLATE OF THIEF = 0NTHK55, 4328GD8, 94KL13X

SELECT name FROM people WHERE license_plate IN (
    SELECT DISTINCT license_plate FROM people
    WHERE passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36) -- Intersect previous 2 commands for match on THIEF

    INTERSECT

    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND hour = 10
    AND minute < 30
    AND minute > 14); -- Names


SELECT * FROM phone_calls; -- Understand table structure

SELECT DISTINCT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE license_plate IN (
    SELECT DISTINCT license_plate FROM people
    WHERE passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36) -- Intersect previous 2 commands for match on THIEF

    INTERSECT

    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND hour = 10
    AND minute < 30
    AND minute > 14)) AND day = 28 AND duration < 60;-- Shortlist accomplice, Luca eliminated

-- For some reason, a list of PHONE CALLS doesn't list HOURS OR MINUTES, which is rather silly, come on guys.
SELECT * FROM people WHERE phone_number IN (
SELECT caller FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE license_plate IN (
    SELECT DISTINCT license_plate FROM people
    WHERE passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36) -- Intersect previous 2 commands for match on THIEF

    INTERSECT

    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND hour = 10
    AND minute < 30
    AND minute > 14)) AND day = 28 AND duration < 60);  -- Precision names and info

SELECT * FROM bank_accounts JOIN people ON person_id = people.id WHERE people.id IN (
    SELECT id FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE license_plate IN (
    SELECT DISTINCT license_plate FROM people
    WHERE passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36)

    INTERSECT

    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND hour = 10
    AND minute < 30
    AND minute > 14)) AND day = 28 AND duration < 60)
); -- Verify against Bank Info, only 1 has bank account thus only one able to retrieve funds
-- Bruce is thief

SELECT * FROM flights WHERE id IN (SELECT flight_id FROM passengers WHERE passport_number = 5773159633); -- Confirm only one flight out

SELECT * FROM airports WHERE id = 4; -- Check airport name

SELECT city FROM airports WHERE id = 4; -- return city for validation

SELECT DISTINCT * FROM phone_calls WHERE caller = '(367) 555-5533' AND day = 28 AND duration < 60; -- match number for accomplice

SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND day = 28 AND duration < 60); -- find accomplice

--Mistery solved