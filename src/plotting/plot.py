import matplotlib.pyplot as plt
import numpy as np
import csv

def plot_optimal_k():
    k_values = []
    avg_t_values = []

    with open('../../outputs/optimal_k_tests.csv', newline='') as csvfile:
        csvreader = csv.reader(csvfile)
        next(csvreader)
        for row in csvreader:
            k_values.append(int(row[0]))
            avg_t_values.append(float(row[1]))

    k_values = np.array(k_values)
    avg_t_values = np.array(avg_t_values)

    plt.plot(k_values, avg_t_values, label='Avg_T vs k', color='b')
    plt.xlabel('k')
    plt.ylabel('Avg_T(ms)')
    plt.title('k (k-ary Heap) vs Avg_T(ms)')
    plt.xticks(np.arange(min(k_values), max(k_values)+1, step=4)) 
    plt.legend()

# Call the function you want to display
plot_optimal_k() 
plt.show()