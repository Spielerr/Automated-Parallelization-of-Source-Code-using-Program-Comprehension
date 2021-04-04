#include<iostream>
using namespace std;

void gen_headers()
{
    cout<<"#include<vector>\n";
    cout<<"#include<deque>\n";
    cout<<"#include<iostream>\n";
    cout<<"#include \"CTPL/ctpl_stl.h\"\n";
    cout<<"#include <thread>\n";
    cout<<"#include <atomic>\n";
    cout<<"#include <unistd.h>\n";
    cout<<"#include \"prog.cpp\"\n";
    cout<<"#include <functional>\n";
    cout<<"using namespace std;\n";
    
}

void prologue()
{
    cout<<"int num_threads = thread::hardware_concurrency();\n";
    cout<<"ctpl::thread_pool tp(num_threads);\n";
    cout<<"vector<future<void>> void_futures;\n";
    cout<<"vector<future<int>> int_futures;\n";
    cout<<"vector<pair<int, string>> special;\n";
    cout<<"vector<pair<int, atomic<bool>&>> thread_track;\n";

    //change arr1 and n based on the output files from lara
    cout<<"vector<vector<string>> args{{\"arr1\",\"n\"}, {\"arr1\",\"n\"}, {\"arr1\",\"n\"}, {\"arr2\",\"n\"}, {\"arr2\",\"n\"}, {\"arr2\",\"n\"}};\n";

    cout<<"deque<pair<int, std::function<int(int)>>> ready_queue;\n";
    cout<<"deque<pair<int, std::function<int(int)>>> wait_queue;\n";
    cout<<"atomic<int> special_changed(0);\n";
    cout<<"string remove_fn;\n\n";

    cout<<"class Find_special\n";
    cout<<"{\n";
    cout<<"     private:\n";
    cout<<"     int x_;\n";
    cout<<"     public:\n";
    cout<<"     Find_special(int x) : x_(x) {}\n";
    cout<<"     bool operator()(pair<int, string> i)\n";
    cout<<"     {\n";
    cout<<"          return i.first == x_;\n";
    cout<<"     }\n";
    cout<<"};\n\n";


    cout<<"class Find_special2\n";
    cout<<"{\n";
    cout<<"     private:\n";
    cout<<"     string x_;\n";
    cout<<"     public:\n";
    cout<<"     Find_special2(string x) : x_(x) {}\n";
    cout<<"     bool operator()(pair<int, string> i)\n";
    cout<<"     {\n";
    cout<<"          if(x_.compare(i.second) == 0)\n";
    cout<<"          {\n";
    cout<<"              return true;\n";
    cout<<"          }\n";
    cout<<"          return false;\n";
    cout<<"     }\n";
    cout<<"};\n";

    
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";


}