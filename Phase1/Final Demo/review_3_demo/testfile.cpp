// parallel algorithm

#include "thread_pool/thread_pool.hpp"
#include <thread>
#include <atomic>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <mutex>
using namespace std;
using namespace thread_pool;
	

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

double mean(const int* a1, int n1)
{
	double mean = 0;
	for(int i = 0;i < n1;++i)
	{
		mean += a1[i];
	}
	mean /= n1;
	return mean;
}

void sort(int* arr,const int arr_n)
{
	for(int i = 0;i < arr_n-1;++i)
	{
		int min = i;
		for(int j = i+1;j < arr_n;++j)
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}


int my_max(int* a4, int n4)
{
	int max = a4[0];
	for(int i = 1; i < n4; ++i)
	{
		if(a4[i]>max)
		{
			max = a4[i];
		}
	}

	printf("Max : %d\n", max);
	return 1;
}

int my_min(int* a4, int n4)
{
	int min = a4[0];
	for(int i = 1; i<n4; ++i)
	{
		if(a4[i]<min)
		{
			min = a4[i];
		}
	}

	printf("Min : %d\n", min);
	return 1;
}



int num_threads = thread::hardware_concurrency();
ThreadPool tp(num_threads);
int sp_c = 12;
int wr_q = 24;
vector<shared_future<void>> void_futures;
vector<shared_future<int>> int_futures;
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}, {"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}, {"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}, {"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}, {"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}, {"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};
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
			break;
		}
	}
}

int main(int argc, char **argv)

{

	struct timeval stop, start;
    gettimeofday(&start, NULL);

	int input_n = 30000;
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

// int input_n = atoi(argv[1]);
	// int *arr1 = (int *)malloc(input_n * sizeof(int));
    // int array_size1 = input_n;
    // srand(8);
    // for(int i = 0; i < array_size1; ++i)
    // {    
    //     arr1[i] = rand();
    // }

	// int *arr2 = (int *)malloc(input_n * sizeof(int));
    // int array_size2 = input_n;
    // srand(2);
    // for(int i = 0; i < array_size2; ++i)
    // {    
    //     arr2[i] = rand();
    // }

	// int n = array_size1;

	// struct timeval stop, start;
    // gettimeofday(&start, NULL);

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
		 sort(arr1, n);
		done1 = true;}));
	pair<int, atomic<bool>&> p_th_1(1, done1);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_1);
	}

	auto fn2 = bind(::my_min, arr1, n);
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
	auto fn3 = bind(::my_max, arr1, n);
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
		 sort(arr2, n);
		done4 = true;}));
	pair<int, atomic<bool>&> p_th_4(4, done4);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_4);
	}

	auto fn5 = bind(::my_min, arr2, n);
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
	auto fn6 = bind(::my_max, arr2, n);
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
	pair<int,string> p7_1(7, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p7_1);
	}
	atomic<bool> done7(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n);
		done7 = true;}));
	pair<int, atomic<bool>&> p_th_7(7, done7);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_7);
	}

	auto fn8 = bind(::my_min, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(8, fn8));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(8, fn8));
	}
	auto fn9 = bind(::my_max, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(9, fn9));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(9, fn9));
	}
	pair<int,string> p10_1(10, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p10_1);
	}
	atomic<bool> done10(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n);
		done10 = true;}));
	pair<int, atomic<bool>&> p_th_10(10, done10);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_10);
	}

	auto fn11 = bind(::my_min, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(11, fn11));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(11, fn11));
	}
	auto fn12 = bind(::my_max, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(12, fn12));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(12, fn12));
	}
	pair<int,string> p13_1(13, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p13_1);
	}
	atomic<bool> done13(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n);
		done13 = true;}));
	pair<int, atomic<bool>&> p_th_13(13, done13);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_13);
	}

	auto fn14 = bind(::my_min, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(14, fn14));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(14, fn14));
	}
	auto fn15 = bind(::my_max, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(15, fn15));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(15, fn15));
	}
	pair<int,string> p16_1(16, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p16_1);
	}
	atomic<bool> done16(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n);
		done16 = true;}));
	pair<int, atomic<bool>&> p_th_16(16, done16);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_16);
	}

	auto fn17 = bind(::my_min, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(17, fn17));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(17, fn17));
	}
	auto fn18 = bind(::my_max, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(18, fn18));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(18, fn18));
	}
	pair<int,string> p19_1(19, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p19_1);
	}
	atomic<bool> done19(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n);
		done19 = true;}));
	pair<int, atomic<bool>&> p_th_19(19, done19);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_19);
	}

	auto fn20 = bind(::my_min, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(20, fn20));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(20, fn20));
	}
	auto fn21 = bind(::my_max, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(21, fn21));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(21, fn21));
	}
	pair<int,string> p22_1(22, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p22_1);
	}
	atomic<bool> done22(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n);
		done22 = true;}));
	pair<int, atomic<bool>&> p_th_22(22, done22);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_22);
	}

	auto fn23 = bind(::my_min, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(23, fn23));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(23, fn23));
	}
	auto fn24 = bind(::my_max, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(24, fn24));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(24, fn24));
	}
	pair<int,string> p25_1(25, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p25_1);
	}
	atomic<bool> done25(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n);
		done25 = true;}));
	pair<int, atomic<bool>&> p_th_25(25, done25);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_25);
	}

	auto fn26 = bind(::my_min, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(26, fn26));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(26, fn26));
	}
	auto fn27 = bind(::my_max, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(27, fn27));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(27, fn27));
	}
	pair<int,string> p28_1(28, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p28_1);
	}
	atomic<bool> done28(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n);
		done28 = true;}));
	pair<int, atomic<bool>&> p_th_28(28, done28);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_28);
	}

	auto fn29 = bind(::my_min, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(29, fn29));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(29, fn29));
	}
	auto fn30 = bind(::my_max, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(30, fn30));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(30, fn30));
	}
	pair<int,string> p31_1(31, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p31_1);
	}
	atomic<bool> done31(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n);
		done31 = true;}));
	pair<int, atomic<bool>&> p_th_31(31, done31);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_31);
	}

	auto fn32 = bind(::my_min, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(32, fn32));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(32, fn32));
	}
	auto fn33 = bind(::my_max, arr1, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(33, fn33));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(33, fn33));
	}
	pair<int,string> p34_1(34, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p34_1);
	}
	atomic<bool> done34(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n);
		done34 = true;}));
	pair<int, atomic<bool>&> p_th_34(34, done34);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_34);
	}

	auto fn35 = bind(::my_min, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(35, fn35));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(35, fn35));
	}
	auto fn36 = bind(::my_max, arr2, n);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(36, fn36));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(36, fn36));
	}
	for(auto &x:void_futures)
	{
		x.wait();
		//x.get();
	}
	for(auto &x:int_futures){
		//cout << x.get() << "\n";
        x.wait();
	}


	gettimeofday(&stop, NULL);
    printf("Time Taken : %lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

}

		
		
	

