select m.title
from people depp
  join stars depps on depps.person_id = depp.id
  join movies m on depps.movie_id = m.id
  join stars bonhams on bonhams.movie_id = m.id
  join people bonham on bonham.id = bonhams.person_id
where depp.name = 'Johnny Depp' and bonham.name = 'Helena Bonham Carter'
