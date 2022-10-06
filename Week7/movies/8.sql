select people.name from stars
Inner join movies On movies.id = stars.movie_id
Inner join people On people.id = stars.person_id
Where movies.title Like 'Toy Story'