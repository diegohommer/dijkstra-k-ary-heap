import matplotlib.pyplot as plt
import numpy as np
import csv

def plot_optimal_k():
    k_values = []
    avg_t_values = []

    with open('../../data/outputs/optimal_k_tests.csv', newline='') as csvfile:
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

def plot_heap_ops():
    i_values = []
    d_values = []
    u_values = []
    m_values = []  # To keep track of varying m values

    # Open the CSV file to read the data
    with open('../../data/outputs/dijkstra_ops_tests.csv', newline='') as csvfile:
        csvreader = csv.reader(csvfile)
        next(csvreader)  # Skip header row
        for row in csvreader:
            n_value = int(row[0])  
            m_value = int(row[1])  
            i_values.append(float(row[2])/(30*n_value))  # Normalize insert operations
            d_values.append(float(row[3])/(30*n_value))  # Normalize delete operations
            u_values.append(float(row[4])/(30*m_value))  # Normalize update operations
            m_values.append(m_value)

    # Plotting the data
    plt.figure(figsize=(10, 6))
    plt.plot(m_values, i_values, label="Insert Operations", marker='o')
    plt.plot(m_values, d_values, label="Delete Operations", marker='s')
    plt.plot(m_values, u_values, label="Update Operations", marker='^')
    
    plt.xlabel('m (Number of edges)')
    plt.ylabel('Operations per node or edge')
    plt.title('Heap Operations Analysis with Fixed n')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    plt.show()

# Call the function you want to display
# plot_optimal_k()
plot_heap_ops() 
plt.show()