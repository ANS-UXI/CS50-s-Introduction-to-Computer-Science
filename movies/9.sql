SELECT DISTINCT people.name FROM people
JOIN movies ON movies.year = 2004
JOIN stars ON movies.id = stars.movie_id AND stars.person_id = people.id
ORDER BY people.birth;