#include "thread_pool/thread_pool.hpp"
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


mutex m_sp;
mutex m_wq;
mutex m_rq;
mutex m_tt;
mutex m_tf;
mutex m_sf;
mutex m_sp_c;
mutex m_vf;
mutex m_if;
mutex m_m1;
mutex m_m2;

// {
//   std::mutex m,
//   std::lock_guard<std::mutex> lockGuard(m_sp);
//   sharedVariable= getVar();
// }
atomic<bool> dones[2];

using namespace std;
using namespace thread_pool;

//define your thread pool here
int num_threads = thread::hardware_concurrency();
ThreadPool tp(num_threads);
// ThreadPool tp{};
int sp_c = 2;
int wr_q = 4;

vector<shared_future<void>> void_futures;
vector<shared_future<int>> int_futures;

//stores the arguments for those functions which are changing them
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};
deque<pair<int, std::function<int()>>> ready_queue;
deque<pair<int, std::function<int()>>> wait_queue;
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
	lock_guard<mutex> lockGuard1(m_m1);
	int flag = true;
		cout << "thread_track_fn\n";
	int sp_done_c = 0;
	while(true)
	{
		// cout << "thread_track_fn\n";
		{
			lock_guard<mutex> lockGuard(m_tt);
			for(auto x:thread_track)
			{
				//update special
				// while(special_changed)cout << "Busy Waiting" << "\n";
				if(x.second)
				{
						//should prolly call .get here - need to get the correct future through an iterator here
						x.second = false;
						lock_guard<mutex> lockGuard(m_sp);
						auto iter_special = find_if(special.begin(), special.end(), Find_special(x.first));
						remove_fn = (*iter_special).second;
						special.erase(iter_special);
						// cout << "Changing Special" << "\n";
						special_changed = 1; //make it 1 only when i remove an arg from special
						// can also remove x from the thread_track vector, that way eliminate iteration through it everytime
						++sp_done_c;
				}
			}
		}
		if(sp_done_c == sp_c) 
		{
			// cout << "EXITING TTF\n";
			break;
		}
		// cout << "Special: " << special.size() << "\n";
	}
}

// schedule threads from queue only when special list gets updated(specifically when there's been a removal)
void scheduling_fn()
{
	lock_guard<mutex> lockGuard1(m_m2);
	// lock_guard<mutex> lockGuard(m_sf);
	bool flag = true;
	int wr_done_c = 0;
		cout << "scheduling_fn\n";
	//special got updated
	while(true)
	{
		// cout << "scheduling_fn\n";
		{
			while(special_changed)
			{
				// if wait queue contains some functions, get only those functions which are dependent on
				// remove_fn which has just got updated
				// how to check for these functions? refer the input data

				//push eligible elements from wait queue to ready queue


				{
					lock_guard<mutex> lockGuard(m_wq);
					for(auto x:wait_queue)
					{
						//pick out every argument from func in x
						//check if it exists in special
						//if it doesnt
						//	move it to ready queue
						bool is_found = false;
						for(auto y:args[x.first - 1])
						{
							lock_guard<mutex> lockGuard(m_sp);
							if(find_if(begin(special), end(special), Find_special2(y)) != end(special))
							{	
								is_found = true;
								break;
							}
						}
						if(!is_found)
						{
							wait_queue.erase(find_if( begin(wait_queue), end(wait_queue), Find_special3<pair<int, std::function<int()>>>(x.first)));
							lock_guard<mutex> lockGuard(m_rq);
							ready_queue.push_back(x);
						}
					}
				}
				special_changed = 0;
			}
		}

		{
			lock_guard<mutex> lockGuard(m_rq);
			if(ready_queue.size() != 0)
			{
				for(auto &x:ready_queue)
				{
					{
						lock_guard<mutex> lockGuard(m_if);
						int_futures.emplace_back(tp.Submit(x.second));
					}

					auto iter = find_if( begin(ready_queue), end(ready_queue), Find_special3<pair<int, std::function<int()>>>(x.first));
					ready_queue.erase(iter);
					++wr_done_c;
					//file output code
					// int_futures.emplace_back(tp.Submit(min, cref(arr1), cref(n)));
				}
			}
		}
		// cout << "Ready Queue: " << ready_queue.size() << "\n";
		// cout << "Special: " << special.size() << "\n";
		// cout << "Wait Queue: " << wait_queue.size() << "\n";
		if(wr_done_c == wr_q) 
		{
			// cout << "EXITING SF\n";
			break;
		}
	}
}

int main(int argc, char **argv)
{
	// int arr1[]{1, 3, 6, -1, 5};
	// int arr2[]{2, 0, 3, 6, 5};
	// int n = sizeof(arr1) / sizeof(arr1[0]);


	lock_guard<mutex> lockGuard1(m_m1);
	lock_guard<mutex> lockGuard2(m_m2);


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


	{
		lock_guard<mutex> lockGuard(m_vf);
		void_futures.emplace_back(tp.Submit(thread_track_fn));
		void_futures.emplace_back(tp.Submit(scheduling_fn));
	}

	using namespace std::chrono_literals;

	// my_sort(arr1, n);
	// if my_sort is writing into one or more of its arguments, add them to special
	// file write code for that
	pair<int,string> p1_1(1,"arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p1_1);
	}
	// atomic bool variable to track the execution of my_sort(arr1, n)
	dones[0] = false;

	{
		lock_guard<mutex> lockGuard(m_vf);
		void_futures.emplace_back(tp.Submit([&] {
			my_sort(arr1, n);
			dones[0] = true;
		}));
	}
	// cout<<tp.thread_ids()[1]<<"\n";

	pair<int, atomic<bool>&> p1_2(1, dones[0]); 

	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p1_2);
	}
	
	
	// int min1 = min(arr1, n);
	int min1 = -1;
	//min does not change any of its arguments
	auto fn2 =  bind(::min, arr1, n);

	//min does depend on one of the arguments in the special array, so add them to wait queue
	vector<pair<int,string>>::iterator iter1, iter2;
	
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if( iter1 != iter2 )
	{
		lock_guard<mutex> lockGuard(m_wq);
		// wait_queue.push_back(pair<int, std::function<int()>>(2, fn2));
		// wait_queue.push_back(pair<int, std::function<void()>>(2, [&](){ min1 = min(arr1, n); } ));
		wait_queue.push_back(pair<int, std::function<int()>>(2, [&]()->int{ return min(arr1, n); } ));
	}
	// push to wait queue
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		// ready_queue.push_back(pair<int, std::function<int()>>(2, fn2));
		// ready_queue.push_back(pair<int, std::function<void()>>(2, [&](){ min1 = min(arr1, n); } ));
		ready_queue.push_back(pair<int, std::function<int()>>(2, [&]()->int{ return min(arr1, n); } ));
	}

	// int max1 = max(arr1, n);
	int max1 = -1;
	auto fn3 = bind(::max, arr1, n);
	
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}

	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		// wait_queue.push_back(pair<int, std::function<int()>>(3, fn3));
		// wait_queue.push_back(pair<int, std::function<void()>>(3, [&](){ max1 = max(arr1, n); } ));
		wait_queue.push_back(pair<int, std::function<int()>>(3, [&]()->int{ return max(arr1, n); } ));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		// ready_queue.push_back(pair<int, std::function<int()>>(3, fn3));
		// ready_queue.push_back(pair<int, std::function<void()>>(3, [&](){ max1 = max(arr1, n); } ));
		ready_queue.push_back(pair<int, std::function<int()>>(3, [&]()->int{ return max(arr1, n); } ));
	}

	// my_sort(arr2, n);
	pair<int,string> p4_1(4,"arr2");
	
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p4_1);
	}

	dones[1] = false;
	{
		lock_guard<mutex> lockGuard(m_vf);
		void_futures.emplace_back(tp.Submit([&] {
			my_sort(arr2, n);
			dones[1] = true;
		}));
	}
	pair<int, atomic<bool>&> p4_2(4, dones[1]);
		
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p4_2);
	}


	// int min2 = min(arr2, n);
	int min2 = -1;
	// if arr2 is found in special vector
	auto fn5 =  bind(::min, arr2, n);

	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}

	if(iter1 != iter2)
	{
		//min to queue
		lock_guard<mutex> lockGuard(m_wq);
		// wait_queue.push_back(pair<int, std::function<int()>>(5, fn5));
		// wait_queue.push_back(pair<int, std::function<void()>>(5, [&](){ min2 = min(arr2, n); } ));
		wait_queue.push_back(pair<int, std::function<int()>>(5, [&]()->int{ return min(arr2, n); } ));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		// ready_queue.push_back(pair<int, std::function<int()>>(5, fn5));
		// ready_queue.push_back(pair<int, std::function<void()>>(5, [&](){ min2 = min(arr2, n); } ));
		ready_queue.push_back(pair<int, std::function<int()>>(5, [&]()->int{ return min(arr2, n); } ));
	}


	// int max2 = max(arr2, n);
	int max2 = -1;
	auto fn6 =  bind(::max, arr2, n);

	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}

	if(iter1 != iter2)
	{
		//min to queue
		lock_guard<mutex> lockGuard(m_wq);
		// wait_queue.push_back(pair<int, std::function<int()>>(6, fn6));
		// wait_queue.push_back(pair<int, std::function<void()>>(6, [&](){ max2 = max(arr2, n); } ));
		wait_queue.push_back(pair<int, std::function<int()>>(6, [&]()->int{ return max(arr2, n); } ));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		// ready_queue.push_back(pair<int, std::function<int()>>(6, fn6));
		// ready_queue.push_back(pair<int, std::function<void()>>(6, [&](){ max2 = max(arr2, n); } ));
		ready_queue.push_back(pair<int, std::function<int()>>(6, [&]()->int{ return max(arr2, n); } ));
	}
















	
	// // int min1 = min(arr1, n);
	// // int min1 = -999999;
	// //min does not change any of its arguments
	// auto fn8 =  bind(::min, arr1, n);

	// //min does depend on one of the arguments in the special array, so add them to wait queue
	// if(find_if(begin(special), end(special), Find_special2("arr1")) != end(special))
	// {
	// 	wait_queue.push_back(pair<int, std::function<int()>>(8, fn8));
	// 	// wait_queue.push_back(pair<int, std::function<void(int)>>(8, [&](){ min1 = fn8(); }));
	// }
	// // push to wait queue
	// else
	// {
	// 	ready_queue.push_back(pair<int, std::function<int()>>(8, fn8));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(8, [&](){ min1 = fn8(); } ));
	// }
	// ++wr_q;

	// // int max1 = max(arr1, n);
	// // int max1 = -9999999;
	// auto fn9 = bind(::max, arr1, n);
	// if(find_if(begin(special), end(special), Find_special2("arr1")) != end(special))
	// {
	// 	wait_queue.push_back(pair<int, std::function<int()>>(9, fn9));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(9, [&](){ max1 = fn9(); }));
	// }
	// else
	// {
	// 	ready_queue.push_back(pair<int, std::function<int()>>(9, fn9));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(9, [&](){ max1 = fn9(); } ));
	// }
	// ++wr_q;

	// // my_sort(arr2, n);


	// // int min2 = min(arr2, n);
	// // int min2 = -99999;
	// // if arr2 is found in special vector
	// auto fn11 =  bind(::min, arr2, n);
	// if(find_if(begin(special), end(special), Find_special2("arr2")) != end(special))
	// {
	// 	//min to queue
	// 	wait_queue.push_back(pair<int, std::function<int()>>(11, fn11));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(11, [&](){ min2 = fn11(); }));
	// }
	// else
	// {
	// 	ready_queue.push_back(pair<int, std::function<int()>>(11, fn11));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(11, [&](){ min2 = fn11(); } ));
	// }
	// ++wr_q;


	// // int max2 = max(arr2, n);
	// // int max2 = -99999;
	// auto fn12 =  bind(::max, arr2, n);
	// if(find_if(begin(special), end(special), Find_special2("arr2")) != end(special))
	// {
	// 	//min to queue
	// 	wait_queue.push_back(pair<int, std::function<int()>>(12, fn12));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(12, [&](){ max2 = fn12(); }));
	// }
	// else
	// {
	// 	ready_queue.push_back(pair<int, std::function<int()>>(12, fn12));
	// 	// ready_queue.push_back(pair<int, std::function<void(int)>>(12, [&](){ max2 = fn12(); } ));
	// }
	// ++wr_q;








	cout<<"DELETING M"<<"\n";

	lockGuard1.~lock_guard();
	lockGuard2.~lock_guard();










	{
		// lock_guard<mutex> lockGuard(m_sf);
		for(auto &x:void_futures)
		{
			// cout << std::boolalpha;
			// cout << x.valid() << "\n";
			// if(x.valid())
			x.wait();
			//x.get();
		}
	}
	// min and max values (called twice after every sort)

	lock_guard<mutex> lockGuard(m_if);
	for(auto &x:int_futures)
	{
		// cout << x.valid() << "\n";
		// if(x.valid())
		// x.wait();
		try
		{
			cout << x.get() << "\n";
		}
		catch(...)
		{
			cout<<"error\n";
			x.wait();
			continue;
		}
	}
	// cout << min1 << "\n\n";
	// cout << max1 << "\n\n";
	// cout << min2 << "\n\n";
	// cout << max2 << "\n\n";

	
	gettimeofday(&stop, NULL);
    printf("took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

	// cout << "TP THREADS : " << tp.thread_ids() << "\n";
	// while ( wait_queue.size() || ready_queue.size() || special.size());
	// tp.~ThreadPool();

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