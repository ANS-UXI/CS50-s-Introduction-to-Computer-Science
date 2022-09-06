SELECT AVG(ratings.rating) FROM ratings
INNER JOIN movies ON movies.id = ratings.movie_id AND year = 2012;