select movies.title from stars
Inner join movies On movies.id = stars.movie_id
Inner join ratings On ratings.movie_id = movies.id
Inner join people On people.id = stars.person_id
Where people.name Like 'Chadwick Boseman'
Order By ratings.rating desc
Limit 5;