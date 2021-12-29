# Gradient Descent 과제
import os
import time
import pymysql
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import statsmodels.api as sm

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler as sc

def load_dbscore_data():
    conn = pymysql.connect(host='localhost', user='root',
                    password='626537', db='data_science3', charset='utf8')
    curs = conn.cursor(pymysql.cursors.DictCursor)

    sql = "select * from db_score"
    curs.execute(sql)

    data = curs.fetchall()

    curs.close()
    conn.close()

    X = [(t['attendance'], t['homework'], t['final']) for t in data]
    X = np.array(X)

    y = [(t['score']) for t in data]
    y = np.array(y)

    return X, y

X, y = load_dbscore_data()

data = pd.read_csv('db_score.csv')


# y = mX + c

X_const = sm.add_constant(X) # 상수항 추가
model = sm.OLS(y, X_const)
ls = model.fit()

# print(ls.summary())
# print(ls.params)


ls_c = ls.params[0]
ls_m1 = ls.params[1]
ls_m2 = ls.params[2]
ls_m3 = ls.params[3]

c = -3.6583
m1 = 1.9348
m2 = 1.7178
m3 = 1.4972

for i in range(len(data)):
        y_pred = X[i][0] * ls_m1 + X[i][1] * ls_m2 + X[i][2] * ls_m3 + ls_c

# plt.plot([min(X), max(X)], [min(y_pred), max(y_pred)], color='red')
# plt.show()


def gradient_descent_naive(X, y):

    epochs = 100000
    min_grad = 0.0001
    learning_rate = 0.001
    
    m1 = 0.0
    m2 = 0.0
    m3 = 0.0
    c = 0.0
    
    n = len(y) # # of sample
    
    c_grad = 0.0
    m1_grad = 0.0
    m2_grad = 0.0
    m3_grad = 0.0
    
    for epoch in range(epochs):
        
        for i in range(len(data)):
            y_pred = m1 * X[i][0] + m2 * X[i][1] + m3 * X[i][2] + c

            m1_grad += 2*(y_pred-y[i]) * X[i][0]
            m2_grad += 2*(y_pred-y[i]) * X[i][1]
            m3_grad += 2*(y_pred-y[i]) * X[i][2]
            c_grad += 2*(y_pred - y[i])

        c_grad /= n
        m1_grad /= n
        m2_grad /= n
        m3_grad /= n
        
        m1 = m1 - learning_rate * m1_grad
        m2 = m2 - learning_rate * m2_grad
        m3 = m3 - learning_rate * m3_grad
        c = c - learning_rate * c_grad
        
        if ( epoch % 1000 == 0):
            print("epoch %d: m1_grad=%f, m2_grad=%f, m3_grad=%f, c_grad=%f, m1=%f, m2=%f, m3=%f, c=%f" %(epoch, m1_grad, m2_grad, m3_grad, c_grad, m1, m2, m3, c) )   
        
        if ( abs(m1_grad) < min_grad and abs(m2_grad) < min_grad and abs(m3_grad) < min_grad and abs(c_grad) < min_grad ):
            break
        
    return m1, m2, m3, c

# start_time = time.time()
# m1, m2, m3, c = gradient_descent_naive(X, y)
# end_time = time.time()

# print("Time: %f seconds" %(end_time - start_time))

# print("\nFinal:")
# print("gdn_m1=%f, gdn_m2=%f, gdn_m3=%f, gdn_c=%f" %(m1, m2, m3, c) )
# print("ls_m1=%f, ls_m2=%f, ls_m3=%f ls_c=%f" %(ls_m1, ls_m2, ls_m3, ls_c) )


def gradient_descent_vectorized(X, y):
    
    epochs = 100000
    min_grad = 0.0001
    learning_rate = 0.001
    
    m1 = 0.0
    m2 = 0.0
    m3 = 0.0
    c = 0.0
    
    n = len(y) # # of sample
    
    c_grad = 0.0
    m1_grad = 0.0
    m2_grad = 0.0
    m3_grad = 0.0

    for epoch in range(epochs):

        # for i in range(len(data)):
        y_pred = m1 * X + m2 * X + m3 * X + c

        m1_grad = (2*(y_pred - y)*X).sum()/n
        m2_grad = (2*(y_pred - y)*X).sum()/n
        m3_grad = (2*(y_pred - y)*X).sum()/n
        c_grad = (2 * (y_pred - y)).sum()/n

        m1 = m1 - learning_rate * m1_grad
        m2 = m2 - learning_rate * m2_grad
        m3 = m3 - learning_rate * m3_grad
        c = c - learning_rate * c_grad

        if ( epoch % 1000 == 0):
            print("epoch %d: m1_grad=%f, m2_grad=%f, m3_grad=%f, c_grad=%f, m1=%f, m2=%f, m3=%f, c=%f" %(epoch, m1_grad, m2_grad, m3_grad, c_grad, m1, m2, m3, c) )      
        
        if ( abs(m1_grad) < min_grad and abs(m2_grad) < min_grad and abs(m3_grad) < min_grad and abs(c_grad) < min_grad ):
            break

    return m1, m2, m3, c

start_time = time.time()
m1, m2, m3, c = gradient_descent_vectorized(X, y)
end_time = time.time()

print("Time: %f seconds" %(end_time - start_time))

print("\nFinal:")
print("gdv_m1=%f, gdv_m2=%f, gdv_m3=%f, gdv_c=%f" %(m1, m2, m3, c) )
print("ls_m1=%f, ls_m2=%f, ls_m3=%f ls_c=%f" %(ls_m1, ls_m2, ls_m3, ls_c) )
