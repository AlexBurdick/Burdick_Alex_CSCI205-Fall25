#include <iostream>
#include <ctime>
#include <vector>
#include "HuffmanTree.hpp"

int main() {

    // Simple one-line compression
    std::string message = "TEST MESSAGE";
    std::string compressed = HuffmanTree<int>::compress(message);
    std::cout << "Compressed: " << compressed << std::endl;
    
    // Get detailed compression info
    HuffmanTree<int>::printCompressionInfo(message);
    
    // Multiple compressions
    std::string text1 = "hello world";
    std::string text2 = "another example";
    
    std::string compressed1 = HuffmanTree<int>::compress(text1);
    std::string compressed2 = HuffmanTree<int>::compress(text2);
    

    return 0;
}