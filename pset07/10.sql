select distinct p.name
from people p
  join directors s on s.person_id = p.id
  join movies m on s.movie_id = m.id
  join ratings r on r.movie_id = m.id
where r.rating >= 9
