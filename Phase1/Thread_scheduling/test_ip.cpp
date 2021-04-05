#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<algorithm>
#define DEBUG 0;

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

int main()
{
    vector<string> return_types;

    //data structure that holds the data from input.txt
    //it has the functions which have a write dependency along with the 
    //list of arguments that are being written into
    vector<pair<string, vector<string>>> fns_write_dep;

    string dependencies;

    ifstream file_1("input.txt");

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
            else
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
            if(j.first.compare("")!=0)
            {
                cout<<j.first<<":\n";
                for(auto k: j.second)
                {
                    cout<<k<<"\n";
                }
            }
            
        }

        cout<<"\n\n";
    }

    #endif


    //finding the number of the last function which is changing its argument(sort - arr2)


}

