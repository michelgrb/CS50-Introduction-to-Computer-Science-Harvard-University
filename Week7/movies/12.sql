select movies.title from movies
Left join stars On stars.movie_id = movies.id
Inner join people On people.id = stars.person_id
where people.name = 'Johnny Depp' or people.name = 'Helena Bonham Carter'
Group By movies.title
Having count(people.name) > 1