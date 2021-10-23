import os
import subprocess

def main_for_sort(f_name):
    f_name = f_name.replace(".c", "")
    t = r'''
    #include <stdio.h>
    int is_sorted(int *a, int n)
    {
        for(int i=1; i<n; ++i)
        {
            if(a[i-1] > a[i])
            {
                return 0;
            }
        }
        return 1;
    }

    int main()
    {
        int arr[] = {1,6,2,8,5};
        <function_name>(arr, 5);
        printf("%d", is_sorted(arr, 5));
    }
    '''
    t = t.replace("<function_name>", f_name)
    return t

def run_verification(f):
    k = os.system("gcc " + f)
    if not k:
        out = subprocess.Popen(["./a.out"], 
            stdout=subprocess.PIPE, 
            stderr=subprocess.STDOUT)
        stdout, stderr = out.communicate()
        # print(f + "  ", stdout)
        try:
            stdout = int(stdout)
            return stdout
        except:
            pass
            # print(stdout, stderr)
        os.system("rm *.out")
        return 0

def verify(f_name):
    fi = f_name
    m = main_for_sort(f_name)
    with open(fi, "r") as f:
        contents = f.read()
    fi = "q_" + fi
    with open(fi, "w") as f:
        f.write(contents + m)
    return run_verification(fi)
        
