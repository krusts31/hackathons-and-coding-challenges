import os
import pathlib
import pandas as pd

current_dir = pathlib.Path(__file__).parent.resolve()

NEW_FOLDER_path = os.path.join(current_dir, 'neo_data')

DATASET_PATH = os.path.join(current_dir, 'data', 'train')

CSV = pd.read_csv(os.path.join(DATASET_PATH, "images.csv"))

pathlib.Path(NEW_FOLDER_path).mkdir(exist_ok=True)
for x in CSV.label.unique():
	if os.path.exists(os.path.join(NEW_FOLDER_path, x)):
		os.remove(os.path.join(NEW_FOLDER_path, x))
	pathlib.Path(os.path.join(NEW_FOLDER_path, x)).mkdir()
