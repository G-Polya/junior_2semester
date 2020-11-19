//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 1                       ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "ptyqueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int priority,              // Task's priority
        arrived;               // Time when task was enqueued

	void setPty(int newPty)
	{
		priority = newPty;
	}   // Set the priority

    int pty () const
    { 
		return priority; 
	}   // Returns the priority

};

//--------------------------------------------------------------------

int getRandom(int n) {
    // 0부터 n-1까지의 랜덤한 수를 리턴하는 함수
    return rand() % n;
}

int getMax(int waits[],int size)
{
	int max = waits[0];

	for (int i = 1; i < size; i++)
	{
		if (max < waits[i])
			max = waits[i];
	}

	return max;
}


void main ()
{
    PtyQueue<TaskData> taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals;             // Number of new tasks arriving

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;


	srand(500);
	int* low_waits = new int[simLength];
	int* high_waits = new int[simLength];
	int lowIndex = 0;
	int highIndex = 0;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
		
        // Dequeue the first task in the queue (if any).
		cout << "Current minute = " << minute << endl;
		
		if (!taskPQ.isEmpty())
		{
			task = taskPQ.dequeue();
			cout << "Task Dequeued" << endl;
			cout << "This task's priority : " << task.pty() << endl;
			cout << "This task was arrived at " << task.arrived << ", and waited for " 
				 << (minute - task.arrived) << endl;

			if (task.pty() == 0)
			{
				low_waits[lowIndex] = (minute - task.arrived);
				lowIndex++;
			}
			else if (task.pty() == 1)
			{
				high_waits[highIndex] = (minute - task.arrived);
				highIndex++;
			}
		}

		// Determine the number of new tasks and add them to
		// the queue.
		numArrivals = getRandom(4);

		if (numArrivals == 0 || numArrivals == 3)
		{
			cout << "No task was added this time" << endl;
			taskPQ.showStructure();
			cout << endl;
		}
		else if ((1 <= numArrivals) && (numArrivals <= 2))
		{
			cout << "Adding " << numArrivals << " tasks" << endl;
			for (int j = 0; j < numArrivals; j++)
			{
				TaskData temp;
				temp.priority = rand() % numPtyLevels;
				temp.arrived = minute;
				taskPQ.enqueue(temp);
			}

			taskPQ.showStructure();
			cout << endl;
		}
				        
    }

	cout << "Longest wait for any low-priority(0) task : " << getMax(low_waits, simLength) << endl;
	cout << "Longest wait for any high-priority(1) task : " << getMax(high_waits, simLength) << endl;

	delete[] low_waits;
	delete[] high_waits;
}
