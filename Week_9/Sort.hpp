# ifndef SORT_HPP
# define SORT_HPP

#include <fstream>
#include "stdlib.h"
#include <vector>
#include <cmath>
#include <functional>

class SortAlgorithm {
    private:
        const std::string name;
        std::vector<std::vector<int>>& data;

        virtual int sort(std::vector<int>& arr) = 0; // Pure virtual function for sorting
        virtual ~SortAlgorithm() = default; // Virtual destructor

        // Write results to file (from LeChat, 10/22/2025)
        void writeToFile(const std::string& filename) {
            std::ofstream outFile(filename);
            if (!outFile.is_open()) {
                std::cerr << "Error: Could not open file " << filename << std::endl;
                return;
            }

            for (std::vector<int> nums : data)
                outFile << nums[0] << " " << nums[1] << std::endl;
            
            outFile.close();
        }

        // helper function to swap two vector elements
        void swap(std::vector<int>& vec, int a, int b){
            int temp	= vec[a];
            vec[a]		= vec[b];
            vec[b]		= temp;
        }
};

# endif