select p.name
from people p
  join stars s on s.person_id = p.id
  join stars kevins on s.movie_id = kevins.movie_id
  join people kevin on kevin.id = kevins.person_id
where kevin.id <> p.id and kevin.name = 'Kevin Bacon' and kevin.birth = 1958
