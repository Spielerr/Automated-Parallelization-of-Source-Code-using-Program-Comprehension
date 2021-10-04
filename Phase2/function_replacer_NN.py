# import re
# input_file = open("example_pgm.cpp","r")
# text = input_file.readlines()
# text = "".join(text)

# pat = r"(add\(.*?\)\s*{.*?})"

# m = re.search(pat, text, re.S)

# if m:
#     print(m.span())
# else:
#     print("test")

from getpass import getpass
from mysql.connector import connect, Error

input_file = open("input5.txt", "r")
text = input_file.readlines()
input_file.close()

#dictionary that maps every function to its start line number and end line number
fn_dict = {}

for i in text:
    fn_name, st_l, end_l = i.split()
    fn_dict[fn_name] = [int(st_l), int(end_l)]

# print(fn_dict)



#input sequential program
input_seq_pgm = open("test_input.c", "r")
pgm_inp = input_seq_pgm.readlines()
input_seq_pgm.close()



'''
assume output file from program comprehension phase format
pgm_comp_output.txt
function_name_in_original_pgm mapped_function_name
'''
#program comprehension output
pgm_comp_file = open("pgm_comp_output.txt", "r")
pgm_comp_text = pgm_comp_file.readlines()
pgm_comp_file.close()

fn_mapping_dict = {}
for line in pgm_comp_text:
    orig_fn, map_fn = line.split()
    fn_mapping_dict[orig_fn] = map_fn


#output parallelized program
output_par_pgm = open("test_output.c", "w")
pgm_out = '''#include <parallel/algorithm>
#include <parallel/numeric>\n'''

test_new = '''
int test(int a)
{
    return a + 4;
}
'''

add_new = '''
int add(int a, int b)
{
    return a + b + 4;
}
'''

prev = 0
n = len(pgm_inp)

try:
    with connect(
        host = "localhost",
        user = "test_user",
        password = "test_user123",
        database = "parallel_code"
    ) as connection:
        # print(connection)
        with connection.cursor() as cursor:
            for func_name in fn_dict:
                start_l = fn_dict[func_name][0]
                end_l = fn_dict[func_name][1]

                pgm_out = pgm_out + "".join(pgm_inp[prev:start_l-1])
                prev = end_l

                mapped_fn_name = fn_mapping_dict[func_name]
                
                # execute select statement based on key in present iteration
                select_fn_name = "SELECT parallel_code FROM mapping WHERE fn_name=\"" + mapped_fn_name + "\";"
                cursor.execute(select_fn_name)
                result = cursor.fetchall()
                
                # if key found in db
                # will have to have a newline at the end of the parallel code
                if(len(result)):
                    print(mapped_fn_name, " key found")
                    mapped_parallel_fn = (result[0][0]).replace("__my_mapped_parallel_function_",func_name)
                    pgm_out = pgm_out + mapped_parallel_fn
                else:
                    print(mapped_fn_name, " key not found")
                    pgm_out = pgm_out + "".join(pgm_inp[start_l-1:end_l])
                    
                # if mapped_fn_name == "test_new":
                #     pgm_out = pgm_out + test_new
                    

                # elif mapped_fn_name == "add_new":
                #     pgm_out = pgm_out + add_new
except Error as e:
    print(e)

pgm_out = pgm_out + "".join(pgm_inp[prev:n])

output_par_pgm.write(pgm_out)
output_par_pgm.close()


    
#handle case where function has no mapping
#depends on what input is given





