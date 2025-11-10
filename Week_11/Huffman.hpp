#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <vector>
#include "PriorityQueue.hpp"
#include "ClosedHashTable.hpp"
#include "BinaryTree.hpp"

/* in the lab:
create trees with new to make sure they are heap alloated (declare pointers to trees)
pass this by reference (or pass them as pointers) */
template <typename T>
class Huffman {

    private:
        // We don't need the alphabet, we just need to add to the list for each char in the message
        ClosedHashTable<int> histogram {11}; // Key = ascii character, Payload = count
        ClosedHashTable<std::string> huffmanCodes {11};
        PriorityQueue queue;
        BinaryTree<std::pair<char, int>>* huffmanTree = nullptr;
        std::vector<int> code;
        
        /**
         * @brief Private construct creates a new Huffman object, and will only be 
         * called by the compress static memeber function. This calls methods to turn
         * the input string into a huffman tree and a hash table of huffman codes.
         * 
         * @param message 
         */
        Huffman(const std::string& message){
            createHistogram(message);
            buildQueue();
            generateCodes(huffmanTree, "");
        }

        /**
         * @brief Creates the character frequency histogram (hashMap) for message.
         * 
         * @param message 
         */
        void createHistogram(const std::string& message) {            
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

        /**
         * @brief Builds the Huffman Tree - each stores a character and the frequency 
         * of that character in a pair. Each node that is not a leaf will have a 
         * count but no character; only leaf nodes will have a character.
         * 
         */
        void buildQueue() {
            // Get all entries from the histogram
            auto entries = histogram.getEntries();
            
            // Create trees and add them to the Priority Queue
            for (const auto& entry : entries) {
                // Create a pair with the character and frequency
                char c = entry.key[0];
                int frequency = entry.value;
                std::pair<char, int> p = std::make_pair(c, frequency);
                
                // Create a binary tree with the pair
                BinaryTree<std::pair<char, int>>* tree = 
                    new BinaryTree<std::pair<char, int>>(p);
                
                // Add the new tree to thezX priority queue
                queue.enqueue(tree);
            }
            
            // Build Huffman tree by combining the smallest trees
            while (queue.size() > 1) {
                // Get the two trees with smallest frequencies
                BinaryTree<std::pair<char, int>>* left  = queue.dequeue();
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
            huffmanTree = queue.dequeue();
        }

        /**
         * @brief Recursive function to generate Huffman codes
         * 
         * @param node 
         * @param code 
         */
        void generateCodes(BinaryTree<std::pair<char, int>>* node, const std::string& code) {
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
        
        /**
         * @brief Create a hash table of huffman codes. Returns the encoded message
         * and the huffman tree needed to decode it.
         * 
         * @param message 
         * @return std::pair<std::string, BinaryTree<std::pair<char, int>>*> 
         */
        std::pair<std::string, BinaryTree<std::pair<char, int>>*> compressMessage(const std::string& message) {
            std::string compressed;
            for (char c : message) {
                std::string charStr(1, c);
                compressed += huffmanCodes.get(charStr);
            }
            return std::make_pair(compressed, huffmanTree);
        }

    public:
        ~Huffman(){}

        /**
         * @brief Static compress function that calls the Huffman private constructor.
         * 
         * @param message 
         * @return std::pair<std::string, BinaryTree<std::pair<char, int>>*> 
         */
        static std::pair<std::string, BinaryTree<std::pair<char, int>>*> compress(const std::string& message) {
            Huffman compressor(message);
            return compressor.compressMessage(message);
        }

        /**
         * @brief Accepts the encoded message and the huffman tree to decode it, and
         * returns the decoded message string.
         * 
         * @param codedMessage 
         * @param tree 
         * @return std::string 
         */
        static std::string inflate(const std::string& codedMessage, BinaryTree<std::pair<char, int>>* tree) {
            std::string decoded;
            BinaryTree<std::pair<char, int>>* current = tree;
            
            // Traverse the Huffman tree using the binary code
            for (char bit : codedMessage) {
                if (bit == '0')
                    current = current->getLeftChild();
                else if (bit == '1')
                    current = current->getRightChild();
                else
                    throw std::runtime_error("Invalid bit in coded message: " + std::string(1, bit));
                
                // If we reached a leaf node, add the character to decoded string
                if (current != nullptr && current->getRootVal().first != '\0') {
                    decoded += current->getRootVal().first;
                    current = tree;  // Reset to root for next character
                }
            }
            
            // Check if we ended in the middle of a code
            if (current != tree && current != nullptr)
                throw std::runtime_error("Incomplete Huffman code at end of message");
            
            return decoded;
        }
        
        // Test code written by DeepSeek (11/09/2025), it occured to AI to get the bit
        // before and after compression, cool!
        static void printCompressionInfo(const std::string& message) {
            Huffman compressor(message);
            
            std::cout << "Original message: " << message << std::endl;
            std::cout << "Original size: " << message.length() * 8 << " bits" << std::endl;
            
            std::string compressed = compressor.compressMessage(message).first;
            std::cout << "Compressed: " << compressed << std::endl;
            std::cout << "Compressed size: " << compressed.length() << " bits" << std::endl;
            
            double ratio = (1.0 - (double)compressed.length() / (message.length() * 8.0)) * 100.0;
            std::cout << "Compression ratio: " << ratio << "%" << std::endl;
            
            compressor.printCodes();
        }

        // Helper method for printCompressionInfo
        void printCodes() {
            std::cout << "Huffman Codes:" << std::endl;
            auto codes = huffmanCodes.getEntries();
            for (const auto& entry : codes) {
                std::cout << "'" << entry.key << "' : " << entry.value << std::endl;
            }
        }
};

#endif