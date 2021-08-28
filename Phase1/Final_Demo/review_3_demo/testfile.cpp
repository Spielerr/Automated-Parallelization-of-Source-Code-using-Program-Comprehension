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
#include <algorithm>
#include <parallel/numeric>
double mean(int const *a1, int n1, int fn_call_no) {
   double* s;
   __gnu_parallel::partial_sum( a1, a1 + n1, s );
   return *s/n1;
}

#include <parallel/algorithm>
void sort(int *arr, int const arr_n, int fn_call_no) {
   __gnu_parallel::sort(arr, arr + arr_n );
}

int my_max(int *a4, int n4, int fn_call_no) {
   int max = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] > max) {
         max = a4[i];
      }
   }
   printf("%d: Max : %d\n", fn_call_no, max);
   
   return 1;
}

int my_min(int *a4, int n4, int fn_call_no) {
   int min = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] < min) {
         min = a4[i];
      }
   }
   printf("%d: Min : %d\n", fn_call_no, min);
   
   return 1;
}

int binarySearch(int arr[], int l, int r, int x, int fn_call_no) {
   int l_ = l;
   int r_ = r;
   while(l_ <= r_) {
      int m = l_ + (r_ - l_) / 2;
      if(arr[m] == x) {
         printf("%d: Index : %d\n", fn_call_no, m);
         
         return 1;
      }
      if(arr[m] < x) l_ = m + 1;
      else r_ = m - 1;
   }
   printf("%d: Index : %d\n", fn_call_no, -1);
   
   return -1;
}

int countOccurrences(int arr[], int n, int x, int fn_call_no) {
   int res = 0;
   for(int i = 0; i < n; i++) if(x == arr[i]) res++;
   printf("%d: Count of %d : %d\n", fn_call_no, x, res);
   
   return 1;
}

int ceilSearch(int arr[], int low, int high, int x, int fn_call_no) {
   int i;
   if(x <= arr[low]) {
      printf("%d:\tCeil of %d : %d\n", fn_call_no, x, arr[low]);
      
      return low;
   }
   for(i = low; i < high; i++) {
      if(arr[i] == x) {
         printf("%d: Ceil of %d : %d\n", fn_call_no, x, arr[i]);
         
         return i;
      }
      if(arr[i] < x && arr[i + 1] >= x) {
         printf("%d: Ceil of %d : %d\n", fn_call_no, x, arr[i + 1]);
         
         return i + 1;
      }
   }
   printf("%d: Ceil of %d : %d\n", fn_call_no, x, -1);
   
   return -1;
}
int num_threads = thread::hardware_concurrency();
ThreadPool tp(num_threads);
int sp_c = 6;
int wr_q = 18;
vector<shared_future<void>> void_futures;
vector<shared_future<int>> int_futures;
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"arr1","n","arr_fn_calls_nos[0]"}, {"arr1","0","n","2147483484","arr_fn_calls_nos[1]"}, {"arr1","n","2147483484","arr_fn_calls_nos[2]"}, {"arr1","0","n","2147483484","arr_fn_calls_nos[3]"}, {"arr2","n","arr_fn_calls_nos[4]"}, {"arr2","0","n","2147470276","arr_fn_calls_nos[5]"}, {"arr2","n","2147470276","arr_fn_calls_nos[6]"}, {"arr2","0","n","2147470276","arr_fn_calls_nos[7]"}, {"arr1","n","arr_fn_calls_nos[0]"}, {"arr1","0","n","2147483484","arr_fn_calls_nos[1]"}, {"arr1","n","2147483484","arr_fn_calls_nos[2]"}, {"arr1","0","n","2147483484","arr_fn_calls_nos[3]"}, {"arr2","n","arr_fn_calls_nos[4]"}, {"arr2","0","n","2147470276","arr_fn_calls_nos[5]"}, {"arr2","n","2147470276","arr_fn_calls_nos[6]"}, {"arr2","0","n","2147470276","arr_fn_calls_nos[7]"}, {"arr1","n","arr_fn_calls_nos[0]"}, {"arr1","0","n","2147483484","arr_fn_calls_nos[1]"}, {"arr1","n","2147483484","arr_fn_calls_nos[2]"}, {"arr1","0","n","2147483484","arr_fn_calls_nos[3]"}, {"arr2","n","arr_fn_calls_nos[4]"}, {"arr2","0","n","2147470276","arr_fn_calls_nos[5]"}, {"arr2","n","2147470276","arr_fn_calls_nos[6]"}, {"arr2","0","n","2147470276","arr_fn_calls_nos[7]"}};
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
					auto x = wait_queue.begin();
					while(x != wait_queue.end())
					{
						//pick out every argument from func in x
						//check if it exists in special
						//if it doesnt
						//	move it to ready queue
						bool is_found = false;
						for(auto y:args[x->first - 1])
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
							{
                                lock_guard<mutex> lockGuard(m_rq);
                                ready_queue.push_back(*x);
                            }
                            x = wait_queue.erase(x);
						}
                        else
                        {
                            ++x;
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
				auto x = ready_queue.begin();
				while(x != ready_queue.end())
				{
					int_futures.emplace_back(tp.Submit(x->second));
					x = ready_queue.erase(x);
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

	int input_n = 50000;
	int no_fn_calls = 24;
	int array_size1 = input_n;
	int n = array_size1;

	int* arr_fn_calls_nos = (int*) malloc( no_fn_calls * sizeof(int) );

	for(int i = 0; i < no_fn_calls; ++i)
	{
		arr_fn_calls_nos[i] = i;
	}

	int *arr1 = (int*)malloc( sizeof(int) * n );
	int *arr2 = (int*)malloc( sizeof(int) * n );

	srand(8);

	for(int i = 0; i < n; ++i)
	{    
		arr1[i] = rand();
		arr2[i] = rand();
	}



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
		 sort(arr1, n, arr_fn_calls_nos[0]);
		done1 = true;}));
	pair<int, atomic<bool>&> p_th_1(1, done1);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_1);
	}

	auto fn2 = bind(::ceilSearch, arr1, 0, n, 2147483484, arr_fn_calls_nos[1]);
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
	auto fn3 = bind(::countOccurrences, arr1, n, 2147483484, arr_fn_calls_nos[2]);
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
	auto fn4 = bind(::binarySearch, arr1, 0, n, 2147483484, arr_fn_calls_nos[3]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(4, fn4));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(4, fn4));
	}
	pair<int,string> p5_1(5, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p5_1);
	}
	atomic<bool> done5(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n, arr_fn_calls_nos[4]);
		done5 = true;}));
	pair<int, atomic<bool>&> p_th_5(5, done5);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_5);
	}

	auto fn6 = bind(::ceilSearch, arr2, 0, n, 2147470276, arr_fn_calls_nos[5]);
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
	auto fn7 = bind(::countOccurrences, arr2, n, 2147470276, arr_fn_calls_nos[6]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(7, fn7));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(7, fn7));
	}
	auto fn8 = bind(::binarySearch, arr2, 0, n, 2147470276, arr_fn_calls_nos[7]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
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
	pair<int,string> p9_1(9, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p9_1);
	}
	atomic<bool> done9(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n, arr_fn_calls_nos[0]);
		done9 = true;}));
	pair<int, atomic<bool>&> p_th_9(9, done9);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_9);
	}

	auto fn10 = bind(::ceilSearch, arr1, 0, n, 2147483484, arr_fn_calls_nos[1]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(10, fn10));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(10, fn10));
	}
	auto fn11 = bind(::countOccurrences, arr1, n, 2147483484, arr_fn_calls_nos[2]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
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
	auto fn12 = bind(::binarySearch, arr1, 0, n, 2147483484, arr_fn_calls_nos[3]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
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
	pair<int,string> p13_1(13, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p13_1);
	}
	atomic<bool> done13(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n, arr_fn_calls_nos[4]);
		done13 = true;}));
	pair<int, atomic<bool>&> p_th_13(13, done13);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_13);
	}

	auto fn14 = bind(::ceilSearch, arr2, 0, n, 2147470276, arr_fn_calls_nos[5]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
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
	auto fn15 = bind(::countOccurrences, arr2, n, 2147470276, arr_fn_calls_nos[6]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
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
	auto fn16 = bind(::binarySearch, arr2, 0, n, 2147470276, arr_fn_calls_nos[7]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(16, fn16));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(16, fn16));
	}
	pair<int,string> p17_1(17, "arr1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p17_1);
	}
	atomic<bool> done17(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr1, n, arr_fn_calls_nos[0]);
		done17 = true;}));
	pair<int, atomic<bool>&> p_th_17(17, done17);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_17);
	}

	auto fn18 = bind(::ceilSearch, arr1, 0, n, 2147483484, arr_fn_calls_nos[1]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
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
	auto fn19 = bind(::countOccurrences, arr1, n, 2147483484, arr_fn_calls_nos[2]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr1"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(19, fn19));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(19, fn19));
	}
	auto fn20 = bind(::binarySearch, arr1, 0, n, 2147483484, arr_fn_calls_nos[3]);
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
	pair<int,string> p21_1(21, "arr2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p21_1);
	}
	atomic<bool> done21(false);
	void_futures.emplace_back(tp.Submit([&] {
		 sort(arr2, n, arr_fn_calls_nos[4]);
		done21 = true;}));
	pair<int, atomic<bool>&> p_th_21(21, done21);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_21);
	}

	auto fn22 = bind(::ceilSearch, arr2, 0, n, 2147470276, arr_fn_calls_nos[5]);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("arr2"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(22, fn22));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(22, fn22));
	}
	auto fn23 = bind(::countOccurrences, arr2, n, 2147470276, arr_fn_calls_nos[6]);
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
	auto fn24 = bind(::binarySearch, arr2, 0, n, 2147470276, arr_fn_calls_nos[7]);
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
	printf("Time Taken : %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
}


