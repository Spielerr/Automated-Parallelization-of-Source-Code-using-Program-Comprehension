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
vector<shared_future<void>> void_futures_scheduler;
vector<pair<int, string>> special;
vector<pair<int, atomic<bool>&>> thread_track;
vector<vector<string>> args{{"match_1_scores","match_1_len"}, {"match_2_scores","match_2_len"}, {"match_3_scores","match_3_len"}, {"match_1_scores","count_1","match_1_len"}, {"match_2_scores","count_2","match_2_len"}, {"match_3_scores","count_3","match_3_len"}, {"match_1_scores","match_1_len","match_2_scores","match_2_len","match_3_scores","match_3_len","merged_arr"}, {"merged_arr","n"}, {"merged_arr","n","0","99","0"}, {"merged_arr","0","range1_ind","arr1","100"}, {"merged_arr","n","100","199","range1_ind + 1"}, {"merged_arr","range1_ind + 1","range2_ind","arr2","100"}, {"merged_arr","n","200","300","range2_ind + 1"}, {"merged_arr","range2_ind + 1","range3_ind","arr3","101"}, {"arr1","n1","arr2","n2","arr3","n3","final_results"}};

deque<pair<int, variant<function<void()>, function<int()>>>> ready_queue;
deque<pair<int, variant<function<void()>, function<int()>>>> wait_queue;

atomic<int> special_changed(0);
string remove_fn;

mutex m_sp;
mutex m_wq;
mutex m_rq;
mutex m_tt;
mutex m_tf;
mutex m_sf;
mutex m_sp_c;
mutex m_f;

// to mark the end of thread_track and scheduling_fn threads
bool done_01 = false;
bool done_02 = false;


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

void thread_track_fn()
{
	while(!done_01 || special.size()!=0)
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
				}
			}
		}
	}
}

void scheduling_fn()
{
	//special got updated
	while(!done_02 || ready_queue.size() != 0 || wait_queue.size() != 0)
	{
		// cout << "scheduling_fn\n";
		{
			if(special_changed)
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
					// int_futures.emplace_back(tp.Submit(x->second));
                    int temp = x->first;
                    {
                        lock_guard<mutex> lockGuard(m_f);
                        visit([temp](auto n)
                            {
                                pair<int, variant<shared_future<void>, shared_future<int>>> temp_pair(temp, tp.Submit(n));
                                futures.emplace_back(temp_pair); 
                                },
                            x->second);
                    }
					x = ready_queue.erase(x);
					//file output code
					// int_futures.emplace_back(tp.Submit(min, cref(arr1), cref(n)));
				}
			}
		}
	}
}

int main(int argc, char **argv)
{


	void_futures_scheduler.emplace_back(tp.Submit(thread_track_fn));
	void_futures_scheduler.emplace_back(tp.Submit(scheduling_fn));

	using namespace std::chrono_literals;
	vector<pair<int,string>>::iterator iter1, iter2;
	

    int match_1_len = 20000;
    int match_2_len = 30000;
    int match_3_len = 50000;

    int *match_1_scores = (int*)malloc( sizeof(int) * match_1_len );
    int *match_2_scores = (int*)malloc( sizeof(int) * match_2_len );
    int *match_3_scores = (int*)malloc( sizeof(int) * match_3_len );
	pair<int,string> p1_1(1, "match_1_scores");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p1_1);
	}
	atomic<bool> done1(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(1, tp.Submit([&]{
			 fill(match_1_scores, match_1_len);
			done1 = true;})));
	}
	pair<int, atomic<bool>&> p_th_1(1, done1);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_1);
	}

	pair<int,string> p2_1(2, "match_2_scores");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p2_1);
	}
	atomic<bool> done2(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(2, tp.Submit([&]{
			 fill(match_2_scores, match_2_len);
			done2 = true;})));
	}
	pair<int, atomic<bool>&> p_th_2(2, done2);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_2);
	}

	pair<int,string> p3_1(3, "merged_arr");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p3_1);
	}
	atomic<bool> done3(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(3, tp.Submit([&]{
			 fill(match_3_scores, match_3_len);
			done3 = true;})));
	}
	pair<int, atomic<bool>&> p_th_3(3, done3);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_3);
	}

    int *count_1 = (int*)malloc( sizeof(int) * match_1_len );
    int *count_2 = (int*)malloc( sizeof(int) * match_2_len );
    int *count_3 = (int*)malloc( sizeof(int) * match_3_len );
	find_future(1);
	pair<int,string> p4_1(4, "count_1");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p4_1);
	}
	atomic<bool> done4(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(4, tp.Submit([&]{
			 map(match_1_scores, count_1, match_1_len);
			done4 = true;})));
	}
	pair<int, atomic<bool>&> p_th_4(4, done4);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_4);
	}

	find_future(2);
	pair<int,string> p5_1(5, "count_2");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p5_1);
	}
	atomic<bool> done5(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(5, tp.Submit([&]{
			 map(match_2_scores, count_2, match_2_len);
			done5 = true;})));
	}
	pair<int, atomic<bool>&> p_th_5(5, done5);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_5);
	}

	find_future(3);
	pair<int,string> p6_1(6, "merged_arr");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p6_1);
	}
	atomic<bool> done6(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(6, tp.Submit([&]{
			 map(match_3_scores, count_3, match_3_len);
			done6 = true;})));
	}
	pair<int, atomic<bool>&> p_th_6(6, done6);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_6);
	}


    int n = match_1_len + match_2_len + match_3_len;
    int *merged_arr = (int*)malloc( sizeof(int) * n );

	pair<int,string> p7_1(7, "merged_arr");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p7_1);
	}
	atomic<bool> done7(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(7, tp.Submit([&]{
			 merge_arr(match_1_scores, match_1_len, match_2_scores, match_2_len, match_3_scores, match_3_len, merged_arr);
			done7 = true;})));
	}
	pair<int, atomic<bool>&> p_th_7(7, done7);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_7);
	}

	find_future(7);
	pair<int,string> p8_1(8, "merged_arr");
	{
		lock_guard<mutex> lockGuard(m_sp);
		special.push_back(p8_1);
	}
	atomic<bool> done8(false);
	{
		lock_guard<mutex> lockGuard(m_f);
		futures.emplace_back(make_pair(8, tp.Submit([&]{
			 sort(merged_arr, n);
			done8 = true;})));
	}
	pair<int, atomic<bool>&> p_th_8(8, done8);
	{
		lock_guard<mutex> lockGuard(m_tt);
		thread_track.push_back(p_th_8);
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
	auto fn9 = bind(::partition, merged_arr, n, 0, 99, 0);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("merged_arr"));
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
    
	find_future(9, range1_ind);
    if(range1_ind != -1)
    {
	int n1;
	auto fn10 = bind(::reduce, merged_arr, 0, range1_ind, arr1, 100);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("merged_arr"));
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
        start_ind = range1_ind + 1;
    }

	int range2_ind;
	auto fn11 = bind(::partition, merged_arr, n, 100, 199, range1_ind + 1);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("merged_arr"));
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

	find_future(11, range2_ind);
    if(range2_ind != -1)
    {
	int n2;
	auto fn12 = bind(::reduce, merged_arr, range1_ind + 1, range2_ind, arr2, 100);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("merged_arr"));
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
        start_ind = range2_ind + 1;
    }

	int range3_ind;
	auto fn13 = bind(::partition, merged_arr, n, 200, 300, range2_ind + 1);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("merged_arr"));
		iter2 = end(special);
	}
	if(iter1 != iter2)
	{
		lock_guard<mutex> lockGuard(m_wq);
		wait_queue.push_back(pair<int, std::function<int()>>(13, fn13));
	}
	else
	{
		lock_guard<mutex> lockGuard(m_rq);
		ready_queue.push_back(pair<int, std::function<int()>>(13, fn13));
	}

	find_future(13, range3_ind);
    if(range3_ind != -1)
    {
	int n3;
	auto fn14 = bind(::reduce, merged_arr, range2_ind + 1, range3_ind, arr3, 101);
	{
		lock_guard<mutex> lockGuard(m_sp);
		iter1 = find_if(begin(special), end(special), Find_special2("merged_arr"));
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
        start_ind = range3_ind + 1;
    }

	find_future(10, n1);
	find_future(12, n2);
	find_future(14, n3);
    node_results *final_results = (node_results*)malloc((n1+n2+n3)*sizeof(node_results));
	int combined_length;
	auto fn15 = bind(::combiner, arr1, n1, arr2, n2, arr3, n3, final_results);
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


    done_01 = true;
    done_02 = true;
    for(auto &x:void_futures_scheduler)
    {
        x.wait();
    }
    

    for (auto &x : futures)
	{
		visit([](auto n) { (n).wait();}, x.second);
	}
    
}
