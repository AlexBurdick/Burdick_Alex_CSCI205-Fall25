#include <iostream>
#include <string>
#include <cstdlib>
#include "BinaryTree.hpp"

using namespace std;


int main() {

    BinaryTree<char> *r = new BinaryTree<char>('a');
	r->insertLeft('b');
	r->insertRight('c');
	r->getLeftChild()->insertRight('d');
	r->getLeftChild()->insertLeft('e');
	r->getRightChild()->insertLeft('f');
	r->getRightChild()->insertRight('g');
	
	cout << "\nIN ORDER TRAVERSAL" << endl;
	r->inorder();
	cout << "\nPOST ORDER TRAVERSAL" << endl;
	r->postorder();
	cout << "\nPRE ORDER TRAVERSAL" << endl;
	r->preorder();
	cout << endl;
	r->printTree();
	
	return 0;
}
