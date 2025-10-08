#include <iostream>
#include "LinkedList.hpp"
#include "Disk.hpp"

void moveDisk(char fp, char tp){
    std::cout << "moving disk from " << fp << " to " << tp << std::endl;
}

void moveTower(int height, char fromPole, char toPole, char withPole){
    if (height >= 1){
        moveTower(height-1, fromPole, withPole, toPole); //Recursive call
        moveDisk(fromPole, toPole);
        moveTower(height-1, withPole, toPole, fromPole); //Recursive call
    }
}

void move(int height, LinkedList<Disk>& A, LinkedList<Disk>& B, LinkedList<Disk>& C){
    // Base case is no disks left on stack1
    if( height >= 1 ){
        B.insert(A.pop());
        --height;
    }
}

void towers_of_hanoi(int height = 3){
    // Instantiate a stack to represent each pole
    LinkedList<Disk> A;
    LinkedList<Disk> B;
    LinkedList<Disk> C;

    for( int i = 1; i <= height; i++ ){
        A.insert(Disk(i));
        C.insert(Disk(i));
    }

    move(height, A, B, C);
    std::cout << C;
}