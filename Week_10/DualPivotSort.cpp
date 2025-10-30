#include "DualPivotSort.h"

/*
Switch to insertion sort for arrays with size less than a pre-decided limit. Once the 
size of the sub-array goes lower than the limit, apply insertion sort on that sub-array.
*/
void DualPivotSort::insertionSort(std::vector<int> &avector)
{
    for (unsigned int index = 1; index<avector.size(); index++) {
        int current		 = avector[index];			// remember current item
        unsigned int pos = index;					// need current position to move towards front
        while (pos>0 && avector[pos-1]>current) {	// while not at front and current item is less than previous
            swap(avector[pos], avector[pos-1]);		// shift by 1 spot
            pos--; 									// keep moving towards front of vector
        }
        avector[pos] = current;						// place current item in opened spot
    }
}

int DualPivotSort::partition(std::vector<int> &avector, int first, int last) {return 0;}

// From https://learnforeverlearn.com/yaro_web/
void DualPivotSort::sort(std::vector<int> &A, int left, int right)
{
    if (left < (right - LIMIT))
        insertionSort(A);
    else if ( left < right )
    {
        int p = A[left], q = A[right];
        int h = left + 1, k = h, g = right - 1;

        while(k <= g)
        {
            if(A[k] < p)
            {
                swap(A[k], A[h]);
                h++;
            } else {
                if(A[k] >= q)
                {
                    while(A[g] > q && k < g)
                        g--;
                    swap(A[k], A[g]);
                    g--;

                    if(A[k] < p)
                    {
                        swap(A[k], A[h]);
                        h++;
                    }
                }
            }
            k++;
        }
        h--; g++;
        swap(A[left], A[h]);
        swap(A[right], A[g]);

        sort(A, left , h - 1);
        sort(A, h + 1, g - 1);
        sort(A, g + 1 , right);
    }
}