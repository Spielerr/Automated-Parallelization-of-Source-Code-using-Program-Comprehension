#include <bits/stdc++.h>
#include "thread_pool/thread_pool.hpp"
#include <thread>
#include <atomic>
#include "prog.cpp"

using namespace std;
using namespace thread_pool;

//define your thread pool here
// int num_threads = thread::hardware_concurrency();
ThreadPool tp{};

vector<future<void>> void_futures;
vector<future<int>> int_futures;

//stores the arguments for those functions which are changing them
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
deque<pair<int, string>> ready_queue;
deque<pair<int, string>> wait_queue;
atomic<int> special_changed(0);
string remove_fn;

class Find_special
{
	private:
	int x_;

	public:
	Find_special(int x) : x_(x) {}
	bool operator()(pair<int, string> i)
	{
		return i.first == x_;
	}
};

class Find_special2
{
	private:
	string x_;

	public:
	Find_special2(string x) : x_(x) {}
	bool operator()(pair<int, string> i)
	{
		if(x_.compare(i.second) == 0)
		{
			return true;
		}
		return false;
	}
};


// function to track execution of threads
// whenever any thread finishes execution, update special vector
void thread_track_fn()
{
	while(true)
	{
		for(auto x:thread_track)
		{
			//update special
			if(x.second)
			{
				//should prolly call .get here - need to get the correct future through an iterator here
				x.second = false;
				auto iter_special = find_if(special.begin(), special.end(), Find_special(x.first));
				remove_fn = (*iter_special).second;
				special.erase(iter_special);
				special_changed = 1; //make it 1 only when i remove an arg from special
			}
		}
	}
}

// schedule threads from queue only when special list gets updated(specifically when there's been a removal)
void scheduling_fn()
{

	//special got updated
	while(true)
	{
		// if(ready_queue is not empty)
		// {
		// 	push functions inside ready_queue into threadpool
		// }
		if(ready_queue.size() != 0)
		{
			for(auto x:ready_queue)
			{
				// int_futures.emplace_back(thread_pool.Submit(x.second));
				//file output code
				// fprintf("int_futures.emplace_back(thread_pool.Submit("+x.second+"));");
				// output right here saldkfjsdalkfjsldkf fn_name
				// int_futures.emplace_back(tp.Submit(min, cref(arr1), cref(n)));
			}
		}
		while(special_changed)
		{
			//check if there's something in ready queue
			// if nothing is there, get stuff(if any, and only those that are dependent) from wait queue

			// if wait queue contains some functions, get only those functions which are dependent on
			// remove_fn which has just got updated
			// how to check for these functions? refer the input data

			// emplace_back them into corresponding futures vector
			// when do you call .get on these functions?

			//push eligible elements from wait queue to ready queue
			for(auto x:wait_queue)
			{
				//pick out every argument from func in x
				//check if it exists in special
				//if it doesnt
				//	move it to ready queue
			}
			special_changed = 0;
		}
	}
}

int main()
{
	int arr1[]{2, 1, 3, 6, 5};
	int arr2[]{2, 0, 3, 6, 5};
	int n = sizeof(arr1) / sizeof(arr1[0]);

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

	void_futures.emplace_back(tp.Submit(thread_track_fn));
	void_futures.emplace_back(tp.Submit(scheduling_fn));
	atomic<bool> done1(false);

	void_futures.emplace_back(tp.Submit([&] {
        my_sort(arr1, n);
        done1 = true;
    }));


	pair<int, atomic<bool>&> p1_2(1, done1); 
	thread_track.push_back(p1_2);
	
	int min1 = min(arr1, n);
	//min does not change any of its arguments
	if(find_if(begin(special), end(special), Find_special2("arr1")) != end(special))
	{
		//min to queue
		wait_queue.push_back(pair<int, string>(2,"min"));
	}
	else
	{
		ready_queue.push_back(pair<int, string>(2,"min"));
	}

	int max1 = max(arr1, n);
	if(find_if(begin(special), end(special), Find_special2("arr1")) != end(special))
	{
		//min to queue
		wait_queue.push_back(pair<int, string>(3,"max"));
	}
	else
	{
		ready_queue.push_back(pair<int, string>(3,"max"));
	}

	my_sort(arr2, n);
	pair<int,string> p4_1(4,"arr2");
	special.push_back(p4_1);
	// thread th1 = thread(my_sort, arr1, n);
	atomic<bool> done4(false);
	void_futures.emplace_back(tp.Submit([&] {
        my_sort(arr2, n);
        done4 = true;
    }));
	pair<int, atomic<bool>&> p4_2(1, done1);
	thread_track.push_back(p4_2);


	int min2 = min(arr2, n);
	// if arr2 is found in special vector
	if(find_if(begin(special), end(special), Find_special2("arr2")) != end(special))
	{
		//min to queue
		wait_queue.push_back(pair<int, string>(5,"min"));
	}
	else
	{
		ready_queue.push_back(pair<int, string>(5,"min"));
	}


	int max2 = max(arr2, n);
	if(find_if(begin(special), end(special), Find_special2("arr2")) != end(special))
	{
		//min to queue
		wait_queue.push_back(pair<int, string>(6,"min"));
	}
	else
	{
		ready_queue.push_back(pair<int, string>(6,"min"));
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