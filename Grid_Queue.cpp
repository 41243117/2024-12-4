#include <iostream>
using namespace std;

template <class T>
class Queue {  // A finite with zero or more elements.
   public:
	Queue(int queueCapacity = 10);
	// Create an empty queue whose initial capacity is queueCapacity
	bool IsEmpty() const;
	// If number f elements in the queue is 0, return true else return false.
	T& Front() const;
	// Return the elements at the front of the queue.
	T& Rear() const;
	// Return the element at the rear of the queue.
	void Push(const T& item);
	// Insert item at the rear of the queue.
	void Pop();
	// Delete the front element of the queue.

   private:
	T* queue;      // array for queue elements
	int front,     // one counterclockwise from front
	    rear,      // array position of rear element
	    capacity;  // capacity of queue array
};

template<class T>
Queue<T>::Queue(int queueCapacity) :capacity(queueCapacity) {
	if (capacity < 1)throw"Queue capacity must be > 0";
	queue = new T[capacity];
	front = rear = 0;
}

template<class T>
inline bool Queue<T>::IsEmpty() const{
	return front == rear;
}

template<class T>
inline T& Queue<T>::Front() const{
	if (IsEmpty())throw"Queue is empty.No front element.";
	return queue[(front + 1) % capacity];
}

template<class T>
inline T& Queue<T>::Rear()const {
	if (IsEmpty())throw"Queue is empty.No rear element.";
	return queue[rear];
}

template<class T>
void Queue<T>::Push(const T& x) {
	if ((rear + 1) % capacity == front) {
		T* newQueue = new T[2 * capacity];
		int start = (front + 1) % capacity;
		if (start < 2)copy(queue + start, queue + start + capacity - 1, newQueue);
		else {
			copy(queue + start, queue + capacity, newQueue);
			copy(queue, queue + rear + 1, newQueue + capacity - start);
		}
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}
	rear = (rear + 1) % capacity;
	queue[rear] = x;
}

template<class T>
void Queue<T>::Pop() {
	if (IsEmpty())throw"Queue is empty,cannot delete.";

	front = (front + 1) % capacity;
	queue[front].~T();
}

bool checkInGrid(int M, int N, int row, int col) {
	return (row >= 0 && col >= 0 && row < M && col < N);
}

// the idea is to use bfs to paint the cell with value 1 starting from (row, col)
void floodFill(int** grid, int M, int N, int row, int col) {
	// standard bfs
	Queue<int> que;
	int index = row * N + col;
	que.Push(index);
	while (!que.IsEmpty()) {
		index = que.Front();
		que.Pop();
		int q_row = index / N;
		int q_col = index % N;
		grid[q_row][q_col] = 2;

		// after painting the cell at (row, col), we try four different directions
		int direction_col[4] = {-1, 0, 0, 1};
		int direction_row[4] = {0, 1, -1, 0};
		for (int i = 0; i < 4; i++) {
			int next_row = q_row + direction_row[i];
			int next_col = q_col + direction_col[i];
			if (checkInGrid(M, N, next_row, next_col) && grid[next_row][next_col] == 1) {
				int next_index = next_row * N + next_col;
				que.Push(next_index);
				grid[next_row][next_col] = 2;
			}
		}
	}
}

int numIslands(int** grid, int M, int N) {
	int result = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (grid[i][j] == 1) {  // if it is land
				floodFill(grid, M, N, i, j);
				result++;
			}
		}
	}
	return result;
}

int main() {
	int M, N;
	// int grid[300][300];
	while (cin >> M >> N) {
		// Create grid
		int** grid = new int*[M];
		for (int i = 0; i < M; i++) {
			grid[i] = new int[N];
			for (int j = 0; j < N; j++) {
				cin >> grid[i][j];
			}
		}
		// cout << numIslands((int**)grid, M, N) << endl;
		cout << numIslands(grid, M, N) << endl;
		for (int i = 0; i < M; i++) {
			delete[] grid[i];
		}
		delete[] grid;
	}
}
