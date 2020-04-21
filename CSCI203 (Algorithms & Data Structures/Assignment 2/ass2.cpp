/*
	Assignment 2 - Supermarket Discrete Event Simulation
	James Dorevski
	jd107
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define SERVER_HEAP_SIZE avaliableServers[0]
#define ROOT 1
#define MAX_SERVER_SIZE 20

// global variables
int customersServedTotal = 0;

struct CustomerRecord {
	double arrivalTime;
	double tallyTime;
	bool paymentMethod; // true: cash, false: card
};

struct Event {
	double eventTime;
	double tallyTime;
	bool paymentMethod;
	int serverIndex; // index of server serving the customers, or -1 for arrival event, or -2 for end of file
};

struct Server {
	double efficiencyFactor;
	int customersServed;
	double idleTime;
	double finishTime;
};

// to swap server indexes
void swapNode(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp; 
}

// circular queue
class CustomerQueue {
private:
	int front;
	int rear;
	int capacity;
	CustomerRecord *circularQueue;
	void resizeQueue();

public:
	int longestQueueLength;
	int totalCustomersQueued;
	double timeSpentQueued;
	double timeLastInsertion;
	double averageQueueLength;

	// initialise queue
	CustomerQueue();
	~CustomerQueue() { delete[] circularQueue; }

	void enqueue(CustomerRecord newRecord); // insert a record at the rear of the queue
	CustomerRecord dequeue(); // pop the record off the front 
	double calcAverageQueueLength(double eventTime);
	bool isEmpty() { return front == rear; }
};

CustomerQueue::CustomerQueue() {
	front = 0;
	rear = 0;
	capacity = 2; // starts low size to save memory if the circular queue isn't needed
 	circularQueue = new CustomerRecord[capacity];

 	longestQueueLength = 0;
	totalCustomersQueued = 0;
	timeSpentQueued = 0.0;
	timeLastInsertion = 0.0;
	averageQueueLength = 0.0;
}

void CustomerQueue::resizeQueue() {
	CustomerRecord *newQueue = new CustomerRecord[capacity * 2];
	int newFront = 0;
	int newRear = 0;

	// copy old data to the new queue
	while (front < rear) {
		newQueue[newRear++] = circularQueue[front++ % capacity]; // dequeues into the new queue
	}

	front = newFront;
	rear = newRear;
	capacity *= 2;
	delete[] circularQueue;
	circularQueue = newQueue;
}

void CustomerQueue::enqueue(CustomerRecord newRecord) {
	if (((front % capacity) == (rear % capacity)) && front != rear) { // checks if queue is full
		resizeQueue();
	}

	// recalculate the average length as the size of the queue has changed
	averageQueueLength += (rear - front) * (newRecord.arrivalTime - timeLastInsertion);
	timeLastInsertion = newRecord.arrivalTime;

	circularQueue[rear++ % capacity] = newRecord;

	int currentLength = rear - front;
	if (currentLength > longestQueueLength) {
		longestQueueLength = currentLength;
	}

	totalCustomersQueued++;
}

CustomerRecord CustomerQueue::dequeue() {
	return circularQueue[front++ % capacity];
}

// finalises the average length for output
double CustomerQueue::calcAverageQueueLength(double finishTime) {
	averageQueueLength += (rear - front) * (finishTime - timeLastInsertion);
	averageQueueLength /= finishTime;

	return averageQueueLength;
}

// min-heap sorted by time
class EventPriorityQueue {
private:
	int heapSize;

public:
	Event events[MAX_SERVER_SIZE + 2]; // for each server active and the next arrival

	EventPriorityQueue(ifstream &in);
	Event readEvent(ifstream &in);
	void insertNode(Event newNode);
	void siftNodeUp(int currentNodeIndex);
	void siftNodeDown(int currentNodeIndex);
	void swapNode(Event &x, Event &y);
	Event removeRoot();
	bool isEmpty() { return heapSize == 0; }
};

EventPriorityQueue::EventPriorityQueue(ifstream &in) {
	heapSize = 0;
	insertNode(readEvent(in)); // reads the first customer
}

Event EventPriorityQueue::readEvent(ifstream &in) {
	Event arrivalEvent;
	string payment;	
	arrivalEvent.serverIndex = -1; // arrival event
	in >> arrivalEvent.eventTime >> arrivalEvent.tallyTime >> payment;

	if (payment.compare("cash") == 0) {
		arrivalEvent.paymentMethod = true;
	} else {
		arrivalEvent.paymentMethod = false;
	}	

	if (in.eof()) {
		arrivalEvent.serverIndex = -2; // let's the finite state machine know the file has ended
	}

	return arrivalEvent;
}

void EventPriorityQueue::insertNode(Event newNode) {
	if (heapSize >= MAX_SERVER_SIZE + 2) {
		cerr << "Heap is full." << endl;
		exit(1);
	}

	events[++heapSize] = newNode;
	siftNodeUp(heapSize);
}

void EventPriorityQueue::siftNodeUp(int currentNodeIndex) {
	if (currentNodeIndex == ROOT) {
		return;
	}

	int parentNodeIndex = currentNodeIndex / 2;

	if (events[parentNodeIndex].eventTime < events[currentNodeIndex].eventTime) {
		return;
	} else {
		swapNode(events[parentNodeIndex], events[currentNodeIndex]);
		siftNodeUp(parentNodeIndex);
	}
}

void EventPriorityQueue::siftNodeDown(int currentNodeIndex) {
	int bestChild = currentNodeIndex * 2;

	if (bestChild > heapSize) {
		return;
	}

	// check if right child exists and if its more efficient than left
	if ((bestChild + 1) <= heapSize) {
		if (events[bestChild + 1].eventTime < events[bestChild].eventTime) {
			bestChild++;
		}
	}

	if (events[bestChild].eventTime < events[currentNodeIndex].eventTime) {
		swapNode(events[bestChild], events[currentNodeIndex]);
		siftNodeDown(bestChild);
	}
}

void EventPriorityQueue::swapNode(Event &x, Event &y) {
	Event temp = x;
	x = y;
	y = temp; 
}

Event EventPriorityQueue::removeRoot() {
	if (isEmpty()) {
		cerr << "Heap is empty therefore cannot remove anything. Critical error." << endl;
		exit(1);
	}
	
	// root is 1
	Event e = events[ROOT]; 
	swapNode(events[ROOT], events[heapSize--]);
	siftNodeDown(ROOT);

	return e;
}

// min-heap based on smallest efficiencyFactor 
class ServerArray {
public:
	Server allServers[MAX_SERVER_SIZE];
	int heapSize;

	ServerArray(ifstream &in);
	void insertNode(int index);
	void siftUp(int currentNode);
	void siftDown(int currentNode);
	int removeRootIndex();
	double getEfficiency(int index);
	bool isEmpty();

private:
	// virtual heap used to directly access the servers without actually removing them from the heap
	int avaliableServers[MAX_SERVER_SIZE + 1]; // heap maths starts at 1 so 0 index should be empty
};

ServerArray::ServerArray(ifstream &in) {
	int serverCount;
	in >> serverCount;

	if (serverCount > MAX_SERVER_SIZE) {
		cerr << "Exceeded server limit of 20. Exiting program." << endl;
		exit(1); 
	}

	heapSize = serverCount;
	avaliableServers[0] = 0;

	// add servers and sort them by efficiency using the min-heap
	for (int i = 0; i < serverCount; i++) {
		in >> allServers[i].efficiencyFactor;   
		allServers[i].finishTime = 0.0;
		allServers[i].idleTime = 0.0;
		allServers[i].customersServed = 0;
		insertNode(i); // insert server index into heap
	}
}

void ServerArray::insertNode(int index) {
	if (SERVER_HEAP_SIZE >= MAX_SERVER_SIZE + 1) {
		cerr << "Heap is full." << endl;
		exit(1);
	}

	avaliableServers[++SERVER_HEAP_SIZE] = index;
	siftUp(SERVER_HEAP_SIZE);
}

void ServerArray::siftUp(int currentNode) {
	if (currentNode == ROOT) {
		return;
	}

	int parentNode = currentNode / 2;

	if (allServers[avaliableServers[parentNode]].efficiencyFactor < allServers[avaliableServers[currentNode]].efficiencyFactor) {
		return;
	} else {
		swapNode(avaliableServers[currentNode], avaliableServers[parentNode]);
		siftUp(parentNode);
	}
}

void ServerArray::siftDown(int currentNode) {
	int bestChild = currentNode * 2;

	if (bestChild > SERVER_HEAP_SIZE) {
		return; 
	}

	if ((bestChild + 1) <= SERVER_HEAP_SIZE) {
		if (allServers[avaliableServers[bestChild + 1]].efficiencyFactor < allServers[avaliableServers[bestChild]].efficiencyFactor) {
			bestChild++;
		}
	}

	if (allServers[avaliableServers[bestChild]].efficiencyFactor < allServers[avaliableServers[currentNode]].efficiencyFactor) {
		swapNode(avaliableServers[currentNode], avaliableServers[bestChild]);
		siftDown(bestChild);
	}
}

int ServerArray::removeRootIndex() {
	if (SERVER_HEAP_SIZE == 0) {
		cerr << "Heap is empty therefore cannot remove anything. Critical error." << endl;
		exit(1);
	}

	int serverIndex = avaliableServers[ROOT];
	swapNode(avaliableServers[ROOT], avaliableServers[SERVER_HEAP_SIZE--]);
	siftDown(ROOT);

	return serverIndex;
}

double ServerArray::getEfficiency(int index) {
	return allServers[index].efficiencyFactor;
}

bool ServerArray::isEmpty() {
	return SERVER_HEAP_SIZE == 0;
}

double calcPaymentTime(bool paymentMethod) {
	if (paymentMethod == true) {
		return 0.3;
	} else {
		return 0.7;
	}
}

int main() {
	ifstream in("ass2.txt");

	if (!in.good()) {
		cerr << "ass2.txt not found. Exiting program." << endl;
		exit(1);
	}

	// declare data structures
	ServerArray servers = ServerArray(in); // reads servers
	EventPriorityQueue events = EventPriorityQueue(in); // reads first event
	CustomerQueue customers;

	Event currentEvent;
	while (!events.isEmpty()) { // there are still events to be processed
		currentEvent = events.removeRoot(); // get the next event off the heap
		if (currentEvent.serverIndex == -1) {// if the event is a customer arrival
			if (!servers.isEmpty()) { // if there is a server avaliable
				int currentServerIndex = servers.removeRootIndex();
				double serviceTime = (currentEvent.tallyTime * servers.getEfficiency(currentServerIndex)) + calcPaymentTime(currentEvent.paymentMethod);

				// adding the server finish event to the queue
				Event serverFinish;
				serverFinish.eventTime = currentEvent.eventTime + serviceTime;
				serverFinish.serverIndex = currentServerIndex;
				events.insertNode(serverFinish);

				// update server's stats
				servers.allServers[currentServerIndex].idleTime += currentEvent.eventTime - servers.allServers[currentServerIndex].finishTime;
			} else { // all the servers are in use so add the customer to the queue
				CustomerRecord customerWaiting;
				customerWaiting.arrivalTime = currentEvent.eventTime;
				customerWaiting.tallyTime = currentEvent.tallyTime;
				customerWaiting.paymentMethod = currentEvent.paymentMethod;
				customers.enqueue(customerWaiting);				
			}
			
			Event nextArrival = events.readEvent(in); // reading in next customer from file
			if (nextArrival.serverIndex != -2) { // checking flag to ensure the end of file hasn't been reached
				events.insertNode(nextArrival);
			}
		} else { // current event is a server finish
			if (!customers.isEmpty()) { // if customer queue isn't empty
				CustomerRecord nextCustomer = customers.dequeue();
				int currentServerIndex = currentEvent.serverIndex;
				double serviceTime = (nextCustomer.tallyTime * servers.getEfficiency(currentServerIndex)) + calcPaymentTime(nextCustomer.paymentMethod);
				Event serverFinish;
				serverFinish.eventTime = currentEvent.eventTime + serviceTime;
				serverFinish.serverIndex = currentServerIndex;
				events.insertNode(serverFinish);

				customers.timeSpentQueued += currentEvent.eventTime - nextCustomer.arrivalTime;
			} else { // no customers to serve
				servers.insertNode(currentEvent.serverIndex); // add server back to heap as it's avaliable
				servers.allServers[currentEvent.serverIndex].finishTime = currentEvent.eventTime;
			}

			servers.allServers[currentEvent.serverIndex].customersServed++;
			customersServedTotal++;
		}
	}

	in.close();

	// finalise stats
	double averageWaitingTime = (customers.timeSpentQueued / customers.totalCustomersQueued);
	double percentageNoWait = ((customersServedTotal - customers.totalCustomersQueued) / (double) customersServedTotal) * 100;

	// print stats
	cout << "Number of customers served: " << customersServedTotal << endl;
	cout << "Time taken to serve all customers: " << currentEvent.eventTime << endl;
	cout << "Greatest length reached by the customer queue: " << customers.longestQueueLength << endl;
	cout << "Average length of the customer queue: " << customers.calcAverageQueueLength(currentEvent.eventTime) << endl;
	cout << "Average customer waiting time in queue: " << averageWaitingTime << endl;
	cout << "Percentage of customers with zero waiting time: " << percentageNoWait << "%" << endl;
	cout << endl;
	cout << setw(6) << "Server" << setw(13) << "Efficiency" << setw(20) << "Customers served" << setw(20) << "Time spent idle" << endl;
	for (int i = 0; i < servers.heapSize; i++) {
		servers.allServers[i].idleTime += currentEvent.eventTime - servers.allServers[i].finishTime;
		cout << setw(6) << i << setw(13) << servers.allServers[i].efficiencyFactor << setw(20) << servers.allServers[i].customersServed << setw(20) << servers.allServers[i].idleTime << endl;
	}

	return 0;
}

/* 
	Data Structures used: 
		- CustomerQueue - Circular Queue
		- EventPriorityQueue - Min-heap 
		- ServerArray - Min-heap

	Using a queue for the CustomerQueue allows for O(log n) insertions.

	A finite state machine was used to handle the event cases. 
	
	The ServerArray and Event Queue are enhanced by using a min-heap to find the next event/most efficient server instead of a linear search.
	Introducing the heap allows for O(1) lookup times compared to linear search's O(n). 

	Creating a second int array in the ServerArray which holds the indexes of each server in the heap allows for 
	heap operations to be performed using just the index instead of the actual server objects, so instead of removing the whole
	Server object when your trying to access the most efficient server, you would just remove the index to the 
	most efficient server and directly access and modify it in the allServers array, saving you from creating another Server object. 
*/
