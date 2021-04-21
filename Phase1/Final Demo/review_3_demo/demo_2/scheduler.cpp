#include <bits/stdc++.h>

#include <future>
#include <iostream>
#include <thread>
using namespace std;

bool check_key(map<string, int>& m, string& key) 
{ 
    return !(m.find(key) == m.end()); 
}

// checks if function makes any write to the paramaters
template <typename ptr_t1, typename ptr_t2>
bool is_writing_fn(ptr_t1 order, ptr_t2 write_fns, int fn_num, int write_fn_num) 
{
    while (write_fn_num <= fn_num) 
    {
        if (order->first == write_fns->first) 
        {
            return true;
        }

        ++write_fns;
        ++write_fn_num;
    }

    return false;
}


// checks if no paramter of the function is written into
bool no_write_params(pair<string, vector<string>>& item, map<string, int>& vars_write) 
{
    for (auto it = item.second.begin(); it != item.second.end(); ++it) 
    {
        if (check_key(vars_write, *it) && vars_write[*it] > 0) 
        {
            return false;
        }
    }

    return true;
}


int main() 
{
    // stores only those functions which are writing to one or more of its arguments (multimap)
    multimap<string, vector<string>> deps;

    // stores only those functions which are writing to one or more of its arguments (vector)
    vector<pair<string, vector<string>>> vec_deps;

    // number of times a variable is being written into
    map<string, int> var_write_count;

    // temporaries to store strings when inputting from file
    string dependencies;
    string fn_call;

    // reading in the write dependencies file
    ifstream MyReadFile1("input.txt");
    while (getline(MyReadFile1, dependencies)) 
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

        for (int i = 1; i < result.size(); i++) 
        {
            temp.second.push_back(result[i]);
            if (!check_key(var_write_count, result[i])) 
            {
                var_write_count[result[i]] = 0;
            }
        }

        // pushing into the multimap
        deps.insert(temp);

        // pushing into the vector
        vec_deps.push_back(temp);
    }

    // Close the file
    MyReadFile1.close();


    // reading in the order of function calls
    ifstream MyReadFile2("input2.txt");

    // vector to store the order of function calls
    vector<pair<string, vector<string>>> order;
    while (getline(MyReadFile2, fn_call)) 
    {
        vector<string> result;
        stringstream s_stream(fn_call);
        while (s_stream.good())
        {
            string substr;
            getline(s_stream, substr, ',');
            result.push_back(substr);
        }

        pair<string, vector<string>> temp;
        temp.first = result[0];
        for (int i = 1; i < result.size(); i++) 
        {
            temp.second.push_back(result[i]);
        }
        order.push_back(temp);
    }

    // reordered fn call
    vector<pair<string, vector<string>>> my_order;              

    // temp to maintain order of fn that do not have write operations
    vector<pair<string, vector<string>>> temp_write_dep_order;  

    // number of writes done on given variable
    map<string, int> vars_write(var_write_count);  

    // iterators
    auto iterator_my_order = my_order.begin();
    auto iterator_order = order.begin();
    auto iterator_write_order = vec_deps.begin();

    int fn_num = 0;
    int write_fn_num = 0;

    while (iterator_order != order.end()) 
    {
        // if no paramter needs any write operations, then add to my_order as it can be executed
        if (no_write_params(*iterator_order, vars_write)) 
        {
            my_order.push_back(*iterator_order);
        } 
        else 
        {
            // maintain original order of fns that need write to occur in temp vector
            temp_write_dep_order.push_back(*iterator_order);
        }

        // computes number of writes have occured to a given variable
        if (is_writing_fn(iterator_order, iterator_write_order, fn_num, write_fn_num)) 
        {
            for (auto it = iterator_write_order->second.begin(); it != iterator_write_order->second.end(); ++it) 
            {
                vars_write[*it] += 1;
            }

            cout << endl;
            write_fn_num++;
            ++iterator_write_order;
        }

        ++iterator_order;
        fn_num++;
    }

    // insert the temp fn order into final reordered fn order
    my_order.insert(my_order.end(), temp_write_dep_order.begin(), temp_write_dep_order.end());

    /*
    for(auto x:my_order)
    {
        cout << x.first << '\n';
    }
    cout << '\n';
    */

    auto iterator_order_of_exec = my_order.begin();
    iterator_write_order = vec_deps.begin();
    map<string, int> vars_for_future(var_write_count);
    fn_num = 0;
    write_fn_num = 0;

    while (iterator_order_of_exec != my_order.end()) 
    {
        // sets future (wait for write) for all variables needed for current function
        for (auto it = iterator_order_of_exec->second.begin(); it != iterator_order_of_exec->second.end(); ++it) 
        {
            if (var_write_count.find(*it) != var_write_count.end() && var_write_count[*it] != 0) 
            {
                cout << "std::future<void> f_" << *it << "_" << var_write_count[*it] << "= p_" << *it << "_" << var_write_count[*it] - 1
                     << ".get_future();\n";
                var_write_count[*it] -= 1;
            }
        }
        // Create promise for all the variable the current function will write to
        if (is_writing_fn(iterator_order_of_exec, iterator_write_order, fn_num, write_fn_num)) 
        {
            for (auto it = iterator_write_order->second.begin(); it != iterator_write_order->second.end(); ++it) 
            {
                cout << "std::promise<void> p_" << *it << "_" << var_write_count[*it];
                vars_for_future[*it] += 1;
                var_write_count[*it] += 1;
            }
            
            cout << endl;
            write_fn_num++;
            ++iterator_write_order;
        }

        cout << "thread ti(" << iterator_order_of_exec->first << ", params);" << endl;
        fn_num++;
        ++iterator_order_of_exec;
    }
    return 0;
}