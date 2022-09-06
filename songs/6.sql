SELECT songs.name FROM songs
INNER JOIN artists ON songs.artist_id = artists.id AND artists.name = "Post Malone";