SELECT title
FROM movies
JOIN stars
ON movies.id = stars.movie_id
WHERE stars.person_id IN (
    SELECT people.id
    FROM people
    WHERE name = 'Helena Bonham Carter')
INTERSECT
SELECT title
FROM movies
JOIN stars
ON movies.id = stars.movie_id
WHERE stars.person_id IN (
    SELECT people.id
    FROM people
    WHERE name = 'Johnny Depp')