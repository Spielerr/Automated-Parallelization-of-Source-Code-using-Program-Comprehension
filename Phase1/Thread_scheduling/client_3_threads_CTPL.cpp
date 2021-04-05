#include "CTPL/ctpl_stl.h"
#include <thread>
#include <atomic>
#include <unistd.h>
#include "prog.cpp"
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <mutex>
using namespace std;

//define your thread pool here
int num_threads = thread::hardware_concurrency();
// ThreadPool tp(num_threads);
ctpl::thread_pool tp(num_threads);
// ThreadPool tp{};
int sp_c = 0;
int wr_q = 0;

vector<future<void>> void_futures;
vector<future<int>> int_futures;

//stores the arguments for those functions which are changing them
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};
deque<pair<int, std::function<int(int)>>> ready_queue;
deque<pair<int, std::function<int(int)>>> wait_queue;
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

template< typename T>
class Find_special3
{
	private:
	int x_;

	public:
	Find_special3(int x) : x_(x) {}
	bool operator()(T i)
	{
		return i.first == x_;
	}
};

// class Find_special3
// {
// 	private:
// 	string x_;

// 	public:
// 	Find_special3(string x) : x_(x) {}
// 	bool operator()(string i)
// 	{
// 		if(x_.compare(i) == 0)
// 		{
// 			return true;
// 		}
// 		return false;
// 	}
// };

// int i1 = 10;
// int i2 = 10;
// function to track execution of threads
// whenever any thread finishes execution, update special vector
void thread_track_fn()
{
	int flag = true;
	while(sp_c)
	{
		// cerr << "thread_track_fn\n";
		// cerr<<"ADDING\n\n";
		for(auto x:thread_track)
		{
			//update special
			while(special_changed);
			if(x.second)
			{
				// cerr<<"ADDING\n\n";
					//should prolly call .get here - need to get the correct future through an iterator here
					x.second = false;
					mutex m;
					lock_guard<mutex> lockGuard(m);
					auto iter_special = find_if(special.begin(), special.end(), Find_special(x.first));
					remove_fn = (*iter_special).second;
					special.erase(iter_special);
					special_changed = 1; //make it 1 only when i remove an arg from special
					// can also remove x from the thread_track vector, that way eliminate iteration through it everytime
					--sp_c;
			}
		}
		// cout << "Special: " << special.size() << "\n";
	}
}

// schedule threads from queue only when special list gets updated(specifically when there's been a removal)
void scheduling_fn()
{
	bool flag = true;
	//special got updated
	while(wr_q)
	{
		// cerr << "scheduling_fn\n";
		while(special_changed)
		{
				// cerr<<"ADDING\n\n";
			// if wait queue contains some functions, get only those functions which are dependent on
			// remove_fn which has just got updated
			// how to check for these functions? refer the input data

			//push eligible elements from wait queue to ready queue
			mutex m;
			lock_guard<mutex> lockGuard(m);
			for(auto x:wait_queue)
			{
				//pick out every argument from func in x
				//check if it exists in special
				//if it doesnt
				//	move it to ready queue
				// cerr<<"ADDING\n\n";
				bool is_found = false;
				for(auto y:args[x.first - 1])
				{
					if(find_if(begin(special), end(special), Find_special2(y)) != end(special))
					{	
						is_found = true;
						break;
					}
				}
				if(!is_found)
				{
					wait_queue.erase(find_if( begin(wait_queue), end(wait_queue), Find_special3<pair<int, std::function<int(int)>>>(x.first)));
					ready_queue.push_back(x);
				}
			}
			special_changed = 0;
		}

		if(ready_queue.size() != 0)
		{
			for(auto &x:ready_queue)
			{
				auto f = x.second;
				// cerr<<"ADDING\n\n";
				int_futures.emplace_back(tp.push(f));

				auto iter = find_if( begin(ready_queue), end(ready_queue), Find_special3<pair<int, std::function<int(int)>>>(x.first));
				ready_queue.erase(iter);
				--wr_q;
				//file output code
				// int_futures.emplace_back(tp.push(min, cref(arr1), cref(n)));
			}
		}
		// cerr << "Ready Queue: " << ready_queue.size() << "\n";
		// cerr << "Special: " << special.size() << "special_changed: " << special_changed << "\n";
		// cerr << "Wait Queue: " << wait_queue.size() << "\n";
	}
}

int main(int argc, char **argv)
{
	// int arr1[]{1, 3, 6, -32423, 5};
	// int arr2[]{2, 0, 3, 6, 5};
	// int n = sizeof(arr1) / sizeof(arr1[0]);





	int input_n = atoi(argv[1]);
	int *arr1 = (int *)malloc(input_n * sizeof(int));
    int array_size1 = input_n;
    srand(8);
    for(int i = 0; i < array_size1; ++i)
    {    
        arr1[i] = rand();
    }

	int *arr2 = (int *)malloc(input_n * sizeof(int));
    int array_size2 = input_n;
    srand(2);
    for(int i = 0; i < array_size2; ++i)
    {    
        arr2[i] = rand();
    }

	int n = array_size1;












	cout << "Number of hardware threads available on current system: " << num_threads << "\n\n";

	struct timeval stop, start;
    gettimeofday(&start, NULL);


	void_futures.emplace_back(tp.push([](int){thread_track_fn();}));
	void_futures.emplace_back(tp.push([](int){scheduling_fn();}));

	using namespace std::chrono_literals;

	// my_sort(arr1, n);
	// if my_sort is writing into one or more of its arguments, add them to special
	// file write code for that
	pair<int,string> p1_1(1,"arr1");
	special.push_back(p1_1);
	++sp_c;
	// atomic bool variable to track the execution of my_sort(arr1, n)
	atomic<bool> done1(false);

	void_futures.emplace_back(tp.push([&] (int) {
        my_sort(arr1, n);
        done1 = true;
    }));

	pair<int, atomic<bool>&> p1_2(1, done1); 
	thread_track.push_back(p1_2);
	
	
	// int min1 = min(arr1, n);
	int min1 = -999999;
	//min does not change any of its arguments
	auto fn2 =  bind(::min, arr1, n);

	//min does depend on one of the arguments in the special array, so add them to wait queue
	if(find_if(begin(special), end(special), Find_special2("arr1")) != end(special))
	{
		wait_queue.push_back(pair<int, std::function<int(int)>>(2, fn2));
		// wait_queue.push_back(pair<int, std::function<void(int)>>(2, [&](int){ min1 = fn2(); }));
	}
	// push to wait queue
	else
	{
		ready_queue.push_back(pair<int, std::function<int(int)>>(2, fn2));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(2, [&](int){ min1 = fn2(); } ));
	}
	++wr_q;

	// int max1 = max(arr1, n);
	int max1 = -9999999;
	auto fn3 = bind(::max, arr1, n);
	if(find_if(begin(special), end(special), Find_special2("arr1")) != end(special))
	{
		wait_queue.push_back(pair<int, std::function<int(int)>>(3, fn3));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(3, [&](int){ max1 = fn3(); }));
	}
	else
	{
		ready_queue.push_back(pair<int, std::function<int(int)>>(3, fn3));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(3, [&](int){ max1 = fn3(); } ));
	}
	++wr_q;

	// my_sort(arr2, n);
	pair<int,string> p4_1(4,"arr2");
	special.push_back(p4_1);
	++sp_c;

	atomic<bool> done4(false);
	void_futures.emplace_back(tp.push([&](int) {
        my_sort(arr2, n);
        done4 = true;
    }));
	pair<int, atomic<bool>&> p4_2(4, done4);
	thread_track.push_back(p4_2);


	// int min2 = min(arr2, n);
	int min2 = -99999;
	// if arr2 is found in special vector
	auto fn5 =  bind(::min, arr2, n);
	if(find_if(begin(special), end(special), Find_special2("arr2")) != end(special))
	{
		//min to queue
		wait_queue.push_back(pair<int, std::function<int(int)>>(5, fn5));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(5, [&](int){ min2 = fn5(); }));
	}
	else
	{
		ready_queue.push_back(pair<int, std::function<int(int)>>(5, fn5));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(5, [&](int){ min2 = fn5(); } ));
	}
	++wr_q;


	// int max2 = max(arr2, n);
	int max2 = -99999;
	auto fn6 =  bind(::max, arr2, n);
	if(find_if(begin(special), end(special), Find_special2("arr2")) != end(special))
	{
		//min to queue
		wait_queue.push_back(pair<int, std::function<int(int)>>(6, fn6));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(6, [&](int){ max2 = fn6(); }));
	}
	else
	{
		ready_queue.push_back(pair<int, std::function<int(int)>>(6, fn6));
		// ready_queue.push_back(pair<int, std::function<void(int)>>(6, [&](int){ max2 = fn6(); } ));
	}
	++wr_q;

	for(auto &x:void_futures)
	{
		x.wait();
	}

	// min and max values (called twice after every sort)
	for(auto &x:int_futures)
	{
		cout<<x.get()<<"\n\n";
	}



	
	gettimeofday(&stop, NULL);
    printf("took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);





	// cout << min1 << "\n\n";
	// cout << max1 << "\n\n";
	// cout << min2 << "\n\n";
	// cout << max2 << "\n\n";
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