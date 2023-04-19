import pandas as pd
import re
import numpy as np
from datetime import datetime
## for plotting
import matplotlib.pyplot as plt
import seaborn as sns
## for machine learning
from sklearn import preprocessing, metrics


def get_data():
    movies = pd.read_excel('data/movie_e.xlsx')
    UNIQUE_MOVIE_IDS = movies['movie_id'].unique()
    return UNIQUE_MOVIE_IDS

def test_function():
    print('Hi from data_import!')