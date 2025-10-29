#ifndef LIST_GENERATOR_HPP
#define LIST_GENERATOR_HPP

#include <vector>
#include <cstdlib>
#include <utility>

using namespace std;

class ListGenerator {
private:
	vector<char> listTypes{'a', 'd', 'r', 'p'};
    vector<pair<char, vector<int>>> testLists;

    vector<int> generateList(size_t size, char type)
    {
        vector<int> vec(size);
        
        switch(type)
        {
            case 'a': // Ascending
                for(size_t i = 0; i < size; i++)
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
                    swap(vec[i], vec[i-4]);
        }
        return vec;
    }
    
public:
    ListGenerator(size_t size) {
        for(char t : listTypes) {
            testLists.push_back({t, generateList(size, t)});
        }
    }

    vector<pair<char, vector<int>>> getLists() { return testLists; }

    void printAllLists() { // Print utility for testing purposes
        for (const auto& [type, data] : testLists) {
            cout << "List type '" << type << "': ";
            for (int num : data) {
                cout << num << " ";
            }
            cout << endl;
        }
    }
};

#endif