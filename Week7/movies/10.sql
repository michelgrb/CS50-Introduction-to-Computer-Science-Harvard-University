select people.name from directors
Inner join movies On movies.id = directors.movie_id
Inner join ratings On ratings.movie_id = movies.id
Inner join people On people.id = directors.person_id
Where ratings.rating >= 9.0
