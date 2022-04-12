#include <iostream>
using namespace std;

class MaxHeap {
   private:
        int N; // size of heap
        int arr[100]; // array representation of heap
        void upHeap(int k);
        void downHeap(int k);
   public:
        MaxHeap();
        void Insert(int element);
        int RemoveMax();
        int size();
};

void sort(int a[], int size) {
    // Build heap structure
    MaxHeap heap;
    for (int i=0; i<size; i++) {
        heap.Insert(a[i]);
    }

    // Sort array using max heap
    for (int i=size-1; i>=0; i--) {
        a[i] = heap.RemoveMax();
    }
}

int main() {
   // Sort array using heap
   int arr[10] = {4,3,7,5,1,0,2,9,8,6};
   int arr_size = 10;
   cout << "Unsorted array:\n";
   for (int i = 0; i < arr_size; i++) {
       cout << arr[i] << " ";
   }
   cout << "\n";
   sort(arr, arr_size);
   cout << "Sorted array using Max-Heap:\n";
   for (int i = 0; i < arr_size; i++) {
       cout << arr[i] << " ";
   }
   cout << "\n";

   return 0;
}

MaxHeap::MaxHeap() {
    N = 0;
}

// Maintain heap constraints by moving child up if needed
void MaxHeap::upHeap(int k) {
    int v;
    v = arr[k];
    int i = k;
    // Parent node of i is (i-1)/2
    while (i > 0 && arr[(i-1)/2] <= v) {
        // Swap child node and parent node
        arr[i] = arr[(i-1)/2];
        i = (i-1)/2;
    }
    arr[i] = v;
}

void MaxHeap::Insert(int element) {
    N++;
    arr[N-1] = element;
    upHeap(N-1);
}

// Maintain heap constraints by moving parent down if needed
void MaxHeap::downHeap(int k) {
    int l, r, v;
    v = arr[k];
    int i = k;
    while (i < N/2) { // node has child
        l = 2*i + 1; // left node
        r = 2*i + 2; // right node
        int bigger = l;
        if (r <= N-1) { // Right node exist
            // Select the child node that has bigger value
            if (arr[l] < arr[r]) {
                bigger = r;
            }
        }

        if (v >= arr[bigger]) {
            // Heap constraints is sastified, stop down heap procedure
            break;
        } else {
            // Swap parent node and child node, then continue down heap procedure
            arr[i] = arr[bigger];
            i = bigger;
        }
    }
    arr[i] = v;
}

int MaxHeap::RemoveMax() {
    int max_value;
    max_value = arr[0];
    arr[0] = arr[N-1];
    N--;
    downHeap(0);
    return max_value;
}

int MaxHeap::size() {
    return N;
}
