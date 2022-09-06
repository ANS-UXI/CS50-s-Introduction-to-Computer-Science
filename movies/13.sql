SELECT people.name FROM people
JOIN stars ON stars.person_id = people.id AND stars.movie_id IN (SELECT movies.id FROM movies
                                                                JOIN stars ON stars.movie_id = movies.id
                                                                JOIN people ON people.id = stars.person_id AND people.name = "Kevin Bacon" AND people.birth = 1958)
WHERE people.name <> "Kevin Bacon";