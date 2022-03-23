import lib_for_ml as my_lib
import tensorflow as tf
import pathlib
import os

train_dataset = my_lib.creat_data_sets_t()
valid_dataset = my_lib.creat_data_sets_v()

model = my_lib.new_model()

model.compile(optimizer='adam',
	loss=tf.keras.losses.CategoricalCrossentropy(from_logits=True),
	metrics=['accuracy'])

model.build(input_shape=(None, 32, 32, 3))

print(model.summary())

model.fit(train_dataset,
	epochs = 1,
	steps_per_epoch = 1,
	validation_data = valid_dataset)

current_dir = pathlib.Path(__file__).parent.resolve()

model.save_weights(os.path.join(current_dir, 'checkpoints', 'my_checkpoint'))
model.save(os.path.join(current_dir, "plankthon-model"))
