import NeuralNetwork
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
import data_import

def return_user_embedding(id_user=0, path_for_model='first_train1'):
    user_model = NeuralNetwork.get_user_submodule(path_for_model)
    return user_model.predict([id_user]).reshape(1, -1)[0]


class Recom:
    def __init__(self, path_for_model='first_train1'):
        print('init:')
        self.clf = KNeighborsClassifier(n_neighbors=11)
        self.MOVIE_EMBEDDING_LIST = []
        self.movie_embedd_model = NeuralNetwork.get_movie_submodule(path_for_model)
        num_movies = 10  # 27278
        for _id in range(num_movies):  # TODO: REMOVE MAGIC NUMBER
            emb = self.movie_embedd_model.predict(np.array([_id]))
            val = list(emb.reshape(1, -1))[0]
            self.MOVIE_EMBEDDING_LIST.insert(_id, val)

        self.clf.fit(self.MOVIE_EMBEDDING_LIST, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9])  # Use UniqueMovieId

        # self.clf.fit([[0, 0], [0, 1], [1, 0], [1, 1]], [0, 1, 2, 3])

    def __recommend_movies(self, embedding):
        distances, indices = self.clf.kneighbors(embedding.reshape(1, -1), n_neighbors=10)
        indices = indices.reshape(10, 1)
        # df_indices = pd.DataFrame(indices, columns=['movie_id'])
        return indices

    def recommend_movies_for_user_id(self, id):
        embedd = return_user_embedding(id)
        print(embedd)
        return self.__recommend_movies(embedd)


rec = Recom()
ids = rec.recommend_movies_for_user_id(1)
print(ids)