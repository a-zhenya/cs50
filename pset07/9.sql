select distinct p.name
from people p
  join stars s on s.person_id = p.id
  join movies m on s.movie_id = m.id
where m.year = 2004 order by p.birth asc
