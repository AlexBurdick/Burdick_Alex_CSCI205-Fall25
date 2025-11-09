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
        ClosedHashTable<std::string> huffmanCodes {11};
        PriorityQueue queue;
        std::vector<int> code;
        int huffmanCodes[28];

        void createHistogram(const std::string& message) {
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
        void buildQueue() {
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
            
            // Build Huffman tree by combining the smallest trees
            while (queue.size() > 1) {
                // Get the two trees with smallest frequencies
                BinaryTree<std::pair<char, int>>* left = queue.dequeue();
                BinaryTree<std::pair<char, int>>* right = queue.dequeue();
                
                // Create new internal node with combined frequency
                int combinedFreq = left->getRootVal().second + right->getRootVal().second;
                
                // Create a new internal node with null value as key
                BinaryTree<std::pair<char, int>>* newTree = 
                    new BinaryTree<std::pair<char, int>>(std::make_pair('\0', combinedFreq));
                
                // Set children
                newTree->connectLeft(left);
                newTree->connectRight(right);
                
                // Add back to queue
                queue.enqueue(newTree);
            }  
        }

        // Recursive function to generate Huffman codes
        void huffmanEncode(BinaryTree<std::pair<char, int>>* node, const std::string& code) {
            // Validation
            if (node == nullptr) return;
            
            // If it's a leaf node (has a character), store the code
            if (node->getRootVal().first != '\0') {
                std::string charStr(1, node->getRootVal().first);
                huffmanCodes.put(charStr, code);
            }
            
            // Recursively traverse left (add '0') and right (add '1')
            generateCodes(node->getLeftChild(), code + "0");
            generateCodes(node->getRightChild(), code + "1");
        }
        
        // Create a hash table of huffman codes
        std::string compressMessage(const std::string& message) {
            std::string compressed;
            for (char c : message) {
                std::string charStr(1, c);
                compressed += huffmanCodes.get(charStr);
            }
            return compressed;
        }
        
        std::string inflateMessage(const std::string& message){
            // Inflates the string input
            return message;
        }
    
        HuffmanTree(const std::string& message){
            createHistogram(message);
            buildQueue();
            huffmanEncode();
        }

    public:
        ~HuffmanTree() = default;

        // Static compress function
        static std::string compress(const std::string& message) {
            // Create a temporary HuffmanTree instance
            HuffmanTree compressor(message);
            
            // Use it to compress the message
            return compressor.compressMessage(message);
        }

        std::string inflate(const std::string& codedMessage) {
            std::string message = inflateMessage(inflateMessage);
            return message;
        }
        
        // Test code written by DeepSeek (11/09/2025)
            static void printCompressionInfo(const std::string& message) {
            HuffmanTree compressor(message);
            
            std::cout << "Original message: " << message << std::endl;
            std::cout << "Original size: " << message.length() * 8 << " bits" << std::endl;
            
            std::string compressed = compressor.compressMessage(message);
            std::cout << "Compressed: " << compressed << std::endl;
            std::cout << "Compressed size: " << compressed.length() << " bits" << std::endl;
            
            double ratio = (1.0 - (double)compressed.length() / (message.length() * 8.0)) * 100.0;
            std::cout << "Compression ratio: " << ratio << "%" << std::endl;
            
            compressor.printCodes();
        }
};

#endif