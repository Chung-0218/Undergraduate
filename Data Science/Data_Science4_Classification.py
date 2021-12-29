# Classification 실습 과제 (SVM)
import pandas as pd
import numpy as np
import pymysql
import statistics as stats
import matplotlib.pyplot as plt
import sklearn.model_selection

from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.datasets import make_multilabel_classification
from sklearn.multiclass import OneVsRestClassifier
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.metrics import recall_score
from sklearn.metrics import precision_score
from sklearn.metrics import f1_score

data = pd.read_csv('db_score_3_labels.csv') # csv 파일 읽기

X = data.drop(['grade'], axis=1)
y = data['grade']

sc = StandardScaler() # 데이터 스케일 조정, 표준화
X = sc.fit_transform(X)

X_train, X_test, y_train,y_test = train_test_split(X,y,test_size = 0.2, random_state = 0) # data 분할

classifier = SVC(kernel='linear', random_state=0) # SVM model
classifier.fit(X_train, y_train) # model 학습

y_pred = classifier.predict(X_test) # model 평가
y_test = y_test.values # 실제 값

confusion_matrix(y_test, y_pred)

print('Accuracy: ', accuracy_score(y_test, y_pred))
print('Recall: ', recall_score(y_test, y_pred, average='macro'))
print('Precision: ', precision_score(y_test, y_pred, average='weighted'))
print('F1 Score: ', f1_score(y_test, y_pred, average='weighted'))
