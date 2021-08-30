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
using namespace std;
using namespace thread_pool;
	
int num_threads = thread::hardware_concurrency();
ThreadPool tp(num_threads);
int sp_c = 2;
int wr_q = 4;
vector<shared_future<void>> void_futures;
vector<shared_future<int>> int_futures;
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};
deque<pair<int, std::function<int()>>> ready_queue;
deque<pair<int, std::function<int()>>> wait_queue;
atomic<int> special_changed(0);
string remove_fn;

mutex m_sp;
mutex m_wq;
mutex m_rq;
mutex m_tt;
mutex m_tf;
mutex m_sf;
mutex m_sp_c;
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

void thread_track_fn()
{
	int flag = true;
	int sp_done_c = 0;
	while(true)
	{
		{
			lock_guard<mutex> lockGuard(m_tt);
			for(auto x:thread_track)
			{
				while(special_changed);
				if(x.second)
				{
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
			cout << "EXITING TTF\n";
			break;
		}
	}
}

void scheduling_fn()
{
	bool flag = true;
	int wr_done_c = 0;
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
					int_futures.emplace_back(tp.Submit(x.second));

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
			cout << "EXITING SF\n";
			break;
		}
	}
}

int main(int argc, char **argv)
{
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

	struct timeval stop, start;
    gettimeofday(&start, NULL);

	void_futures.emplace_back(tp.Submit(thread_track_fn));
	void_futures.emplace_back(tp.Submit(scheduling_fn));

	using namespace std::chrono_literals;
	vector<pair<int,string>>::iterator iter1, iter2;
	

	pair<int,string> p1_1(1, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p1_1);
	}
	atomic<bool> done1(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_sort(arr1, n);
		done1 = true;}));
	pair<int, atomic<bool>&> p_th_1(1, done1);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_1);
	}

	auto fn2 = bind(::min, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(2, fn2));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(2, fn2));
	}
	auto fn3 = bind(::max, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(3, fn3));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(3, fn3));
	}
	pair<int,string> p4_1(4, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p4_1);
	}
	atomic<bool> done4(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_sort(arr2, n);
		done4 = true;}));
	pair<int, atomic<bool>&> p_th_4(4, done4);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_4);
	}

	auto fn5 = bind(::min, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(5, fn5));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(5, fn5));
	}
	auto fn6 = bind(::max, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(6, fn6));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(6, fn6));
	}
	for(auto &x:void_futures)
	{
		x.wait();
		x.get();
	}
	for(auto &x:int_futures){
		x.wait();
		cout << std::boolalpha;
		cout << x.valid() << "\n";
		if(x.valid())
		cout << x.get() << "\n";
	}

	gettimeofday(&stop, NULL);
    printf("took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

	return 0;
}

