import os
import pathlib
import pandas as pd

current_dir = pathlib.Path(__file__).parent.resolve()

NEW_FOLDER_path = os.path.join(current_dir, 'neo_data')

DATASET_PATH = os.path.join(current_dir, 'data', 'train')
DATASET_PATH_IMAGES = os.path.join(current_dir, 'data', 'train', 'images')

CSV = pd.read_csv(os.path.join(DATASET_PATH, "images.csv"))

i = 0

for label in CSV.label:
	os.rename(os.path.join(DATASET_PATH_IMAGES, CSV.image[i]), os.path.join(NEW_FOLDER_path, label, CSV.image[i]))
	i = i + 1
