import csv


def train_for_user(userId, movieId, rating):
    userId += 500  # first 500 users are our "base" value
    with open('../../../../RecomSystem/data/new_data.csv', 'a', newline='') as fd:
        writer = csv.writer(fd)
        writer.writerow([userId, movieId, round(rating, 1)])
    return 1


if __name__ == '__main__':
    a = 'dummy'
    # retrain_last_values()
