# Creates a graph from text files in the working directory
import os
import matplotlib.pyplot as plt 
import numpy as np

# Function created by Copilot 09/11/2025
def plot_algorith_analysis():
    # Opening files
    data_dir = os.path.join(os.getcwd(), 'data')
    files = [
        f for f in os.listdir(data_dir)
        if os.path.isfile(os.path.join(data_dir, f)) and f.endswith('.txt')
    ]
    print("Files found:", files)  # Debug: Check if files are found

    # Group files by prefix (e.g., "bubble_", "merge_", "quick_")
    groups = {}
    for file in files:
        # Extract the prefix before the first underscore or dash
        prefix = file.split('_')[0]
        
        if prefix not in groups:
            groups[prefix] = []
        groups[prefix].append(file)
        
    for group_name, group_files in groups.items():
        for file in files:
            # Sort out naming
            title = group_name
            label = file.split('_')[-1].replace('.txt', '')
            match label:
                case 'a':
                    label = "Ascending"
                case 'd':
                    label = "Descending"
                case 'r':
                    label = "Random"
                case 'p':
                    label = "Partially sorted"
                case _: # Default case
                    label = ""
            
            try:
                file_path = os.path.join(data_dir, file)
                data = np.loadtxt(file_path, delimiter=' ')
                x = data[:, 0]
                y = data[:, 1]
                plt.plot(x, y, label=label)
            except Exception as e:
                print(f"Error loading {file}: {e}")

        plt.xlabel('Problem size')
        plt.ylabel('Swaps')
        plt.title(title)

        # Create the graphs folder if it doesn't exist
        os.makedirs('graphs', exist_ok=True)
        plt.savefig(f'graphs/{group_name}_analysis.png')

        # Optional: still show it plt.show()

print("Generating graphs from text files...")
plot_algorith_analysis()