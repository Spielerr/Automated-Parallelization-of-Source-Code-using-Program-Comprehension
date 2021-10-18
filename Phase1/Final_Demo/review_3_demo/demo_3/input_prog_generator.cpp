#include <iostream>
#include <stdlib.h>
using namespace std;

void gen_fn()
{
    cout << R"(void transform(int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int temp = 0;
        }
    }
})";
    cout << "\n\n";
}

void gen_main(int arr_size, int fn_calls)
{
    cout << "int main()\n{\n";

    for(int i = 0; i < fn_calls; ++i)
    {
        cout << "\ttransform(" << arr_size << ");\n";
    }
    cout << "}\n";
}

int main(int argc, char** argv)
{
    int array_size = atoi(argv[1]);
    int no_fn_calls = atoi(argv[2]);
    
    cout << "#include <iostream>\n\nusing namespace std;\n\n";
    gen_fn();
    gen_main(array_size, no_fn_calls);
}