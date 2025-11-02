#include "DualPivotSort.h"



int DualPivotSort::partition(std::vector<int> &avector, int first, int last) {return 0;}

// From https://learnforeverlearn.com/yaro_web/
void DualPivotSort::sort(std::vector<int> &A, int left, int right)
{
    recursionDepth++;
	maxRecursions = max(maxRecursions, recursionDepth);

    if ( (right - left + 1) <= right )
    {
        // Extract the subarray from first to last
        std::vector<int> subvector(A.begin() + left, A.begin() + right + 1);
        insertionSort(subvector);
        // Copy the sorted subarray back to the original vector
        std::copy(subvector.begin(), subvector.end(), A.begin() + left);
    }
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
    recursionDepth--;
}