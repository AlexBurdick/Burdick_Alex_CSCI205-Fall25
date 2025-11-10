/*
g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
valgrind --tool=memcheck --leak-check=full ./a.out
*/

#include <iostream>
#include <ctime>
#include <vector>
#include "Huffman.hpp"

/**
 * @brief Compresses a message using Huffman coding
 * NOTE: Caller is responsible for deleting the returned tree
 * 
 */
int main() {

    // Simple one-line compression
    std::string message = "TEST MESSAGE";
    std::pair<std::string, BinaryTree<std::pair<char, int>>*> compressed = Huffman<int>::compress(message);
    std::cout << "Compressed: " << compressed.first << std::endl;
    
    // Get detailed compression info
    Huffman<int>::printCompressionInfo(message);
    
    // Multiple compressions
    std::string text1 = "hello world";
    std::string text2 = "another example";
    
    std::pair<std::string, BinaryTree<std::pair<char, int>>*> compressed1 = Huffman<int>::compress(text1);
    std::pair<std::string, BinaryTree<std::pair<char, int>>*> compressed2 = Huffman<int>::compress(text2);

    std::string decompressed1 = Huffman<int>::inflate(compressed1.first, compressed1.second);
    std::string decompressed2 = Huffman<int>::inflate(compressed2.first, compressed2.second);

    std::cout << "Compressed 1: " << compressed1.first << std::endl;
    std::cout << "Decompressed: " << decompressed1 << std::endl;
    std::cout << "Compressed 2: " << compressed2.first << std::endl;
    std::cout << "Decompressed: " << decompressed2 << std::endl;
    
    delete compressed.second;
    delete compressed1.second;
    delete compressed2.second;
    return 0;
}