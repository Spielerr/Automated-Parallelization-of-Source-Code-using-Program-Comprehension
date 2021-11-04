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
#include <stdlib.h>
// Map Reduce Program to find distributed count
// Given the batsmen scores from every match in the Cricket World Cup, find the frequency of the scores

struct node_results {
   int score;
   int count;
};

typedef struct node_results node_results;
void fill(int a[], int n) {
   for(int i = 0; i < n; ++i) {
      a[i] = rand() % 300;
   }
}

void map(int *arr, int *count_arr, int n) {
   for(int i = 0; i < n; ++i) {
      count_arr[i] = 1;
   }
}

void merge_arr(int *arr1, int n1, int *arr2, int n2, int *arr3, int n3, int *merged_arr) {
   int ind = 0;
   for(int i = 0; i < n1; ++i) {
      merged_arr[ind] = arr1[i];
      ++ind;
   }
   for(int i = 0; i < n2; ++i) {
      merged_arr[ind] = arr2[i];
      ++ind;
   }
   for(int i = 0; i < n3; ++i) {
      merged_arr[ind] = arr3[i];
      ++ind;
   }
}

#include <parallel/algorithm>
void sort(int *arr, int n) {
   __gnu_parallel::sort(arr, arr + n );
}

//returns the ending index in the sorted_scores_arr for the range defined
int partition(int *sorted_scores_arr, int n, int range_start, int range_end, int start_ind) {
   if(start_ind < n && sorted_scores_arr[start_ind] >= range_start && sorted_scores_arr[start_ind] <= range_end) {
      int end_ind = start_ind;
      int i = start_ind + 1;
      while(i < n && sorted_scores_arr[i] <= range_end) {
         end_ind = i;
         ++i;
      }
      
      return end_ind;
   }
   else {
      //partition is empty
      
      return -1;
   }
}

// returns the length of the node_results arr after performing the reduce operation
int reduce(int *sorted_scores_arr, int l, int r, node_results *arr, int n) {
   int count_score = 1;
   int ind = 0;
   for(int i = l + 1; i <= r; ++i) {
      if(sorted_scores_arr[i] == sorted_scores_arr[i - 1]) {
         count_score += 1;
      }
      else {
         arr[ind].score = sorted_scores_arr[i - 1];
         arr[ind].count = count_score;
         count_score = 1;
         ind += 1;
      }
   }
   arr[ind].score = sorted_scores_arr[r];
   arr[ind].count = count_score;
   ind += 1;
   
   return ind;
}

//ranges are defined as follows:
// range 1 : 0-99
// range 2 : 100 - 199
// range 3 : 200 - 300
//returns the length of the combined array generates the combined array
int combiner(node_results *arr1, int n1, node_results *arr2, int n2, node_results *arr3, int n3, node_results *combined_arr) {
   int ind = 0;
   for(int i = 0; i < n1; ++i) {
      combined_arr[ind].count = arr1[i].count;
      combined_arr[ind].score = arr1[i].score;
      ++ind;
   }
   for(int i = 0; i < n2; ++i) {
      combined_arr[ind].count = arr2[i].count;
      combined_arr[ind].score = arr2[i].score;
      ++ind;
   }
   for(int i = 0; i < n3; ++i) {
      combined_arr[ind].count = arr3[i].count;
      combined_arr[ind].score = arr3[i].score;
      ++ind;
   }
   
   return ind;
}

void display(node_results *arr, int n) {
   printf("The Distributed Count of the Batsmen Scores are:\n");
   for(int i = 0; i < n; ++i) {
      printf("Score: %d, Count: %d\n", arr[i].score, arr[i].count);
   }
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
    int match_1_len = 20000;
    int match_2_len = 30000;
    int match_3_len = 50000;

    int *match_1_scores = (int*)malloc( sizeof(int) * match_1_len );
    int *match_2_scores = (int*)malloc( sizeof(int) * match_2_len );
    int *match_3_scores = (int*)malloc( sizeof(int) * match_3_len );
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(1, tp.Submit([&]{
			 fill(match_1_scores, match_1_len);
			})));
	}
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(2, tp.Submit([&]{
			 fill(match_2_scores, match_2_len);
			})));
	}
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(3, tp.Submit([&]{
			 fill(match_3_scores, match_3_len);
			})));
	}
    int *count_1 = (int*)malloc( sizeof(int) * match_1_len );
    int *count_2 = (int*)malloc( sizeof(int) * match_2_len );
    int *count_3 = (int*)malloc( sizeof(int) * match_3_len );
	find_future(1);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(4, tp.Submit([&]{
			 map(match_1_scores, count_1, match_1_len);
			})));
	}
	find_future(2);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(5, tp.Submit([&]{
			 map(match_2_scores, count_2, match_2_len);
			})));
	}
	find_future(3);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(6, tp.Submit([&]{
			 map(match_3_scores, count_3, match_3_len);
			})));
	}

    int n = match_1_len + match_2_len + match_3_len;
    int *merged_arr = (int*)malloc( sizeof(int) * n );

	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(7, tp.Submit([&]{
			 merge_arr(match_1_scores, match_1_len, match_2_scores, match_2_len, match_3_scores, match_3_len, merged_arr);
			})));
	}
	find_future(7);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(8, tp.Submit([&]{
			 sort(merged_arr, n);
			})));
	}

    int start_ind = 0;

    // range 1 : 0-99
    // range 2 : 100 - 199
    // range 3 : 200 - 300

    node_results *arr1 = (node_results*)malloc( sizeof(node_results) * 100 );
    node_results *arr2 = (node_results*)malloc( sizeof(node_results) * 100 );
    node_results *arr3 = (node_results*)malloc( sizeof(node_results) * 101 );
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

	find_future(8);
	int range1_ind;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(9, tp.Submit([&]()->int{
			 int temp = partition(merged_arr, n, 0, 99, 0);
			return temp;})));
	}
    
	find_future(9, range1_ind);
    if(range1_ind != -1)
    {
	int n1;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(10, tp.Submit([&]()->int{
			 int temp = reduce(merged_arr, 0, range1_ind, arr1, 100);
			return temp;})));
	}
        start_ind = range1_ind + 1;
    }

	int range2_ind;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(11, tp.Submit([&]()->int{
			 int temp = partition(merged_arr, n, 100, 199, range1_ind + 1);
			return temp;})));
	}

	find_future(11, range2_ind);
    if(range2_ind != -1)
    {
	int n2;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(12, tp.Submit([&]()->int{
			 int temp = reduce(merged_arr, range1_ind + 1, range2_ind, arr2, 100);
			return temp;})));
	}
        start_ind = range2_ind + 1;
    }

	int range3_ind;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(13, tp.Submit([&]()->int{
			 int temp = partition(merged_arr, n, 200, 300, range2_ind + 1);
			return temp;})));
	}

	find_future(13, range3_ind);
    if(range3_ind != -1)
    {
	int n3;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(14, tp.Submit([&]()->int{
			 int temp = reduce(merged_arr, range2_ind + 1, range3_ind, arr3, 101);
			return temp;})));
	}
        start_ind = range3_ind + 1;
    }

	find_future(10, n1);
	find_future(12, n2);
	find_future(14, n3);
    node_results *final_results = (node_results*)malloc((n1+n2+n3)*sizeof(node_results));
	int combined_length;
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(15, tp.Submit([&]()->int{
			 int temp = combiner(arr1, n1, arr2, n2, arr3, n3, final_results);
			return temp;})));
	}


    for (auto &x : futures)
	{
		visit([](auto n) { (n).wait();}, x.second);
	}
    
}
