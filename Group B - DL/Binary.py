# =========================================================
# IMDB Sentiment Classification using Deep Neural Network
# Works in:
# 1. Google Colab
# 2. Jupyter Notebook
# =========================================================

# ================= IMPORT LIBRARIES =================

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import tensorflow as tf

from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from sklearn.model_selection import train_test_split

# ================= LOAD IMDB DATASET =================

# Load only top 10000 frequent words
(X_train, y_train), (X_test, y_test) = imdb.load_data(num_words=10000)

# Combine train and test data
data = np.concatenate((X_train, X_test), axis=0)
labels = np.concatenate((y_train, y_test), axis=0)

# ================= DISPLAY DATASET INFO =================

print("Total Reviews :", len(data))
print("Total Labels  :", len(labels))

print("\nSample Encoded Review:\n")
print(data[0])

print("\nSample Label:")
print(labels[0])

# ================= DECODE REVIEW =================

word_index = imdb.get_word_index()

reverse_word_index = {
    value: key for (key, value) in word_index.items()
}

decoded_review = " ".join(
    [reverse_word_index.get(i - 3, "?") for i in data[0]]
)

print("\nDecoded Review:\n")
print(decoded_review)

# ================= VECTORIZE DATA =================

def vectorize_sequences(sequences, dimension=10000):

    results = np.zeros((len(sequences), dimension))

    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1.0

    return results

# Convert reviews into vectors
data = vectorize_sequences(data)

# Convert labels into float values
labels = np.asarray(labels).astype("float32")

# ================= TRAIN TEST SPLIT =================

X_train, X_test, y_train, y_test = train_test_split(
    data,
    labels,
    test_size=0.20,
    random_state=42
)

print("\nTraining Data Shape :", X_train.shape)
print("Testing Data Shape  :", X_test.shape)

# ================= DATA VISUALIZATION =================

sns.countplot(x=labels)

plt.title("Positive and Negative Reviews")

plt.show()

# ================= BUILD DNN MODEL =================

model = Sequential()

# Input Layer
model.add(
    Dense(
        50,
        activation='relu',
        input_shape=(10000,)
    )
)

# Hidden Layer 1
model.add(Dropout(0.3))

# Hidden Layer 2
model.add(Dense(50, activation='relu'))

# Dropout Layer
model.add(Dropout(0.2))

# Hidden Layer 3
model.add(Dense(50, activation='relu'))

# Output Layer
model.add(Dense(1, activation='sigmoid'))

# ================= MODEL SUMMARY =================

print("\nModel Summary:\n")

model.summary()

# ================= EARLY STOPPING =================

callback = tf.keras.callbacks.EarlyStopping(
    monitor='val_loss',
    patience=3,
    restore_best_weights=True
)

# ================= COMPILE MODEL =================

model.compile(
    optimizer='adam',
    loss='binary_crossentropy',
    metrics=['accuracy']
)

# ================= TRAIN MODEL =================

print("\nTraining Started...\n")

history = model.fit(
    X_train,
    y_train,
    epochs=2,
    batch_size=500,
    validation_data=(X_test, y_test),
    callbacks=[callback],
    verbose=1
)

# ================= CHECK HISTORY =================

print("\nHistory Keys:\n")

print(history.history.keys())

# ================= EVALUATE MODEL =================

loss, accuracy = model.evaluate(X_test, y_test)

print("\nTest Accuracy :", accuracy)

# ================= ACCURACY GRAPH =================

plt.figure(figsize=(8,5))

plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])

plt.title('Model Accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')

plt.legend(['Train', 'Validation'])

plt.show()

# ================= LOSS GRAPH =================

plt.figure(figsize=(8,5))

plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])

plt.title('Model Loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')

plt.legend(['Train', 'Validation'])

plt.show()

# ================= PREDICTIONS =================

predictions = model.predict(X_test)

print("\nSample Predictions:\n")

print(predictions[:5])

# ================= POSITIVE / NEGATIVE RESULT =================

print("\nSentiment Results:\n")

for i in range(5):

    if predictions[i][0] > 0.5:
        print("Review", i+1, "-> Positive Review")
    else:
        print("Review", i+1, "-> Negative Review")
