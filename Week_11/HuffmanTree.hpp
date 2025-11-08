#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include <vector>
#include "PriorityQueue.hpp"
#include "ClosedHashTable.hpp"
#include "BinaryTree.hpp"

/* in the lab:
create trees with new to make sure they are heap alloated (declare pointers to trees)
pass this by reference (or pass them as pointers) */
template <typename T>
class HuffmanTree {

    private:

        // Key     = ascii character
        // Payload = count
        // We don't need the alphabet, we just need to add to the list for each char in the message
        ClosedHashTable<int> histogram {11};
        PriorityQueue queue;

        void create_histogram(const std::string& message){
            // Creates the character frequency histogram (hashMap) for message.
            
            // Iterate through each character in the message
            for (char c : message) {
                std::string k(1, c);
                // If character exists in histogram, increment its count
                if (histogram.contains(k))
                    histogram.put(k, histogram.get(k) + 1);
                // If not, add it with count of 1
                else
                    histogram.put(k, 1);
            }

            // Print for testing 
            // histogram.print();
        }

        /* Builds the Huffman Tree (each node needs to store a character 
        and the frequency of that character (could be done with a pair)
        each node that is not a leaf will have a count but no character
        only leaf nodes will have a character */
        void build_queue(){
            // Get all entries from the histogram
            auto entries = histogram.getEntries();
            
            // Create trees and add them to the Priority Queue
            for (const auto& entry : entries) {
                // Create a pair with the character and frequency
                char c = entry.key[0];
                int frequency = entry.value;
                std::pair p = std::make_pair(c, frequency);
                
                // Create a binary tree with the pair
                BinaryTree<std::pair<char, int>>* tree = 
                    new BinaryTree<std::pair<char, int>>(p);
                
                // Add the new tree to thezX priority queue
                queue.enqueue(tree);
            }
            
            /* 
            Now build the Huffman tree by combining the smallest trees
            while (queue.size() > 1) {
                // Get the two trees with smallest frequencies
                BinaryTree<std::pair<char, int>>* left = queue.extractMin();
                BinaryTree<std::pair<char, int>>* right = queue.extractMin();
                
                // Create new internal node with combined frequency
                int combinedFreq = left->getRootVal().second + right->getRootVal().second;
                BinaryTree<std::pair<char, int>>* newTree = 
                    new BinaryTree<std::pair<char, int>>(std::make_pair('\0', combinedFreq));
                
                // Set children
                newTree->insertLeft(left->getRootVal());
                newTree->getLeftChild()->leftChild = left->leftChild;
                newTree->getLeftChild()->rightChild = left->rightChild;
                
                newTree->insertRight(right->getRootVal());
                newTree->getRightChild()->leftChild = right->leftChild;
                newTree->getRightChild()->rightChild = right->rightChild;
                
                // Add back to queue
                queue.insert(newTree, combinedFreq);
            }
            */
        }
        
        std::string compress(const std::string& message){
            // Compresses the string input
            return message;
        }
        
        std::string inflate(const std::string& message){
            // Inflates the string input
            return message;
        }
    
    public:
        HuffmanTree(const std::string& message){
            create_histogram(message);
            build_queue();
        }

        ~HuffmanTree() = default;
        
};

#endif