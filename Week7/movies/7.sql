select movies.title, ratings.rating from ratings
Inner join movies On movies.id = ratings.movie_id
Where movies.year = 2010
Order By ratings.rating DESC, movies.title asc
Limit 10;