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

def plot_dijkstra_benchmark(fixed_type):
    i_values = []
    d_values = []
    u_values = []
    x_values = []  # Stores either n or m, depending on what is varying
    t_values = []  # Stores normalized execution time
    
    # Determine filename and x-axis label based on fixed_type
    if fixed_type == "vertices":
        filename = "../../data/outputs/dijkstra_fixed_vertices.csv"
        xlabel = "m (Number of edges)"
    elif fixed_type == "edges":
        filename = "../../data/outputs/dijkstra_fixed_edges.csv"
        xlabel = "n (Number of vertices)"
    else:
        raise ValueError("Invalid fixed_type. Use 'vertices' or 'edges'.")
    
    with open(filename, newline='') as csvfile:
        csvreader = csv.reader(csvfile)
        next(csvreader)  # Skip header row
        for row in csvreader:
            n_value = int(row[0])  
            m_value = int(row[1])  
            i_value = float(row[2])
            d_value = float(row[3])
            u_value = float(row[4])
            t_value = float(row[5])  # Execution time (T)
            
            # Determine which variable is the x-axis
            x_value = m_value if fixed_type == "vertices" else n_value
            x_values.append(x_value)
            
            # Check if I <= n, D <= n, U <= m
            if i_value > n_value or d_value > n_value or u_value > m_value:
                print(f"Invalid data for n={n_value}, m={m_value}: I={i_value}, D={d_value}, U={u_value}")
            
            # Normalize operations
            i_values.append(i_value / n_value)
            d_values.append(d_value / n_value)
            u_values.append(u_value / m_value)
            
            # Normalize execution time T / ((n + m) * log(n))
            t_normalized = t_value / ((n_value + m_value) * np.log(n_value))
            t_values.append(t_normalized)
    
    # Plotting the operations and execution time
    plt.figure(figsize=(12, 8))
    
    # Subplot for Insert, Delete, and Update operations
    plt.subplot(2, 1, 1)
    plt.plot(x_values, i_values, label="Insert Operations", marker='o')
    plt.plot(x_values, d_values, label="Delete Operations", marker='s')
    plt.plot(x_values, u_values, label="Update Operations", marker='^')
    plt.xlabel(xlabel)
    plt.ylabel('Operations per node or edge')
    plt.title(f'Heap Operations Analysis with Fixed {"n" if fixed_type == "vertices" else "m"}')
    plt.legend()
    plt.grid(True)
    
    # Subplot for Execution Time
    plt.subplot(2, 1, 2)
    plt.plot(x_values, t_values, label="Normalized Execution Time (T / ((n + m) * log(n)))", color='red', marker='x')
    plt.xlabel(xlabel)
    plt.ylabel('Normalized Execution Time')
    plt.title(f'Execution Time Analysis with Fixed {"n" if fixed_type == "vertices" else "m"}')
    plt.legend()
    plt.grid(True)
    
    plt.tight_layout()
    plt.show()

def plot_fixed_vertices():
    plot_dijkstra_benchmark("vertices")

def plot_fixed_edges():
    plot_dijkstra_benchmark("edges")

# Call the function you want to display
# plot_optimal_k()
plot_fixed_vertices() 
plt.show()