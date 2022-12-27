SELECT title, rating FROM movies JOIN ratings ON id = movie_id WHERE year IN (SELECT year FROM movies WHERE year = 2010 ORDER BY title) ORDER BY rating DESC, title ASC;
