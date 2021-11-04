import os
import subprocess

def get_return_type(f_name):
    # print(f_name)
    with open("input2.txt", 'r') as f:
        l = f.readlines()
        for i in l:
            i = i.split(";")
            t = i[0].split(",")
            if(t[0] == f_name):
                # print(t)
                return t[1]
            
    return "void"


def verify_for_sort(f_name):
    f_name = f_name.replace(".c", "")
    ret_type = get_return_type(f_name)
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
        <return_var><function_name>(arr, 5);
        printf("%d", is_sorted(arr, 5));
    }
    '''
    t = t.replace("<function_name>", f_name)
    if(ret_type is not "void"):
        t = t.replace("<return_var>", "")
    else:
        t = t.replace("<return_var>", ret_type + " t = ")
    return t

def verify_for_max(f_name):
    f_name = f_name.replace(".c", "")
    ret_type = get_return_type(f_name)
    t = r'''
    #include <stdio.h>

    int main()
    {
        int arr[] = {1,6,2,8,5};
        // get return type
        <return_var><function_name>(arr, 5);
        printf("%d", t == 8);
    }
    '''
    t = t.replace("<function_name>", f_name)
    if(ret_type is "void"):
        t = t.replace("<return_var>", "")
    else:
        t = t.replace("<return_var>", ret_type + " t = ")
    return t


def verify_for_min(f_name):
    f_name = f_name.replace(".c", "")
    ret_type = get_return_type(f_name)
    t = r'''
    #include <stdio.h>

    int main()
    {
        int arr[] = {1,6,2,8,5};
        // get return type
        int t = <function_name>(arr, 5);
        printf("%d", t == 1);
    }
    '''
    t = t.replace("<function_name>", f_name)
    if(ret_type is not "void"):
        t = t.replace("<return_var>", "")
    else:
        t = t.replace("<return_var>", ret_type + " t = ")
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
    if("sort" in f_name):
        m = verify_for_sort(f_name)
    elif("max" in f_name):
        m = verify_for_max(f_name)
    elif("min" in f_name):
        m = verify_for_min(f_name)
    with open(fi, "r") as f:
        contents = f.read()
    fi = "q_" + fi
    with open(fi, "w") as f:
        f.write(contents + m)
    return run_verification(fi)
        
if __name__ == "__main__":
    print(verify("min.c"))