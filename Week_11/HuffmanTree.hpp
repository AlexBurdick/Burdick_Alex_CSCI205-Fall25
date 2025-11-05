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
        std::string message;
        // key is ascii character, payload is count
        // We don't need the alphabet, we just need to add to the list for each char in the message
        ClosedHashTable<int> histogram;

        void create_histogram(){
            //Creates the character frequency histogram (hashMap) for message.
        }

        void build_tree(histogram){
             /* Builds the Huffman Tree (each node needs to store a character 
                and the frequency of that character (could be done with a pair)
                each node that is not a leaf will have a count but no character
                only leaf nodes will have a character */
            
        }
        
        string compress(string){
            // Compresses the string input
        }
        
        string inflate(string){
            // Inflates the string input
        }

};