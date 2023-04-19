import csv
import tensorflow
from tensorflow.python.keras.models import model_from_json
from datetime import datetime
import numpy as np
hasToLog = False


def retrain_last_values():
    tensorflow.keras.backend.clear_session()
    if hasToLog:
        print('\n\n\nIMPORTING MODEL FOR RETRAIN MODEL==================')
    model = tensorflow.keras.models.load_model('../../../../RecomSystem/saved_model/train600')

    if hasToLog:
        print("Loaded model from disk")
    model.compile(optimizer='adam', loss='mean_absolute_error', metrics=['mean_absolute_percentage_error'])
    train_file = open('../../../../RecomSystem/data/new_data.csv')
    csvreader = csv.reader(train_file)
    userIds = []
    movieIds = []
    ratings = []
    header = next(csvreader)
    for row in csvreader:
        userIds.append(int(row[0]))
        movieIds.append(int(row[1]))
        ratings.append(float(row[2]))
    train_file.close()

    # reset data
    with open('../../../../RecomSystem/data/new_data.csv', 'w+', newline='') as fd:
        writer = csv.writer(fd)
        writer.writerow(['userId', 'movieId', 'rating'])

    # with open('../../../../RecomSystem/logs/train_logs.txt', 'a') as file:
    #     file.write('Loading model started %s.' % datetime.now())
    with open('../../../../RecomSystem/logs/train_logs.txt', 'a') as file:
        file.write('Train started %s' % datetime.now())
    if hasToLog: print('TRAIN STARTED:')
    model.fit(x=(np.array(userIds), np.array(movieIds)), y=np.array(ratings), verbose=0)
    if hasToLog: print('trained complete model. start saving')
    model.save('../../../../RecomSystem/saved_model/train600')

    if hasToLog: print('model saved. saving in logs')

    with open('../../../../RecomSystem/logs/train_logs.txt', 'a') as file:
        file.write(' and ended %s\n' % datetime.now())
    tensorflow.keras.backend.clear_session()
    return 1


retrain_last_values()