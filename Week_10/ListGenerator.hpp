#ifndef VECTOR_GENERATOR_HPP
#define VECTOR_GENERATOR_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <utility>

class ListGenerator {
private:
    size_t size {100};
    std::vector<char> listTypes{'a', 'd', 'r', 'p'};
    std::vector<std::vector<int>> sortedLists; // list to be sorted

    std::vector<int> generateList(size_t size, char type)
    {
        std::vector<int> vec(size);
        int temp; // holder for swaps
        
        switch(type)
        {
            case 'a': // Ascending
                for(int i = 0; i < size; i++)
                    vec[i] = i + 1;
                break;

            case 'd': // Descending
                for(size_t i = 0; i < size; i++)
                    vec[i] = size - i;
                break;

            case 'r': // Random
                for(size_t i = 0; i < size; i++)
                    vec[i] = rand() % 100;
                break;

            case 'p': // Partially sorted
                for(size_t i = 0; i < size; i++)
                    vec[i] = i + 1;
                // Swap every 5th item
                for (size_t i = 4; i < vec.size(); i += 5)
                    std::swap(vec[i], vec[i-4]);
        }
        return vec;
    }

public:
    // Constructors
    ListGenerator()
    {
        for(char t : listTypes)
            sortedLists.push_back(generateList(size, t));
    }
    ListGenerator(const size_t n) : size {n}
    {
        for(char t : listTypes)
            sortedLists.push_back(generateList(size, t));
    }
    ~ListGenerator() {};

    // Member functions
    std::vector<std::vector<int>> getLists() { return sortedLists; }
    void printLists()
    {
        for(std::vector<int> list : sortedLists)
            for (size_t i = 0; i < list.size(); i++)
                std::cout << list[i] << " ";
        std::cout << std::endl;
    }
};

#endif