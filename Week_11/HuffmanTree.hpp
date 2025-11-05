#include <string>
#include "MinHeap.hpp"
#include "QuadHashTable.hpp"
#include "BinaryTree.hpp"

template <typename T>
class HuffmanTree {

    private:
        std::string message;
        // key is ascii character, payload is count
        // We don't need the alphabet, we just need to add to the list for each char in the message
        QuadHashMap<int> histogram;

        void create_histogram(){
            //Creates the character frequency histogram (hashMap) for message.
        }

        void build_tree(histogram)
        
/*
- build_tree(histogram): Builds the Huffman Tree (each node needs to store a character 
    and the frequency of that character (could be done with a pair)
    each node that is not a leaf will have a count but no character
    only leaf nodes will have a character
- string compress(string): Compresses the string input
- string inflate(string): Inflates the string input
*/

};