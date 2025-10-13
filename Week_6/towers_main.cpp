#include <iostream>
#include "LinkedList.hpp"
#include "Disk.hpp"

void moveDisk(int counter, LinkedList<Disk>& fp, LinkedList<Disk>& tp){
    std::cout << "moving disk from " << fp << " to " << tp << " counter = " << counter << std::endl;
}

void move(  int height,
            int& counter,
            LinkedList<Disk>& fromPole, 
            LinkedList<Disk>& toPole,
            LinkedList<Disk>& withPole
         )
{   
    // Base case is one disk left on stack
    if( height >= 1 ){
        move(height-1, counter, fromPole, withPole, toPole);
        counter++;
        toPole.insert( fromPole.pop() );
        moveDisk(counter, fromPole, toPole);
        move(height-1, counter, withPole, toPole, fromPole);
    }
}

void towers_of_hanoi(int height = 3){
    // Instantiate a stack to represent each pole
    LinkedList<Disk> A;
    LinkedList<Disk> B;
    LinkedList<Disk> C;
    int counter = 0;
    
    // Using LIFO logic, because we are treating this as a stack, fill stack
    for( int i=height; i>=1; i-- ) A.insert(Disk(i));

    // Print the starting state
    std::cout << "\n Stack A: ";
    A.print();
    std::cout << "\n Stack B: ";
    B.print();
    std::cout << "\n Stack C: ";
    C.print();

    // Start towers of Hanio solve
    move(height, counter, A, B, C);

    // Print out results
    std::cout << "Stack A: ";
    A.print();
    std::cout << "Stack B: ";
    B.print();
    std::cout << "Stack C: ";
    C.print();
}