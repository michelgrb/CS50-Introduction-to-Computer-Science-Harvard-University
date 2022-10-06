select people.name from people
inner join stars On stars.person_id = people.id
Inner join movies On movies.id = stars.movie_id
where movies.title IN (select movies.title from stars Left join movies On movies.id = stars.movie_id Inner join people On people.id = stars.person_id Where people.name = 'Kevin Bacon' Group By movies.title)
Group By people.name
Having not people.name = 'Kevin Bacon';



