# Data summary 과제
import pandas as pd
import numpy as np
import openpyxl
import statistics as stats
import matplotlib.pyplot as plt
import seaborn as sns

xl_file = 'db_score.xlsx'
df = pd.read_excel(xl_file)

plt.scatter(df['final'], df['score'])
plt.xlabel('final')
plt.ylabel('score')
plt.grid()
plt.show()
