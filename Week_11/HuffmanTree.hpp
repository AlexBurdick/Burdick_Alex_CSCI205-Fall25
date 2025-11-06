#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include "PriorityQueue.hpp"
#include "ClosedHashTable.hpp"
#include "BinaryTree.hpp"
/*
in the lab:
create trees with new to make sure they are heap alloated (declare pointers to trees)
pass this by reference (or pass them as pointers)
*/
template <typename T>
class HuffmanTree {

    private:
        // Key      = ascii character
        // Payload  = count
        // We don't need the alphabet, we just need to add to the list for each char in the message
        ClosedHashTable<int> histogram = ClosedHashTable(0);
        PriorityQueue<std::pair<char, int>> queue = PriorityQueue();

        void create_histogram(const std::string& message){
            // Creates the character frequency histogram (hashMap) for message.
            
            // Iterate through each character in the message
            for (char c : message) {
                // If character exists in histogram, increment its count
                if (histogram.contains(c))
                    histogram.put(c, histogram.get(c) + 1);
                // If not, add it with count of 1
                else
                    histogram.put(c, 1);
            }
            
            // Print for testing 
            histogram.print();
        }

        void build_tree(){
             /* Builds the Huffman Tree (each node needs to store a character 
                and the frequency of that character (could be done with a pair)
                each node that is not a leaf will have a count but no character
                only leaf nodes will have a character */
            
        }
        
        std::string compress(std::string message){
            // Compresses the string input
            return message;
        }
        
        std::string inflate(std::string message){
            // Inflates the string input
            return message;
        }
    
    public:
        HuffmanTree(const std::string message){
            createHistogram(message);
        }
        
};

#endif