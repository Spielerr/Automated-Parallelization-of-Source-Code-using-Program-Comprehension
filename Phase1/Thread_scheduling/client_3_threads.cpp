#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <queue>
#include <atomic>
#include <bits/stdc++.h>
#include "prog.cpp"

using namespace std;

vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
queue<pair<int, string>> ready_queue;
queue<pair<int, string>> wait_queue;

// vector<pair<int, int>> special_changed;
atomic<int> special_changed(0);
string add_remove;

// function to track execution of threads
// whenever any thread finishes execution, update special vector
void thread_track_fn()
{
	int index = 0;
	while(true)
	{
		if(index == 6)
		{
			index = 0;
		}
		for(int i = 0; i<6; i++)
		{
			//update special
			if(thread_track[i].second == true)
			{
				auto iter_special = find(special.begin(), special.end(), thread_track[i].first);
				add_remove = (*iter_special).second;
				special.erase(iter_special);
				special_changed = 1;
			}
		}	
	}
}

// schedule threads from queue only when special list gets updated
void scheduling_fn()
{
	//special got updated
	if(special_changed)
	{
		//note all fns with same arguments as add_remove
		//push these functions into ready queue

		//if threads are available, empty the ready queue
		//assuming threads are available

		special_changed = 0;
	}
}

int main()
{
	int arr1[]{2, 1, 3, 6, 5};
	int arr2[]{2, 0, 3, 6, 5};
	int n = sizeof(arr1) / sizeof(arr1[0]);

	//define your thread pool here

	//we know the number of fn calls
	//initialise thread_track_changed to all 0 signifying that nothing has changed
	// for(int i = 0; i<6;i++)
	// {
	// 	thread_track_changed[i] = 0;
	// }

	using namespace std::chrono_literals;

	my_sort(arr1, n);
	// if my_sort is writing into one or more of its arguments, add them to special
	// file write code for that
	pair<int,string> p1_1(1,"arr1");
	special.push_back(p1_1);
	// thread th1 = thread(my_sort, arr1, n);
	atomic<bool> done1(false);
	thread t1([&] {
        my_sort(arr1, n);
        done1 = true;
    });
	pair<int, atomic<bool>&> p1_2(1, done1); //problem here since i cannot store a reference in a pair
	thread_track.push_back(p1_2);
	
	int min1 = min(arr1, n);
	//min does not change any of its arguments
	if(find(begin(special), end(special), "arr1") != end(special))
	{
		//min to queue
		wait_queue.push(pair<int, string>(2,"min"));
	}
	else
	{
		ready_queue.push(pair<int, string>(2,"min"));
	}

	int max1 = max(arr1, n);
	if(find(begin(special), end(special), "arr1") != end(special))
	{
		//min to queue
		wait_queue.push(pair<int, string>(3,"max"));
	}
	else
	{
		ready_queue.push(pair<int, string>(3,"max"));
	}

	my_sort(arr2, n);
	pair<int,string> p4_1(4,"arr2");
	special.push_back(p4_1);
	// thread th1 = thread(my_sort, arr1, n);
	atomic<bool> done4(false);
	thread t4([&] {
        my_sort(arr2, n);
        done1 = true;
    });
	pair<int, atomic<bool>&> p4_2(1, done1);
	thread_track.push_back(p4_2);


	int min2 = min(arr2, n);
	if(find(begin(special), end(special), "arr2") != end(special))
	{
		//min to queue
		wait_queue.push(pair<int, string>(5,"min"));
	}
	else
	{
		ready_queue.push(pair<int, string>(5,"min"));
	}


	int max2 = max(arr2, n);
	if(find(begin(special), end(special), "arr2") != end(special))
	{
		//min to queue
		wait_queue.push(pair<int, string>(6,"min"));
	}
	else
	{
		ready_queue.push(pair<int, string>(6,"min"));
	}

	return 0;
}

// thread th1 = thread(min, arr1, n);
/*
#include <thread> 
#include <future> int func() { cout << "fn executing\n"; return 1; } 
std::future<int> ret = std::async(&func);  //does create a thread and executes the fn func
int i = ret.get();
cout << i << '\n';
*/