SELECT DISTINCT name FROM people JOIN stars ON person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE movie_id = (SELECT id FROM movies WHERE title = 'Toy Story');