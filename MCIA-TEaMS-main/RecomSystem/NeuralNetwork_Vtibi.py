from tensorflow.keras import layers
import tensorflow as tf

from tensorflow.keras.layers import Input, Embedding, Dot, Dense, Reshape, Concatenate
from tensorflow.keras import Model, utils

class NeuralNetwork:
    def __init__(self, input_max1, embedding_size, input_max2, name1, name2, denselayers_number=1,
                 denselayers_units=[20]):
        if denselayers_units is None:
            denselayers_units = []
        self.input_max1 = input_max1
        self.embedding_size1 = embedding_size
        self.input_max2 = input_max2
        self.name1 = name1
        self.name2 = name2
        self.denselayers_number = denselayers_number
        self.denselayers_units = denselayers_units
        self.member1_input = Input(name="input_" + self.name1, shape=(1,))
        self.member2_input = Input(name="input_" + self.name2, shape=(1,))

    def __embedding(self, the_input, input_max, name):
        the_imbedding = Embedding(name="embd_" + name, input_dim=input_max, output_dim=self.embedding_size1)(the_input)
        the_reshape = Reshape(name='reshape_' + name, target_shape=((self.embedding_size1,)))(the_imbedding)
        return the_reshape

    def __embedding_Matrix(self):
        first_result = self.__embedding(self.member1_input, self.input_max1, self.name1)
        second_result = self.__embedding(self.member2_input, self.input_max2, self.name2)

        sim = Dot(name='dot', normalize=True, axes=1)([first_result, second_result])
        y_out = layers.Dense(name="y_out", units=1, activation='linear')(sim)
        return y_out

    def __embedding_Neural(self):
        first_result = self.__embedding(self.member1_input, self.input_max1, self.name1 + "1")
        second_result = self.__embedding(self.member2_input, self.input_max2, self.name2 + "1")

        dens = Concatenate(name='concat')([first_result, second_result])
        for nmb_layer in range(self.denselayers_number):
            dens = Dense(name='dense' + str(nmb_layer), units=self.denselayers_units[nmb_layer], activation='relu')(
                dens)
        return dens

    def get_mode_with_neural_filtering(self):
        result1 = self.__embedding_Matrix()
        result2 = self.__embedding_Neural()
        conc = Concatenate(name='concat2')([result1, result2])
        y_out = Dense(name='rating', units=1, activation='linear')(conc)
        model = Model(inputs=[self.member1_input, self.member2_input], outputs=y_out, name="NCF")
        return model

#
# model = NeuralNetwork(input_max1=50, embedding_size=50, input_max2=50, name1="users", name2="movie")\
#     .get_mode_with_neural_filtering()
# model.summary()
# utils.plot_model(model, to_file='model2.png', show_shapes=True, show_layer_names=True)
