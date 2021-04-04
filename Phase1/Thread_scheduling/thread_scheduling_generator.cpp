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
    cout<<"vector<vector<string>> args{{\"arr1\",\"n\"}, {\"arr1\",\"n\"}, {\"arr1\",\"n\"}, {\"arr2\",\"n\"}, {\"arr2\",\"n\"}, {\"arr2\",\"n\"}};\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";


}