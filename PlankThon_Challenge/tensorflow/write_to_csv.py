from tensorflow import keras
import lib_for_ml as my_lib 
import tensorflow as tf 
import pandas as pd
import numpy as np
import pathlib
import os

current_dir = pathlib.Path('.').parent.resolve()

model = my_lib.new_model()

model.load_weights(os.path.join(current_dir, 'checkpoints', 'my_checkpoint'))

path_2 = os.path.join(current_dir, 'data', 'test', 'images')

test_csv_path = os.path.join(current_dir, 'data', 'test')

CSV_test = pd.read_csv(os.path.join(test_csv_path, "images.csv"))

CSV_PATH = os.path.join(current_dir, 'data', 'train')

CSV_train = pd.read_csv(os.path.join(CSV_PATH, "images.csv"))

pathlib.Path(os.path.join(current_dir, 'score')).mkdir(exist_ok=True)

header = CSV_train.label.unique()


df = pd.DataFrame(columns=['image', *header])

i = 0

for imgs in CSV_test.image:
	print("number for test: ", i)

	imgz = keras.preprocessing.image.load_img(
		os.path.join(path_2, str(imgs)), target_size=(32, 32)
	)

	img_array = keras.preprocessing.image.img_to_array(imgz)
	img_array = tf.expand_dims(img_array, 0)
	predictions = model.predict(img_array)
	res = np.divide(predictions, 100)
	row = ""
	for num in res:
		df = df.append({'image': imgs, **{header[i]: num[i] for i in range(len(header))}}, ignore_index=True)
	i = i + 1

df.to_csv(os.path.join(current_dir, 'score', 'result.csv'), sep=',', index=False)
