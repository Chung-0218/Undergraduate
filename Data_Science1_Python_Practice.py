# Python 기초 과제
import pandas as pd

xl_file = 'score.xlsx' # excel 파일
df = pd.read_excel(xl_file) # dataframe 생성

midterm_20 = df['midterm'] >= 20
final_20 = df['final'] >= 20

X = df[midterm_20 & final_20]

Q1 = X.loc[:, ['sno', 'midterm', 'final']]
print(Q1)