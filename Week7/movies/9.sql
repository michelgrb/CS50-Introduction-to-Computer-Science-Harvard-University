select people.name from stars
Inner join movies On movies.id = stars.movie_id
Inner join people On people.id = stars.person_id
Where movies.year = 2004
Order By people.birth asc