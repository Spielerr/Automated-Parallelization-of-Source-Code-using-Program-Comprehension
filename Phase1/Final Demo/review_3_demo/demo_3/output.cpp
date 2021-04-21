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


void my_max(int* a4, int n4, int *res)
{
	int max = a4[0];
	for(int i = 1; i < n4; ++i)
	{
		if(a4[i]>max)
		{
			max = a4[i];
		}
	}

	*res = max;
}

void my_min(int* a4, int n4, int *res)
{
	int min = a4[0];
	for(int i = 1; i<n4; ++i)
	{
		if(a4[i]<min)
		{
			min = a4[i];
		}
	}

	*res = min;
}



int num_threads = thread::hardware_concurrency();
ThreadPool tp(num_threads);
int sp_c = 12;
int wr_q = 0;
vector<shared_future<void>> void_futures;
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"arr1","n"}, {"arr1","n","&min_res1"}, {"arr1","n","&max_res1"}, {"arr2","n"}, {"arr2","n","&min_res2"}, {"arr2","n","&max_res2"}, {"arr1","n"}, {"arr1","n","&min_res3"}, {"arr1","n","&max_res3"}, {"arr2","n"}, {"arr2","n","&min_res4"}, {"arr2","n","&max_res4"}};
deque<pair<int, std::function<void()>>> ready_queue;
deque<pair<int, std::function<void()>>> wait_queue;
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
							wait_queue.erase(find_if( begin(wait_queue), end(wait_queue), Find_special3<pair<int, std::function<void()>>>(x.first)));
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
					void_futures.emplace_back(tp.Submit(x.second));

					auto iter = find_if( begin(ready_queue), end(ready_queue), Find_special3<pair<int, std::function<void()>>>(x.first));
					ready_queue.erase(iter);
					++wr_done_c;
					//file output code
					// void_futures.emplace_back(tp.Submit(min, cref(arr1), cref(n)));
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

		int min_res1, max_res1, min_res2, max_res2;
		int min_res3, max_res3, min_res4, max_res4;
		
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

	pair<int,string> p2_1(2, "&min_res1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p2_1);
	}
	atomic<bool> done2(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_min(arr1, n, &min_res1);
		done2 = true;}));
	pair<int, atomic<bool>&> p_th_2(2, done2);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_2);
	}

	pair<int,string> p3_1(3, "&max_res1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p3_1);
	}
	atomic<bool> done3(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_max(arr1, n, &max_res1);
		done3 = true;}));
	pair<int, atomic<bool>&> p_th_3(3, done3);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_3);
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

	pair<int,string> p5_1(5, "&min_res2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p5_1);
	}
	atomic<bool> done5(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_min(arr2, n, &min_res2);
		done5 = true;}));
	pair<int, atomic<bool>&> p_th_5(5, done5);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_5);
	}

	pair<int,string> p6_1(6, "&max_res2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p6_1);
	}
	atomic<bool> done6(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_max(arr2, n, &max_res2);
		done6 = true;}));
	pair<int, atomic<bool>&> p_th_6(6, done6);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_6);
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

	pair<int,string> p8_1(8, "&min_res3");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p8_1);
	}
	atomic<bool> done8(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_min(arr1, n, &min_res3);
		done8 = true;}));
	pair<int, atomic<bool>&> p_th_8(8, done8);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_8);
	}

	pair<int,string> p9_1(9, "&max_res3");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p9_1);
	}
	atomic<bool> done9(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_max(arr1, n, &max_res3);
		done9 = true;}));
	pair<int, atomic<bool>&> p_th_9(9, done9);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_9);
	}

	pair<int,string> p10_1(10, "&min_res4");
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

	pair<int,string> p11_1(11, "&min_res4");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p11_1);
	}
	atomic<bool> done11(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_min(arr2, n, &min_res4);
		done11 = true;}));
	pair<int, atomic<bool>&> p_th_11(11, done11);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_11);
	}

	pair<int,string> p12_1(12, "&min_res4");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p12_1);
	}
	atomic<bool> done12(false);
	void_futures.emplace_back(tp.Submit([&] {
		 my_max(arr2, n, &max_res4);
		done12 = true;}));
	pair<int, atomic<bool>&> p_th_12(12, done12);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_12);
	}

	for(auto &x:void_futures)
	{
		x.wait();
		//x.get();
	}

		printf("Min of array 1 : %d\n", min_res1);
		printf("Min of array 2 : %d\n", min_res2);
		printf("Max of array 1 : %d\n", max_res1);
		printf("Max of array 2 : %d\n", max_res2);


		printf("Min of array 1 : %d\n", min_res3);
		printf("Min of array 2 : %d\n", min_res4);
		printf("Max of array 1 : %d\n", max_res3);
		printf("Max of array 2 : %d\n", max_res4);
	

	gettimeofday(&stop, NULL);
    printf("%lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);


}

		
		
	
