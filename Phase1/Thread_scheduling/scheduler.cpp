#include <thread>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
	multimap<string, vector<string>> deps;
	multimap<string, vector<string>> fn_calls;

	string dependencies;
	string fn_call;

	ifstream MyReadFile1("input.txt");
	while (getline (MyReadFile1, dependencies)) 
	{
		vector<string> result;
		stringstream s_stream(dependencies);
		while(s_stream.good()) 
		{
			string substr;
			getline(s_stream, substr, ',');
			result.push_back(substr);
		}
		pair<string, vector<string>> temp;
		temp.first = result[0];
		for(int i=1; i<result.size(); i++)
		{
			temp.second.push_back(result[i]);
		}
		deps.insert(temp);
	}

	multimap <string, vector<string>>::iterator itr;
    for (itr = deps.begin(); itr != deps.end(); ++itr)
    {
        cout << itr->first << '\t' << itr->second[0] << '\n';
    }

    // cout << (deps.find("my_sort"))->second[0] << '\n';



	// Close the file
	MyReadFile1.close();
	cout << '\n';
	ifstream MyReadFile2("input2.txt");
	vector<pair<string, vector<string>>> order;
	while (getline (MyReadFile2, fn_call)) 
	{
		vector<string> result;
		stringstream s_stream(fn_call);
		while(s_stream.good()) 
		{
			string substr;
			getline(s_stream, substr, ',');
			result.push_back(substr);
		}
		pair<string, vector<string>> temp;
		temp.first = result[0];
		for(int i=1; i<result.size(); i++)
		{
			temp.second.push_back(result[i]);
		}
		// fn_calls.insert(temp);
		order.push_back(temp);
	}

	// multimap <string, vector<string>>::iterator itr;
    // for (itr = fn_calls.begin(); itr != fn_calls.end(); ++itr)
    // {
    //     cout << itr->first << '\t' << itr->second[0] << '\n';
    // }

    for(auto x:order)
    {
    	cout << x.first << '\t' << x.second[0] << '\n';
    }

	// Close the file
	MyReadFile2.close();

	// cout << dependencies << '\n';
	// cout << fn_calls << '\n';
}