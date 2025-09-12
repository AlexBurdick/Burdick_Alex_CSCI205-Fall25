# Creates a graph from text files in the working directory
import os
import matplotlib.pyplot as plt 
import numpy as np

# Function created by Copilot 09/11/2025
def plot_graph_from_files():
    files = [f for f in os.listdir('.') if os.path.isfile(f) and f.endswith('.txt')]
    for file in files:
        label = file.replace('.txt', '')
        data = np.loadtxt(file, delimiter=' ')
        x = data[:, 0]
        y = data[:, 1]
        plt.plot(x, y, label=label)
    
    plt.xlabel('Problem size')
    plt.ylabel('Comparisons')
    plt.title('Algorithm Analysis')
    plt.legend()
    plt.show()

print("Generating graphs from text files...")
plot_graph_from_files()