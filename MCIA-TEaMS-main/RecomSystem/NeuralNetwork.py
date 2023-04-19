from tensorflow.keras import layers
import tensorflow as tf

from tensorflow.keras.layers import Input, Embedding, Dot, Dense, Reshape, Concatenate
from tensorflow.keras import Model, utils

def retrieve_model(path):
    return tf.keras.models.load_model('saved_model/first_train')


def get_user_submodule(model_path):
    full_model = retrieve_model('model_path')
    user_model = Model(inputs=full_model.get_layer('user_inp').input,
                       outputs=full_model.get_layer('reshape_usr').output)
    return user_model


def get_movie_submodule(model_path):
    full_model = retrieve_model('model_path')
    movie_model = Model(inputs=full_model.get_layer('movie_inp').input,
                        outputs=full_model.get_layer('reshape_movie').output)
    return movie_model


class NeuralNetwork:
    def __init__(self, input_max1, embedding_size, input_max2, name1, name2, denselayers_number=1,
                 denselayers_units=[20]):
        self.model = None
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

    def train_model(self, train):
        self.model = self.get_mode_with_neural_filtering()
        self.model.compile(optimizer='adam', loss='mean_absolute_error', metrics=['mean_absolute_percentage_error'])
        # Train
        training = self.model.fit(x=[train["user"], train["entry_id"]], y=train["y"], epochs=100, batch_size=128,
                                  shuffle=True, verbose=1, validation_split=0.3)

    def save_weights(self, path_to_weights='model_weights'):
        self.model.save_weights('./checkpoints/' + path_to_weights)

    def load_weights(self, path_to_weights='model_weights'):
        self.model.load_weights('./checkpoints/' + path_to_weights)
