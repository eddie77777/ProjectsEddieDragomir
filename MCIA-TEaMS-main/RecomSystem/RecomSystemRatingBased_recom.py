import heapq
import tensorflow
import numpy as np
import random
hasToLog=False

def recommend_movies(user_id, batch_size, num_movie_recom):
    tensorflow.keras.backend.clear_session()
    if hasToLog: print('cleared session')

    # get model
    # TODO: send path as argument
    if hasToLog: print('loading')
    model = tensorflow.keras.models.load_model('../../../../RecomSystem/saved_model/train600')
    if hasToLog: print('loaded. compiling')
    model.compile(optimizer='adam', loss='mean_absolute_error', metrics=['mean_absolute_percentage_error'])
    if hasToLog: print('loaded')
    # the pool of movies from which we recommend
    # TODO: select random movies from available pool
    batch_movies = random.sample(range(0,1000), batch_size)

    map_item_scores = {}
    # users needed for predictions
    users = np.full(batch_size, user_id, dtype='int32')
    predictions = model.predict([users, np.array(batch_movies)], verbose=0)
    if hasToLog: print('clearing session')
    if hasToLog: print('cleared session')
    for x in range(batch_size):
        map_item_scores[batch_movies[x]] = predictions[x]
    ranklist = heapq.nlargest(num_movie_recom, map_item_scores, map_item_scores.get)
    return ranklist


def dummy_return_function(a):
    model = tensorflow.keras.models.load_model('../../../../RecomSystem/saved_model/first_train')
    return [a, a, a]


# function to test import in c++
def test_import_functio():
    print('yay here:)')


if __name__ == '__main__':
    # only for recom
    recommend_movies(1, 1, 2)
