#include<iostream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#define DEBUG 1

using namespace std;

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

int main()
{
    
    //data structure that holds the data from input.txt
    //it has the functions which have a write dependency along with the 
    //list of arguments that are being written into
    vector<pair<string, vector<string>>> fns_write_dep;

    string dependencies_1, dependencies;

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

    string dependencies_3;

    ifstream file_3("input3.txt");

    //data structure that stores the info from input3.txt
    // stores it in the order of function calls
    // vector consists of [function being called, return type of the function, variable to which the value is stored, line number of the function call]
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

    #if DEBUG

    cout<<"testing whether data is stored in the f3_ret_var_lineno data structure properly\n";

    for(auto i : f3_ret_var_lineno)
    {
        for(auto j : i)
        {
            cout<<j<<"\t";
        }

        cout<<"\n";
    }    

    cout<<"\n";
    #endif



    //DD1
    // all return types
    
    vector<string> return_types;

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
    vector<vector<string>> all_fn_args;

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

    int sp_c = fns_write_dep.size();

    #if DEBUG
    cout<<"The total number of functions changing their arguments are: "<<sp_c<< "\n";
    #endif

    // DD4
    // wr_q stores the total number of functions not changing their arguments (like min, max)
    // in our case, it is 4 (2 min and 2 max fn calls)
    int wr_q = order_fn_calls_types.size() - fns_write_dep.size();

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
    vector<tuple<string, int, vector<string>, vector<string>>> fn_call_info;
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

