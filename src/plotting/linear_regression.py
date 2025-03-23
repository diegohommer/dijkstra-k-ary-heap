import statsmodels.api as sm  # Corrected import
import pandas as pd
import numpy as np

# Load data from files
data_A = pd.read_csv('../../data/outputs/dijkstra_fixed_vertices.csv', sep=',', header=None, names=['n', 'm', 'I', 'D', 'U', 'T'])
data_B = pd.read_csv('../../data/outputs/dijkstra_fixed_edges.csv', sep=',', header=None, names=['n', 'm', 'I', 'D', 'U', 'T'])

# Combine data from both files
data = pd.concat([data_A, data_B])

# Validate the data
numeric_columns = ['n', 'm', 'I', 'D', 'U', 'T']
data[numeric_columns] = data[numeric_columns].apply(pd.to_numeric, errors='coerce')
valid_data = data[(data['I'] <= data['n']) & (data['D'] <= data['n']) & (data['U'] <= data['m']) & (data['T'] > 0)].copy()

# Convert time from milliseconds to seconds
valid_data['T'] = valid_data['T'] / 1000

# T(n,m) ∼ a(n^b)(m^c)
# ln(T) = ln(a) + b*ln(n) + c*ln(m)
valid_data.loc[:, 'ln_n'] = np.log(valid_data['n'])
valid_data.loc[:, 'ln_m'] = np.log(valid_data['m'])
valid_data.loc[:, 'ln_T'] = np.log(valid_data['T'])

# Define independent variables (ln_n and ln_m) and dependent variable (ln_T)
X = valid_data[['ln_n', 'ln_m']]
X = sm.add_constant(X)  # Add a constant term for the intercept (ln(a))
y = valid_data['ln_T']

model = sm.OLS(y, X).fit()
print(model.summary())

a = np.exp(model.params['const'])  # a = exp(intercept)
b = model.params['ln_n']           # b
c = model.params['ln_m']           # c

print(f"a = {a}, b = {b}, c = {c}")
