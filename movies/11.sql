SELECT movies.title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id AND people.name = "Chadwick Boseman"
JOIN ratings ON ratings.movie_id = stars.movie_id
ORDER BY ratings.rating DESC
LIMIT 5;