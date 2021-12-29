# Keras Non-Linear Regression
import numpy as np
import matplotlib.pyplot as plt

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Input, Dense
from tensorflow.keras import initializers
from tensorflow.keras.optimizers import Adam, SGD

# y = a + b * X1 + c * (X2 ** 2) + d * (X3 ** 3) + e * (X4 ** 4)

# Keras의 Sequential model 생성, hidden layer 수와 activation function, neuron 수 설정
def gen_sequential_model():
    model = Sequential([
        Input(4, name='input_layer'),
        Dense(16, activation='sigmoid', name='hidden_layer1', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),
        Dense(16, activation='sigmoid', name='hidden_layer2', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),
        Dense(16, activation='sigmoid', name='hidden_layer3', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),
        Dense(1, activation='relu', name='output_layer', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42))
        ])

    model.compile(optimizer='sgd', loss='mse') # 이 부분도 설정 (sgd or adam), learning rate는 기본 값으로 0.001

    return model

# 문제에서 주어진 형태로 non linear regression식과 data sample 생성
# a, b, c, d, e는 원하는 값으로 설정(여기서는 pdf에서 주어진 값으로 함)
def gen_non_linear_regression_dataset(num_samples=1000, a=1, b=3, c=5, d=10, e=20):
    np.random.seed(42)
    X = np.random.rand(num_samples, 4) # X1~X4에 0에서 1사이의 랜덤 값 생성

    X_arr = []
    for X1, X2, X3, X4 in X:
        X_arr.append([X1, X2 ** 2, X3 ** 3, X4 ** 4])
    
    X_arr = np.array(X_arr)

    # print(X_arr.shape)

    coef = np.array([b, c, d, e])
    bias = a

    # print(coef)
    # print(coef.shape)

    y = np.matmul(X_arr, coef.transpose()) + bias

    # print(y)
    # print(y.shape)

    return X_arr, y

# loss 그래프를 그리는 함수
def plot_loss_curve(history):

    plt.figure(figsize=(15, 10))

    plt.plot(history.history['loss'][1:])
    plt.plot(history.history['val_loss'][1:])
    plt.title('model loss')
    plt.ylabel('loss')
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper right')
    plt.show()

# 실제 y값과 예측한 y값을 계산하는 함수
def predict_new_sample(model, X, a=1, b=3, c=5, d=10, e=20):
    X = X.reshape(1, 4) # 배열 X의 형태를 1x4로 변경
    bias = a

    y_actual = b * X[0][0] + c * (X[0][1] ** 2) + d * (X[0][2] ** 3) + e * (X[0][3] ** 4) + bias # 직접 계산

    y_pred = model.predict(X)[0][0] # 예측

    print('y_actual: ', y_actual)
    print('y_pred: ', y_pred)


# 전체 함수 실행
model = gen_sequential_model()
X, y = gen_non_linear_regression_dataset(num_samples=1000) # sample 수 설정
history = model.fit(X, y, epochs=300, verbose=2, validation_split=0.3) # hyperparameter 설정
plot_loss_curve(history)
print("train loss=", history.history['loss'][-1])
print("test loss=", history.history['val_loss'][-1])

predict_new_sample(model, np.array([0.6, 0.3, 0.1, 0.2])) # X1~X4 값을 임의로 설정하고 예측

# YouTube 발표 - https://youtu.be/YMth4ijCGv0
