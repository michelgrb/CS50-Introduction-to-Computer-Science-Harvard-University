select avg(energy) From songs
INNER JOIN artists
ON songs.artist_id = artists.id
Where artists.name = 'Post Malone';