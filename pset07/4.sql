select count(1) from movies join ratings on movies.id = ratings.movie_id where ratings.rating = 10
