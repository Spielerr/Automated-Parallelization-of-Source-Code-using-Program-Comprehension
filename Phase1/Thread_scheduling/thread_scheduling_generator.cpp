#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// NOTE FOR DD: I have numbered whatever data from Lara is required.
// Ctrl + F for "DD"

// all return types
// DD1
vector<string> return_types{"int", "void"};

// vector of vector of strings containing all fn args
// DD2
vector<vector<string>> all_fn_args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};

// sp_c stores the total number of functions changing their arguments (like my_sort)
// in our case, it is 2 (2 my_sort fn calls)
// DD3
int sp_c = 2;


// wr_q stores the total number of functions not changing their arguments (like min, max)
// in our case, it is 4 (2 min and 2 max fn calls)
// DD4
int wr_q = 4;

/*
string is for the fn name
int is a flag variable to signify the type of fn call
	0 for those fns which change their argument (like my_sort)
	1 for the others (like min, max)
vector<string> is to store all the arguments(and not parameters) of the fn calls
the second vector<string> stores the arguments which are getting changed from those functions changing their arguments
if fn doesnt change anything (for cases of 1) just store an empty vector if possible, or just store 
all arguments like the first vector

how to work with tuples?
tuple <char, int, float> geek;
geek = make_tuple('a', 10, 15.5);
thank me later
*/
//DD5
vector<tuple<string, int, vector<string>, vector<string>>> fn_call_info;


void gen_headers()
{
	string temp = R"(#include "thread_pool/thread_pool.hpp"
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
	)";
	cout << temp << '\n';
	
}

void prologue()
{
	cout<<"int num_threads = thread::hardware_concurrency();\n";
	cout<<"ctpl::thread_pool tp(num_threads);\n";
	cout << "int sp_c = " << to_string(sp_c) << ";\n";
	cout << "int wr_q = " << to_string(wr_q) << ";\n";

	for(auto x:return_types)
	{
		cout << "vector<future<" + x + ">> " + x + "_futures;\n";
	}
	
	cout<<"vector<pair<int, string>> special;\n";
	cout<<"vector<pair<int, atomic<bool>&>> thread_track;\n";

	
	cout << "vector<vector<string>> args{";
	for(int j = 0; j<all_fn_args.size(); j++)
	{
		auto x = all_fn_args[j];
		cout << "{";
		for(int i=0;i<x.size();i++)
		{
			if(i != x.size() - 1)
				cout << "\"" + x[i] + "\",";
			else
				cout << "\"" + x[i] + "\"";
		}
		if(j != all_fn_args.size() - 1)
			cout << "}, ";
		else
			cout << "}};\n";
	}

	// change these according to the return values of those functions not changing their arguments (like min, max)
	// we could have different function return types
	// but should have only one ready queue and one wait queue
	cout<<"deque<pair<int, string>> ready_queue;\n";
	cout<<"deque<pair<int, string>> wait_queue;\n";

	cout<<"atomic<int> special_changed(0);\n";
	cout<<"string remove_fn;\n\n";

	string temp = R"(mutex m_sp;
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
};)";
	cout << temp << "\n\n";


}

void threadtrack()
{
	string temp = R"(void thread_track_fn()
{
	int flag = true;
	int sp_done_c = 0;
	while(true)
	{
		{
			lock_guard<mutex> lockGuard(m_tt);
			for(auto x:thread_track)
			{
				while(special_changed)cout << "Busy Waiting" << "\n";
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
})";

	cout << temp << "\n\n";
}

void schedulingfn()
{
	string temp = R"(void scheduling_fn()
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
})";

	cout << temp << "\n\n";
}

void mainfn()
{
	// gotta handle this part of code from client somehow
	string temp = R"(int main(int argc, char **argv)
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
	)";
	cout << temp << "\n\n";

	// format of fn_call_info tuples
	//("my_sort", 0, ["arr1", "n"], ["arr1"])
	int count = 1;
	for(int k = 0; k < fn_call_info.size(); k++)
	{
		++count;

		// for min, max n stuff
		if(get<1>(fn_call_info[k]))
		{
			cout << "auto fn" + to_string(count) + " = bind(::" + get<0>(fn_call_info[k]) + ", ";
			for(int i = 0; i < get<2>(fn_call_info[k]).size(); i++)
			{
				if(i == (get<2>(fn_call_info[k]).size() - 1))
				{
					cout << get<2>(fn_call_info[k])[i] << ");\n";
				}
				else
				{
					cout << get<2>(fn_call_info[k])[i] << ", ";
				}
			}
			cout << "\t{\n\t\tlock_guard<mutex> lockGuard(m_sp);\n\t\titer1 = find_if(begin(special), end(special), Find_special2(\"";
			cout << get<2>(fn_call_info[k])[0] + "\"));\n\t\titer2 = end(special);\n\t}\n";

			cout << "\tif(iter1 != iter2)\n\t{\n\t\tlock_guard<mutex> lockGuard(m_wq);\nwait_queue.push_back(pair<int, std::function<int()>>(";
			cout << to_string(k+1);
			cout << ", fn" + to_string(k+1) + "));\n\t};\n";

			cout << "else\n\t{\n\t\tlock_guard<mutex> lockGuard(m_wq);\nready_queue.push_back(pair<int, std::function<int()>>(";
			cout << to_string(k+1);
			cout << ", fn" + to_string(k+1) + "));\n\t};\n";	
		}
		// for my_sort n stuff
		else
		{
			for(int i = 0; i < get<3>(fn_call_info[k]).size(); i++)
			{
				cout << "\tpair<int,string> p" + to_string(k+1) + "_" + to_string(i+1) + "(" + to_string(k+1) + ", " + "\"" + get<3>(fn_call_info[k])[i] + "\");\n";
			}
			cout << "\t{\n\t\tlock_guard<mutex> lockGuard(m_sp);\n";
			for(int i = 0; i < get<3>(fn_call_info[k]).size(); i++)
			{
				cout << "\t\tspecial.push_back(p" + to_string(k+1) + "_" + to_string(i+1) + ");\n"
			}
			cout << "\t}\n"
			cout << "\tatomic<bool> done" + to_string(k+1) + "(false);\n";
			cout << "\tvoid_futures.emplace_back(tp.Submit([&] {\n\t\t " + get<0>(fn_call_info[k]) + "(";
			for(int i = 0; i < get<2>(fn_call_info[k]).size(); i++)
			{
				if(i == (get<2>(fn_call_info[k]).size() - 1))
				{
					cout << get<2>(fn_call_info[k])[i] << ");\n";
				}
				else
				{
					cout << get<2>(fn_call_info[k])[i] << ", ";
				}
			}
			cout << "\t\tdone" + to_string(k+1) + " = true;;}))\n";
			string pair_temp = "p_th_" + to_string(k+1);
			cout << "\tpair<int, atomic<bool>&> " + pair_temp + "(1, done" + to_string(k+1) + ");\n" 
			cout << "\t{\n\t\tlock_guard<mutex> lockGuard(m_tt);\n\t\tthread_track.push_back(" + pair_temp + ");\n\t}\n\n";
 		}
	}
	for(auto x:return_types)
	{
		cout << "\tfor(auto &x:" + x + "_futures)";
		if(!strcmp(x, "void"))
		{
			cout << "\n\t{\n\t\tx.wait();\n\t\tx.get();\n\t}\n";
		}
		else
		{
			string temp = R"({
		x.wait();
		cout << std::boolalpha;
		cout << x.valid() << "\n";
		if(x.valid())
		cout << x.get() << "\n";
	})";
		cout << temp << "\n\n";
		}
	}
	string finish = R"(gettimeofday(&stop, NULL);
    printf("took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

	return 0;
})";
	cout << finish << "\n\n";
}

int main()
{
	gen_headers();
	prologue();
	threadtrack();
	schedulingfn();
	mainfn();
}