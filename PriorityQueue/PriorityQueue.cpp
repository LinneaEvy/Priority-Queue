#include <iostream>
#include <vector>
template <typename E>
class PriorityQueue {
	E* priorityQueue;
	int* endOfHeap;
	int priorityQueueSize;
	int priorityQueueHeight;

public:
	PriorityQueue(int n, E* arr);
	PriorityQueue();

	int getLeftChild(int currentIndex);
	int getRightChild(int currentIndex);
	int getParent(int currentIndex);

	void push_back(E data);
	void push_back(E data, bool(*compare)(E, E));
	void expandQueue();
	void pop_back();
	void pop_back(bool(*compare)(E, E));

	int front() { return priorityQueue[0]; }
	void printQueue();

	void recalcHeap(int currentIndex);
	void recalcHeapDownwards(int currentIndex);
	void recalcHeap(int currentIndex, bool(*compare)(E, E));
	void recalcHeapDownwards(int currentIndex, bool(*compare)(E, E));
	void swap(int index1, int index2);
};//overload operators

template<typename E>
PriorityQueue<E>::PriorityQueue(int n, E* arr)
{
	priorityQueue = arr;
	priorityQueueSize = std::pow(2, n) - 1;
	priorityQueueHeight = n;
	endOfHeap = &arr[0];
}

template<typename E>
PriorityQueue<E>::PriorityQueue()
{
	E arr[16 - 1];
	priorityQueue = arr;
	priorityQueueSize = std::pow(2, 4) - 1;
	priorityQueueHeight = 4;
	endOfHeap = &arr[0];
}

template<typename E>
int PriorityQueue<E>::getLeftChild(int currentIndex)
{
	return ((((currentIndex + 1) * 2 - 1) > ((endOfHeap - &priorityQueue[0]) -1)) ? currentIndex : ((currentIndex + 1) * 2 - 1));
}

template<typename E>
int PriorityQueue<E>::getRightChild(int currentIndex)
{
	return ((((currentIndex + 1) * 2) > ((endOfHeap - &priorityQueue[0]) - 1)) ? currentIndex : ((currentIndex + 1) * 2));
}

template<typename E>
int PriorityQueue<E>::getParent(int currentIndex)
{
	if (currentIndex == 0) return 0;
	return ((currentIndex % 2 != 0)? (currentIndex/2): (currentIndex-1)/2);
}

template<typename E>
void PriorityQueue<E>::push_back(E data)
{
	*(endOfHeap) = data;
	
	recalcHeap(endOfHeap - &priorityQueue[0]);

	if (priorityQueueSize <= endOfHeap - &priorityQueue[0]) {
		std::cout << "priority queue is full call expandQueue() for more space" << std::endl;
	}
	else {
		endOfHeap += 1;
		//std::cout << "current position of end of heap" << endOfHeap - &priorityQueue[0] << std::endl;
	}
	
}

template<typename E>
void PriorityQueue<E>::pop_back()
{
	if (endOfHeap - &priorityQueue[0] <= 0) {
		std::cout << "priority queue is empty" << std::endl;
	}
	else {
		endOfHeap -= 1;
		swap(0, endOfHeap - &priorityQueue[0]);
		recalcHeapDownwards(0);
	}
}

template<typename E>
void PriorityQueue<E>::push_back(E data, bool(*compare)(E, E))
{
	*(endOfHeap) = data;

	recalcHeap(endOfHeap - &priorityQueue[0], compare);

	if (priorityQueueSize <= endOfHeap - &priorityQueue[0]) {
		std::cout << "priority queue is full call expandQueue() for more space" << std::endl;
	}
	else {
		endOfHeap += 1;
		//std::cout << "current position of end of heap" << endOfHeap - &priorityQueue[0] << std::endl;
	}
}

template<typename E>
void PriorityQueue<E>::pop_back(bool(*compare)(E, E))
{
	if (endOfHeap - &priorityQueue[0] <= 0) {
		std::cout << "priority queue is empty" << std::endl;
	}
	else {
		endOfHeap -= 1;
		//std::cout << "current position of end of heap" << endOfHeap - &priorityQueue[0] << std::endl;
		//std::cout << "element in there:" << priorityQueue[endOfHeap - &priorityQueue[0]] << std::endl;
		swap(0, endOfHeap - &priorityQueue[0]);
		//std::cout << "element in there:" << priorityQueue[endOfHeap - &priorityQueue[0]] << std::endl;
		recalcHeapDownwards(0, compare);
	}
}

template<typename E>
void PriorityQueue<E>::recalcHeap(int currentIndex)
{
	//std::cout << "compare these   " << currentIndex << getParent(currentIndex) << std::endl;
	//std::cout << "with this inside" << priorityQueue[currentIndex] << priorityQueue[getParent(currentIndex)] << std::endl;
	if (priorityQueue[currentIndex] > priorityQueue[getParent(currentIndex)]) {
		swap(currentIndex, getParent(currentIndex));
		//std::cout<<"queue recalculated"<<std::endl;
		recalcHeap(getParent(currentIndex));
	}
}

template<typename E>
void PriorityQueue<E>::recalcHeapDownwards(int currentIndex)
{
	if (priorityQueue[currentIndex] < priorityQueue[getLeftChild(currentIndex)] && priorityQueue[currentIndex] < priorityQueue[getRightChild(currentIndex)]) {
		if (priorityQueue[getLeftChild(currentIndex)] < priorityQueue[getRightChild(currentIndex)]) {
			swap(getRightChild(currentIndex), currentIndex);// swap right with currentIndex
			recalcHeapDownwards(getRightChild(currentIndex));
		}
		else {
			swap(getLeftChild(currentIndex), currentIndex);// swap left with currentIndex
			recalcHeapDownwards(getLeftChild(currentIndex));
		}//std::cout << "left and right were larger than last element" << std::endl;
	}
	else if (priorityQueue[currentIndex] < priorityQueue[getLeftChild(currentIndex)]) {
		swap(getLeftChild(currentIndex), currentIndex);// swap left with currentIndex
		recalcHeapDownwards(getLeftChild(currentIndex));
		//std::cout << "left was larger than last element" << std::endl;
	}
	else if (priorityQueue[getLeftChild(currentIndex)] < priorityQueue[getRightChild(currentIndex)]) {
		swap(getRightChild(currentIndex), currentIndex);// swap right with currentIndex
		recalcHeapDownwards(getRightChild(currentIndex));
		//std::cout << "right was larger than last element" << std::endl;
	}
}

template<typename E>
void PriorityQueue<E>::recalcHeap(int currentIndex, bool(*compare)(E, E))
{
	if (compare(priorityQueue[currentIndex], priorityQueue[getParent(currentIndex)])) {
		swap(currentIndex, getParent(currentIndex));
		recalcHeap(getParent(currentIndex));
	}
}

template<typename E>
void PriorityQueue<E>::recalcHeapDownwards(int currentIndex, bool(*compare)(E, E))
{
	if (compare(priorityQueue[getLeftChild(currentIndex)], priorityQueue[(currentIndex)]) && compare(priorityQueue[getRightChild(currentIndex)], priorityQueue[(currentIndex)])) {
		if (compare(priorityQueue[getRightChild(currentIndex)], priorityQueue[getLeftChild(currentIndex)])) {
			swap(getRightChild(currentIndex), currentIndex);// swap right with currentIndex
			recalcHeapDownwards(getRightChild(currentIndex));
		}
		else {
			swap(getLeftChild(currentIndex), currentIndex);// swap left with currentIndex
			recalcHeapDownwards(getLeftChild(currentIndex));
		}//std::cout << "left and right were larger than last element" << std::endl;
	}
	else if (compare(priorityQueue[getLeftChild(currentIndex)], priorityQueue[(currentIndex)])) {
		swap(getLeftChild(currentIndex), currentIndex);// swap left with currentIndex
		recalcHeapDownwards(getLeftChild(currentIndex));
		//std::cout << "left was larger than last element" << std::endl;
	}
	else if (compare(priorityQueue[getRightChild(currentIndex)], priorityQueue[(currentIndex)])) {
		swap(getRightChild(currentIndex), currentIndex);// swap right with currentIndex
		recalcHeapDownwards(getRightChild(currentIndex));
		//std::cout << "right was larger than last element" << std::endl;
	}
}

template<typename E>
void PriorityQueue<E>::expandQueue()
{
	E arr[2 * priorityQueueSize + 1];
	priorityQueue = arr;
	priorityQueueSize = std::pow(2, priorityQueueHeight + 1) - 1;
	priorityQueueHeight ++;
}

template<typename E>
void PriorityQueue<E>::swap(int index1, int index2)
{
	E temp = priorityQueue[index1];
	priorityQueue[index1] = priorityQueue[index2];
	priorityQueue[index2] = temp;
}

template<typename E>
void PriorityQueue<E>::printQueue()
{
	for (int i = 0; i < (endOfHeap - &priorityQueue[0]); i++) {
		std::cout << priorityQueue[i] << "     ";
	}std::cout << std::endl;
}


bool comparison(int x, int y)
{
	return x > y; // swap if the first element is greater than the second
}


int main() {
	int till[15];
	PriorityQueue<int> tom(4, till);
	tom.push_back(10, comparison);
	std::cout << "10 added:" << std::endl; tom.printQueue();
	tom.push_back(14, comparison);
	std::cout << "14 added:" << std::endl; tom.printQueue();
	tom.push_back(15, comparison);
	std::cout << "15 added:" << std::endl; tom.printQueue();
	tom.push_back(30, comparison);
	std::cout << "30 added:" << std::endl; tom.printQueue();
	tom.push_back(0, comparison);
	std::cout << "0 added:" << std::endl; tom.printQueue();

	std::cout << tom.front(); std::cout << " removed:" << std::endl;
	tom.pop_back(comparison); tom.printQueue();
	std::cout << tom.front(); std::cout << " removed:" << std::endl;
	tom.pop_back(comparison); tom.printQueue();
	std::cout << tom.front(); std::cout << " removed:" << std::endl;
	tom.pop_back(comparison); tom.printQueue();
	std::cout << tom.front(); std::cout << " removed:" << std::endl;
	tom.pop_back(comparison); tom.printQueue();

}