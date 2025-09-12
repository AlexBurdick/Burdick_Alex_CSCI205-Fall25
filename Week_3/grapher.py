# Creates a graph from text files in the working directory
import os
import matplotlib.pyplot as plt 
import numpy as np

def plot_graph_from_files():
    files = [f for f in os.listdir('.') if os.path.isfile(f) and f.endswith('.txt')]
    for file in files:
        data = np.loadtxt(file, delimiter=' ')
        x = data[:, 0]
        y = data[:, 1]
        plt.plot(x, y, label=file)
    
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Performance Graphs')
    plt.legend()
    plt.show()

print("Generating graphs from text files...")
plot_graph_from_files()