#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
#define DEBUG 0

// NOTE FOR DD: I have numbered whatever data from Lara is required.
// Ctrl + F for "DD"

// all return types
// DD1
vector<string> return_types;

// vector of vector of strings containing all fn args
// DD2
vector<vector<string>> all_fn_args;

// sp_c stores the total number of functions changing their arguments (like my_sort)
// in our case, it is 2 (2 my_sort fn calls)
// DD3
int sp_c;


// wr_q stores the total number of functions not changing their arguments (like min, max)
// in our case, it is 4 (2 min and 2 max fn calls)
// DD4
int wr_q;

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

class my_find_special
{
    private:
    string x_;

    public:
    my_find_special(string x): x_(x){}

    bool operator()(pair<string, vector<string>> i)
    {
        return i.first == x_;
    }

};

class my_find_2
{
    private:
    string x_;

    public:
    my_find_2(string x): x_(x){}

    bool operator()(pair<string,vector<pair<string, vector<string>>>> i)
    {
        return i.first == x_;
    }
};

void input_data()
{
	//data structure that holds the data from input.txt
    //it has the functions which have a write dependency along with the 
    //list of arguments that are being written into
    vector<pair<string, vector<string>>> fns_write_dep;

    string dependencies_1, dependencies;

    // ifstream file_1("input_large.txt");
    ifstream file_1("input.txt");

    //storing sort only once and adding all the arguments that it writes into as the vector associated with the pair
    //this way we can't keep track of the exact number of function calls that have write dependencies
    //this is because we can't count the number of argument to know the number of fn calls that perform a write
    //as a single fn call could be writing into multiple arguments

    /*
    while(getline(file_1, dependencies))
    {
        vector<string> result;
        stringstream s_stream(dependencies);
        while (s_stream.good()) 
        {
            string substr;
            getline(s_stream, substr, ',');
            result.push_back(substr);
        }

        pair<string, vector<string>> temp;

        temp.first = result[0];

        

        auto it1 = find_if(fns_write_dep.begin(),fns_write_dep.end(),my_find_special(temp.first));
        
        if(it1 != fns_write_dep.end())
        {
            for(int i = 1; i < result.size(); ++i)
            {
                (*it1).second.push_back(result[i]);

            }
        }   

        else
        {
            for(int i = 1; i < result.size(); ++i)
            {
                temp.second.push_back(result[i]);
            }

            fns_write_dep.push_back(temp);

        }     

        

    }
    */

   
   //creating a new pair every time sort occurs in the input.txt file
    while(getline(file_1, dependencies_1))
    {
        vector<string> result_1;
        stringstream s_stream_1(dependencies_1);
        while (s_stream_1.good()) 
        {
            string substr;
            getline(s_stream_1, substr, ',');
            result_1.push_back(substr);
        }

        pair<string, vector<string>> temp_p_sv;

        temp_p_sv.first = result_1[0];

        
        for(int i = 1; i < result_1.size(); ++i)
        {
            temp_p_sv.second.push_back(result_1[i]);
        }

        fns_write_dep.push_back(temp_p_sv);

    }
    

    file_1.close();


    #if DEBUG
    //testing whether the data from input.txt has been stored properly in the data structure
    for(auto i : fns_write_dep)
    {
        cout<<i.first<<"\n";
        for(auto j : i.second)
        {
            cout<<j<<"\n";
        }
    }

    cout<<"\n\n\n";

    #endif

    //data structure that holds the data from input2.txt
    vector<pair<string,vector<pair<string, vector<string>>>>> order_fn_calls_types;

    // ifstream file_2("input_large2.txt");
    ifstream file_2("input2.txt");

    while(getline(file_2,dependencies))
    {
        vector<string> result;
        stringstream s_stream(dependencies);

        int i = 0;

        pair<string,vector<pair<string, vector<string>>>> temp;
        vector<pair<string, vector<string>>> temp_v;

        while (s_stream.good()) 
        {
            string substr;
            getline(s_stream, substr, ';');

            //cout<<substr<<"\n";

            //substr contains the function and its return type
            if(i==0)
            {
                //cout<<substr<<"\n";

                stringstream s_stream_2(substr);

                int j = 0;

                while(s_stream_2.good())
                {
                    string substr2;
                    getline(s_stream_2, substr2, ',');

                    //cout<<substr2<<"\n";

                    //substr2 contains function name
                    if(j==0)
                    {
                        temp.first = substr2;
                    }

                    //substr2 contains return type
                    else
                    {
                        pair<string, vector<string>> temp_p;
                        temp_p.first = "ret_type";
                        temp_p.second = vector<string>{substr2};
                        temp_v.push_back(temp_p);
                    }

                    ++j;
                }
                

            }

            //substr contains an argument and parameter along with their return types
            else if(substr.size()>0)
            {

                stringstream s_stream_3(substr);

                //cout<<substr<<"\n";

                vector<string> temp_v_s;

                pair<string, vector<string>> temp_p;

                while(s_stream_3.good())
                {
                    string substr3;
                    getline(s_stream_3, substr3, ',');

                    temp_v_s.push_back(substr3);
                    

                    //cout<<substr3<<"\n";

                }

                if(temp_v_s.size()!=0)
                {
                    //making the argument the key in the pair
                    temp_p.first = temp_v_s[1];
                    temp_p.second = temp_v_s;
                    temp_v.push_back(temp_p);

                }


            }
            
            

            ++i;
        }

        temp.second = temp_v;
        order_fn_calls_types.push_back(temp);
    }

    file_2.close();

    #if DEBUG
    //testing whether data is stored properly in the data structure created

    for(auto i : order_fn_calls_types)
    {
        cout<<i.first<<":\n";

        for(auto j: i.second)
        {
            
                cout<<j.first<<":\n";
                for(auto k: j.second)
                {
                    cout<<k<<"\n";
                }
            
            
        }

        cout<<"\n\n";
    }

    #endif


    //DD1
    // all return types
    
    // vector<string> return_types;

    for(auto i : order_fn_calls_types)
    {
        for(auto j: i.second)
        {
            if(j.first.compare("ret_type")==0 && find(return_types.begin(),return_types.end(),j.second[0])==return_types.end())
            {
                return_types.push_back(j.second[0]);
            }
        }
    }

    //set<string> temp_rt_set(return_types_copy.begin(),return_types_copy.end());



    //vector<string> return_types(temp_rt_set.begin(),temp_rt_set.end());

    //testing whether data is stored in return_types properly
    #if DEBUG
    cout<<"\ntesting whether data is stored in return_types properly:\n";
    for(auto i: return_types)
    {
        cout<<i<<"\n";
    }
    #endif



    //DD2
    // vector of vector of strings containing all fn args
    //vector<vector<string>> all_fn_args{{"arr1","n"}, {"arr1","n"}, {"arr1","n"}, {"arr2","n"}, {"arr2","n"}, {"arr2","n"}};
    // vector<vector<string>> all_fn_args;

    for(auto i : order_fn_calls_types)
    {
        vector<string> temp_args;
        for(auto j: i.second)
        {
            if(j.first.compare("ret_type")!=0)
            {
                temp_args.push_back(j.first);
            }
        }
        all_fn_args.push_back(temp_args);
    }

    //testing whether data is stored properly in all_fn_args
    #if DEBUG
    cout<<"\ntesting whether data is stored properly in all_fn_args:\n";

    for(auto i : all_fn_args)
    {
        cout<<"\nfunction arg list:\n";
        for(auto j : i)
        {
            cout<<j<<"\n";
        }
        cout<<"\n";
    }

    #endif


    //DD3
    // sp_c stores the total number of functions changing their arguments (like my_sort)
    // in our case, it is 2 (2 my_sort fn calls)

    sp_c = fns_write_dep.size();

    #if DEBUG
    cout<<"The total number of functions changing their arguments are: "<<sp_c<< "\n";
    #endif

    // DD4
    // wr_q stores the total number of functions not changing their arguments (like min, max)
    // in our case, it is 4 (2 min and 2 max fn calls)
    wr_q = order_fn_calls_types.size() - fns_write_dep.size();

    #if DEBUG
    cout << "The Total number of functions not changing their arguments are: "<< wr_q <<"\n";
    #endif


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
    // vector<tuple<string, int, vector<string>, vector<string>>> fn_call_info;
    int flag_fn_call;
    int loop_i = 0;
    int count_fn = 0;

    

    for(auto i : order_fn_calls_types)
    {
        auto it_find_fn = find_if(fns_write_dep.begin(),fns_write_dep.end(),my_find_special(i.first));
        
        //if the function is found
        if(it_find_fn!=fns_write_dep.end())
        {
            flag_fn_call = 0;
        }
        else
        {
            flag_fn_call = 1;
        }

        

        vector<string> temp_v_args(all_fn_args[loop_i].begin(),all_fn_args[loop_i].end());

        

        vector<string> temp_v_changes_args;

        //args getting changed
        if(flag_fn_call==0)
        {
            count_fn = count_if(order_fn_calls_types.begin(),order_fn_calls_types.end(),my_find_2(i.first));
            
            
            if(count_fn > 1)
            {
                int call_no = 0;
                for(int i2 = 0; i2<order_fn_calls_types.size(); ++i2)
                {
                    //same as the function under consideration
                    if(order_fn_calls_types[i2].first == i.first)
                    {
                        call_no += 1;
                    }

                    if(i2 == loop_i)
                    {
                        break;
                    }
                }

                

                int call_no_w = 0;
                for(int j2 = 0; j2 < fns_write_dep.size(); ++ j2)
                {
                    //same as the function under consideration
                    if(fns_write_dep[j2].first == i.first)
                    {
                        call_no_w += 1;
                    }

                    if(call_no_w == call_no)
                    {
                        temp_v_changes_args.resize(fns_write_dep[j2].second.size());
                        copy(fns_write_dep[j2].second.begin(),fns_write_dep[j2].second.end(),temp_v_changes_args.begin());
                        
                    }
                }

                
            }
            else
            {
                temp_v_changes_args.resize((*it_find_fn).second.size());
                copy((*it_find_fn).second.begin(),(*it_find_fn).second.end(),temp_v_changes_args.begin());
            }
        }

        

        tuple<string, int, vector<string>, vector<string>> temp_fn_call;
        temp_fn_call = make_tuple(i.first,flag_fn_call,temp_v_args,temp_v_changes_args);

        fn_call_info.push_back(temp_fn_call);

        ++loop_i;
    }


    #if DEBUG
    //testing if the data is stored properly in the fn_call_info data structure

    for(auto i: fn_call_info)
    {
        cout<<"\n\nfunction name: ";
        cout<<get<0> (i)<<"\n";
        cout<<"flag: "<< get<1> (i) <<"\n";

        cout<<"vector of arguments: \n";
        for(auto j : get<2> (i))
        {
            cout<<j<<"\t";
        }

        cout<<"\nvector of arguments being changed: \n";
        for(auto k: get<3> (i))
        {
            cout<<k<<"\t";
        }

        cout<<"\n\n";
    }
    #endif
}


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
	cout<<"int num_threads = 12;\n";
	cout<<"ThreadPool tp(num_threads);\n";
	cout << "int sp_c = " << to_string(sp_c) << ";\n";
	cout << "int wr_q = " << to_string(wr_q) << ";\n";

	for(auto x:return_types)
	{
		cout << "vector<shared_future<" + x + ">> " + x + "_futures;\n";
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
	cout<<"deque<pair<int, std::function<int()>>> ready_queue;\n";
	cout<<"deque<pair<int, std::function<int()>>> wait_queue;\n";

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
	// cout << fn_call_info.size() << endl;
	for(int k = 0; k < fn_call_info.size(); k++)
	{

		// for min, max n stuff
		if(get<1>(fn_call_info[k]))
		{
			cout << "\tauto fn" + to_string(k+1) + " = bind(::" + get<0>(fn_call_info[k]) + ", ";
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

			cout << "\tif(iter1 != iter2)\n\t{\n\t\tlock_guard<mutex> lockGuard(m_wq);\n\t\twait_queue.push_back(pair<int, std::function<int()>>(";
			cout << to_string(k+1);
			cout << ", fn" + to_string(k+1) + "));\n\t}\n";

			cout << "\telse\n\t{\n\t\tlock_guard<mutex> lockGuard(m_rq);\n\t\tready_queue.push_back(pair<int, std::function<int()>>(";
			cout << to_string(k+1);
			cout << ", fn" + to_string(k+1) + "));\n\t}\n";	
		}
		// for my_sort n stuff
		else
		{
            // cout << "********************" << get<3>(fn_call_info[k]).size() << "\n";
			for(int i = 0; i < get<3>(fn_call_info[k]).size(); i++)
			{
				cout << "\tpair<int,string> p" + to_string(k+1) + "_" + to_string(i+1) + "(" + to_string(k+1) + ", " + "\"" + get<3>(fn_call_info[k])[i] + "\");\n";
			}
			cout << "\t{\n\t\tlock_guard<mutex> lockGuard(m_sp);\n";
			for(int i = 0; i < get<3>(fn_call_info[k]).size(); i++)
			{
				cout << "\t\tspecial.push_back(p" + to_string(k+1) + "_" + to_string(i+1) + ");\n";
			}
			cout << "\t}\n";
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
			cout << "\t\tdone" + to_string(k+1) + " = true;}));\n";
			string pair_temp = "p_th_" + to_string(k+1);
			cout << "\tpair<int, atomic<bool>&> " + pair_temp + "(" + to_string(k+1) +", done" + to_string(k+1) + ");\n";
			cout << "\t{\n\t\tlock_guard<mutex> lockGuard(m_tt);\n\t\tthread_track.push_back(" + pair_temp + ");\n\t}\n\n";
 		}
	}
	for(auto x:return_types)
	{
		cout << "\tfor(auto &x:" + x + "_futures)";
		if(x.compare("void") == 0)
		{
			cout << "\n\t{\n\t\tx.wait();\n\t\t//x.get();\n\t}\n";
		}
		else
		{
			string temp = R"({
		//cout << x.get() << "\n";
        x.wait();
	})";
		cout << temp << "\n\n";
		}
	}
	string finish = R"(	gettimeofday(&stop, NULL);
    printf("%lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
    free(arr1);
    free(arr2);
	return 0;
})";
	cout << finish << "\n\n";
}

int main()
{
	input_data();
	gen_headers();
	prologue();
	threadtrack();
	schedulingfn();
	mainfn();
}