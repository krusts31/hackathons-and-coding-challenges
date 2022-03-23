from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras import layers
import pathlib
import os

path = pathlib.Path(__file__).parent.resolve()

path = os.path.join(path, 'neo_data')

def creat_data_sets_t():
	train = ImageDataGenerator(rescale = 1./ 255, validation_split=0.2)
	train_dataset = train.flow_from_directory(path,
						target_size = (32, 32),
						batch_size = 32,
						color_mode = 'rgb',
						class_mode = 'categorical',
						subset='training')

	return train_dataset

def creat_data_sets_v():
	validation = ImageDataGenerator(rescale = 1./ 255, validation_split=0.2)
	valid_dataset = validation.flow_from_directory(path,
						target_size = (32, 32),
						color_mode = 'rgb',
						batch_size = 32,
						class_mode = 'categorical',
						subset='validation')
	return valid_dataset

def new_model():
	"""
	Last layer has to be same length as class cnt == 84
	YOU can change the rest layers to waht you deam
	"""
	model = Sequential([
		layers.Conv2D(16, 3, padding='same', activation='relu'),
		layers.MaxPooling2D(),
		layers.Conv2D(32, 3, padding='same', activation='relu'),
		layers.MaxPooling2D(),
		layers.Conv2D(64, 3, padding='same', activation='relu'),
		layers.MaxPooling2D(),
		layers.Flatten(),
#		layers.Dense(128, activation='relu'),
		layers.Dense(84)
	])
	return model
