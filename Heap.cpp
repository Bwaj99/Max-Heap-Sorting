#include <iostream>
#include "PrintJob.h"
#include "Heap.h"

using namespace std;

Heap::Heap() { //defines constructor and sets initial value of variable to 0
    numItems = 0;
}

void Heap::enqueue(PrintJob* newJob) {
    if (numItems < MAX_HEAP_SIZE){ //checks if heap has room for newJob
        ++numItems; //adds numItems (member variable of newJob) if heap has room
        arr[numItems-1] = newJob; //stores the pointer to newJob in next available slot in array
        int i = numItems-1; //index of the slot
        trickleUp(i); //ensures newly added item is in coorect place in heap
    }
}

void Heap::dequeue() { //remove the root PrintJob from the heap
    if (numItems > 0){
        if (numItems == 1){ //if only one item in heap, numItems = 0 indicating that heap is empty
            numItems = 0; 
            arr[0] = 0; 
        }
        else{ //if multiple items in heap, replaces root item with last item in heap
            arr[0] = arr[numItems - 1];
            --numItems;
            trickleDown(0); //ensures that new root item is in correct place in heap
        }
    }
}

PrintJob* Heap::highest() { //return pointer to root currently in heap without remobing it
    if (numItems == 0){
        return 0;
    }
    else{ //if items in heap, returns pointer to first item in array
        return arr[0];
    }
}

void Heap::print() {
    if (numItems == 0){
        return; //if heap empty, nothing is printed
    }
    else{
        PrintJob* highPrior = this->highest(); //prints highest priority job in the heap
        cout << "Priority: " << highPrior->getPriority();
        cout << ", Job Number: " << highPrior->getJobNumber();
        cout << ", Number of Pages: " << highPrior->getPages() << endl; 
    }
}

void Heap::trickleDown(int value) {
    for (int i = 0; i < numItems; ++i){
        if (arr[i]->getPriority() > arr[value]->getPriority()){ //checks if priority of item at index i is greater than priority of item at index value
            PrintJob* toSwap; //if true, item at index value is swaapped with item at index i
            toSwap = arr[value];
            arr[value] = arr[i];
            arr[i] = toSwap; //loop continues until all items have been compared with item at index value
        }
    }
}

void Heap::trickleUp(int value) {
    PrintJob* parent = arr[(value-1)/2]; // assigns parent node of item at index value to a pointer variable parent
    while (parent->getPriority() < arr[value]->getPriority() && value > 0){ //loops as long as parent node has a lower priority than item being inserted and the item is not at the root  
        PrintJob* temp = arr[value];
        arr[value] = arr[(value-1) / 2]; 
        arr[(value-1) / 2] = temp; 

        value = (value-1)/2; //value is updated to the index of the parent node
        parent = arr[(value-1)/2]; //updates parent pointer to point to the new parent node of item at index value
    }
}