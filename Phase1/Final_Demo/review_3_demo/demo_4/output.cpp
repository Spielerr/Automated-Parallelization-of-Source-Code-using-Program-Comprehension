#include "thread_pool.hpp"
#include <thread>
#include <atomic>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <mutex>
#include <variant>
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

int my_max(int *a, int n, int fn_call_no) {
   int max = a[n - 1];
   printf("%d: Max : %d\n", fn_call_no, max);
   
   return max;
}

int my_min(int *a, int n, int fn_call_no) {
   int min = a[0];
   printf("%d: Min : %d\n", fn_call_no, min);
   
   return min;
}

int binarySearch(int arr[], int l, int r, int x, int fn_call_no) {
   int l_ = l;
   int r_ = r;
   while(l_ <= r_) {
      int m = l_ + (r_ - l_) / 2;
      if(arr[m] == x) {
         printf("%d: Index : %d\n", fn_call_no, m);
         
         return m;
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
vector<pair<int, variant<shared_future<void>, shared_future<int>>>> futures;
mutex m_f;

class Find_futures
{
	private:
	int ind_;

	public:
	Find_futures(int index) : ind_(index) {}
	bool operator()(pair<int,variant<shared_future<void>, shared_future<int>>> i)
{
		if(i.first == ind_)
		{
			return true;
		}
		return false;
	}
};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<typename T>
void find_future(int index, T& res)
{
	// wait until the required future is moved into futures from ready queue
	// while(find_if(begin(futures), end(futures), Find_futures(index)) != end(futures));
	while(1)
	{
		{
			lock_guard<mutex> lockGuard(m_f);
			if(find_if(begin(futures), end(futures), Find_futures(index)) != end(futures))
			{
				break;
			}
		}
	}
	vector<pair<int,variant<shared_future<void>, shared_future<int>>>>::iterator it;
{
		lock_guard<mutex> lockGuard(m_f);
		it = find_if(begin(futures), end(futures), Find_futures(index));
	}
	// cout << it->first << "\n";

	visit(overloaded {
		[&res](auto n){ res = n.get(); },
		[](shared_future<void> n){ ; }
		}, 
		it->second);
}

void find_future(int index)
{
	// wait until the required future is moved into futures from ready queue
	// while(find_if(begin(futures), end(futures), Find_futures(index)) != end(futures));
	while(1)
	{
		{
			lock_guard<mutex> lockGuard(m_f);
			if(find_if(begin(futures), end(futures), Find_futures(index)) != end(futures))
			{
				break;
			}
		}
	}
	vector<pair<int,variant<shared_future<void>, shared_future<int>>>>::iterator it;
{
		lock_guard<mutex> lockGuard(m_f);
		it = find_if(begin(futures), end(futures), Find_futures(index));
	}
	// cout << it->first << "\n";

	visit(overloaded {
        [](auto n){ n.get(); },
		[](shared_future<void> n){ n.wait(); }
		}, 
		it->second);
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

	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(1, tp.Submit([&]{
			 sort(arr1, n, arr_fn_calls_nos[0]);
			})));
	}
	find_future(1);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(2, tp.Submit([&]()->int{
			 int temp = my_max(arr1, n, arr_fn_calls_nos[1]);
			return temp;})));
	}
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(3, tp.Submit([&]()->int{
			 int temp = my_min(arr1, n, arr_fn_calls_nos[2]);
			return temp;})));
	}
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(4, tp.Submit([&]()->int{
			 int temp = binarySearch(arr1, 0, n, 2147335086, arr_fn_calls_nos[3]);
			return temp;})));
	}


	gettimeofday(&stop, NULL);
	// printf("Time Taken : %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);


    for (auto &x : futures)
	{
		visit([](auto n) { (n).wait();}, x.second);
	}
    
}
