SELECT title
FROM movies
JOIN ratings
ON id = ratings.movie_id
WHERE id IN (
    SELECT movie_id FROM stars
    JOIN people ON person_id = people.id
    WHERE name = 'Chadwick Boseman'

)
ORDER BY ratings.rating DESC
LIMIT 5
;