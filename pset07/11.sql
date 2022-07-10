select m.title
from people p
  join stars s on s.person_id = p.id
  join movies m on s.movie_id = m.id
  join ratings r on r.movie_id = m.id
where p.name = 'Chadwick Boseman'
order by r.rating desc limit 5
