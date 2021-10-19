#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
#define DEBUG 0

// all return types
vector<string> return_types;

// vector of vector of strings containing all fn args - should remove
vector<vector<string>> all_fn_args;

/*
string is for the fn name
int is a flag variable to signify the type of fn call
	0 for those fns which change their argument (like my_sort)
	1 for the others (like min, max) - which don't change their arguments

vector<string> is to store all the arguments(and not parameters) of the fn calls
the second vector<string> stores the arguments which are getting changed from those functions changing their arguments
if fn doesnt change anything (for cases of 1) just store an empty vector if possible, or just store 
all arguments like the first vector

how to work with tuples?
tuple <char, int, float> geek;
geek = make_tuple('a', 10, 15.5);
thank me later
*/
vector<tuple<string, int, vector<string>, vector<string>>> fn_call_info;

//stores line numbers (relative to main) of all fn calls
vector<int> fn_line_nos;

// stores the fn name, the return value variable name, and its data type, fn call line no, next usage line no (of the changed argument)
// if no return value, then store empty string
// maintain order of fn calls as it is, and every fn call should be present
// last field being -1 signifies that fn can complete on its own will - no need to be preempted
vector<tuple<string, string, string, int, int>> return_vars;

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

            //substr contains the function and its return type
            if(i==0)
            {
                stringstream s_stream_2(substr);
                int j = 0;

                while(s_stream_2.good())
                {
                    string substr2;
                    getline(s_stream_2, substr2, ',');

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
                vector<string> temp_v_s;
                pair<string, vector<string>> temp_p;

                while(s_stream_3.good())
                {
                    string substr3;
                    getline(s_stream_3, substr3, ',');

                    temp_v_s.push_back(substr3);
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

    string dependencies_3;
    ifstream file_3("input3.txt");

    //data structure that stores the info from input3.txt
    // stores it in the order of function calls
    // vector consists of [function being called, line number of the function call]
    vector<vector<string>> f3_ret_var_lineno;

    while(getline(file_3, dependencies_3))
    {
        vector<string> result_3;
        stringstream s_stream_3(dependencies_3);

        while(s_stream_3.good())
        {
            string substr_3;
            getline(s_stream_3,substr_3,' ');
            result_3.push_back(substr_3);
        }

        f3_ret_var_lineno.push_back(result_3);

    }

    file_3.close();

    for(int i = 0; i < f3_ret_var_lineno.size(); ++i)
    {
        fn_line_nos.push_back(stoi(f3_ret_var_lineno[i][1]));
    }


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


    ifstream file_4("input4.txt");
    string return_vars_info;
    while (getline(file_4, return_vars_info)) {
        tuple<string, string, string, int, int> temp_return_vars;
        int indx = 0;
        vector<string> store_string_info;
        vector<int> store_line_info;
        stringstream stream1(return_vars_info);
        while (stream1.good()) {
            string substring;
            getline(stream1, substring, ',');
            if (indx == 1 || indx == 2) {
                store_line_info.push_back(stoi(substring));
            } else {
                store_string_info.push_back(substring);
            }
            ++indx;
        }
        if (store_string_info.size() == 1) {
            store_string_info.push_back("");
            store_string_info.push_back("");
        }
        temp_return_vars = make_tuple(store_string_info[0], store_string_info[2], store_string_info[1], store_line_info[0], store_line_info[1]);
        return_vars.push_back(temp_return_vars);
    }
    file_4.close();

}

void gen_headers()
{
	string temp = R"(#include "thread_pool.hpp"
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
	)";
	cout << temp << '\n';

    string dependencies;

    ifstream file_ip_client("input_prog_test.cpp");

    while(getline(file_ip_client, dependencies))
    {    
        cout<<dependencies<<"\n";
    }
}

void prologue()
{
	cout<<"int num_threads = thread::hardware_concurrency();\n";
	cout<<"ThreadPool tp(num_threads);\n";

    string return_types_variant = "variant<";
    cout << "vector<pair<int, ";
	for(int i = 0; i < return_types.size(); ++i)
	{
        if(i != return_types.size() - 1)
        {
            // cout << "shared_future<" << return_types[i] << ">, ";
            return_types_variant += "shared_future<" + return_types[i] + ">, ";
        }
        else
        {
            // cout << "shared_future<" << return_types[i] << ">";
            return_types_variant += "shared_future<" + return_types[i] + ">";
        }
	}
    return_types_variant += ">";
    cout << return_types_variant;
    cout << ">> futures;\n";

    string variant_text = "variant<";
    for(int i = 0; i < return_types.size(); ++i)
	{
        if(i != return_types.size() - 1)
        {
            variant_text += "function<" + return_types[i] + "()>, ";
        }
        else
        {
            variant_text += "function<" + return_types[i] + "()>";
        }
	}
    variant_text += ">";

	cout << R"(mutex m_f;)";
    cout << "\n\n";

    string find_futures = R"(class Find_futures
{
	private:
	int ind_;

	public:
	Find_futures(int index) : ind_(index) {}
	bool operator()(pair<int,)";

    cout << find_futures << return_types_variant << ">" << " i)\n";
    cout << R"({
		if(i.first == ind_)
		{
			return true;
		}
		return false;
	}
};)";
    cout << "\n\n";
    cout << R"(template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
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
	vector<pair<int,)" << return_types_variant << ">>::iterator it;\n";

    cout << R"({
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
	vector<pair<int,)" << return_types_variant << ">>::iterator it;\n";
	

    cout << R"({
		lock_guard<mutex> lockGuard(m_f);
		it = find_if(begin(futures), end(futures), Find_futures(index));
	}
	// cout << it->first << "\n";

	visit(overloaded {
        [](auto n){ n.get(); },
		[](shared_future<void> n){ n.wait(); }
		}, 
		it->second);
})";

cout << "\n\n";
}

bool sort_by_field(const tuple<string, string, string, int, int>& a, const tuple<string, string, string, int, int>& b)
{
    return (get<3>(a) < get<3>(b));
}

void mainfn()
{
    string line;
    ifstream file_ip_main("main_code_client.txt");
    vector<string> main_ip;

    while(getline(file_ip_main, line))
    {    
        main_ip.push_back(line);
    }

    cout<<"int main(int argc, char **argv)\n";

    cout<<main_ip[1]<<"\n";

    int line_no_index = 2;

    sort(return_vars.begin(), return_vars.end(), sort_by_field);

	for(int k = 0; k < fn_call_info.size(); k++)
	{

        // printing client code up until present iteration function call
        for(int i = line_no_index; i <= fn_line_nos[k]; ++i)
        {

            for(int t_1 = 0; t_1 < return_vars.size(); ++t_1)
            {
                if((i == get<3>(return_vars[t_1])) && !(get<2>(return_vars[t_1]).empty()))
                {
                    // the declaration
                    cout << "\t" << get<2>(return_vars[t_1]) << " " << get<1>(return_vars[t_1]) << ";\n";
                }

                if(i == get<4>(return_vars[t_1]))
                {
                    // call find_future
                    if(!(get<2>(return_vars[t_1]).empty()))
                    {
                        cout << "\tfind_future(" << to_string(t_1+1) << ", " << get<1>(return_vars[t_1]) << ");\n";
                    }
                    else
                    {
                        cout << "\tfind_future(" << to_string(t_1+1) << ");\n";
                    }
                }
            }
            if(i != fn_line_nos[k])
                cout << main_ip[i] << '\n';
        }

        line_no_index = fn_line_nos[k] + 1;

        cout << "\t{\n\t\tlock_guard<mutex> lockGuard(m_f);\n";

        if(!get<2>(return_vars[k]).empty())
        {
            cout << "\t\tfutures.emplace_back(make_pair(" + to_string(k+1) + ", tp.Submit([&]()->" + get<2>(return_vars[k]) + "{\n\t\t\t " + 
            get<2>(return_vars[k]) + " temp = " + get<0>(fn_call_info[k]) + "(";

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

            cout << "\t\t\treturn temp;})));\n";
            cout << "\t}\n";
        }
        else
        {
            cout << "\t\tfutures.emplace_back(make_pair(" + to_string(k+1) + ", tp.Submit([&]{\n\t\t\t " + get<0>(fn_call_info[k]) + "(";

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

            cout << "\t\t\t})));\n";
            cout << "\t}\n";
        }
        
    }

    //printing client code after last fn call
    for(int i = line_no_index; i < main_ip.size()-1; ++i)
    {
        for(int t_1 = 0; t_1 < return_vars.size(); ++t_1)
        {
            if(i == get<4>(return_vars[t_1]))
            {
                // call find_future
                if(!(get<2>(return_vars[t_1]).empty()))
                {
                    cout << "\tfind_future(" << to_string(t_1+1) << ", " << get<1>(return_vars[t_1]) << ");\n";
                }
                else
                {
                    cout << "\tfind_future(" << to_string(t_1+1) << ");\n";
                }
            }
        }

        cout << main_ip[i] << '\n';
    }

	string wait_on_futures = R"(
    for (auto &x : futures)
	{
		visit([](auto n) { (n).wait();}, x.second);
	}
    )";

    cout << wait_on_futures << endl;
    cout << "}\n";
}

int main()
{
	input_data();
	gen_headers();
	prologue();
	mainfn();
}