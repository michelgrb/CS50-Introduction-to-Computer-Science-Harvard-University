select avg(rating) from ratings
Inner join movies On movies.id = ratings.movie_id
Where movies.year = 2012;