SELECT people.name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.title = "Toy Story" AND movies.id = stars.movie_id;