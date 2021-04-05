#include <iostream>
#include <string>
#include <vector>
using namespace std;

// all return types
vector<string> return_types;
// vector of vector of strings containing all fn args
vector<vector<string>> all_fn_args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};

//set this from lara data
int tt_counter = 4;
int s_fn_counter = 6;

void gen_headers()
{
	string temp = R"(#include <vector>
#include <deque>
#include <iostream>
#include "CTPL/ctpl_stl.h"
#include <thread>
#include <atomic>
#include <unistd.h>
#include "prog.cpp"
#include <functional>
using namespace std;
	)";
	cout << temp << '\n';
	
}

void prologue()
{
	cout<<"int num_threads = thread::hardware_concurrency();\n";
	cout<<"ctpl::thread_pool tp(num_threads);\n";
	cout << "int tt_counter = " << to_string(tt_counter) << ";\n";
	cout << "int s_fn_counter = " << to_string(s_fn_counter) << ";\n";

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
	cout<<"deque<pair<int, std::function<int(int)>>> ready_queue;\n";
	cout<<"deque<pair<int, std::function<int(int)>>> wait_queue;\n";

	cout<<"atomic<int> special_changed(0);\n";
	cout<<"string remove_fn;\n\n";

	string temp = R"(class Find_special
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
	while(flag)
	{
		cerr<<"ADDING\n\n";
		for(auto x:thread_track)
		{
			while(special_changed);
			if(x.second)
			{
				x.second = false;
				auto iter_special = find_if(special.begin(), special.end(), Find_special(x.first));
				remove_fn = (*iter_special).second;
				special.erase(iter_special);
				special_changed = 1;
				if(x.first == tt_counter)
				{
					flag = false;
				}
			}
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
	while(flag)
	{
		while(special_changed)
		{
			cerr<<"ADDING\n\n";
			for(auto x:wait_queue)
			{
				cerr<<"ADDING\n\n";
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
					if(x.first == s_fn_counter)
					{
						flag = false;
					}
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
				cerr<<"ADDING\n\n";
				int_futures.emplace_back(tp.push(f));
				auto iter = find_if( begin(ready_queue), end(ready_queue), Find_special3<pair<int, std::function<int(int)>>>(x.first));
				ready_queue.erase(iter);
			}
		}
	}
})";

	cout << temp << "\n\n";
}

void mainfn()
{

}

int main()
{
	gen_headers();
	prologue();
	threadtrack();
	schedulingfn();
	mainfn();
}