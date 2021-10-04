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
import pandas as  pd
import pickle
input_file = open("pre_processor/input5.txt", "r")
text = input_file.readlines()
input_file.close()

#dictionary that maps every function to its start line number and end line number
fn_dict = {}

for i in text:
    fn_name, st_l, end_l = i.split()
    fn_dict[fn_name] = [int(st_l), int(end_l)]

# print(fn_dict)



#input sequential program
input_seq_pgm = open("pre_processor/inline_input.c", "r")
pgm_inp = input_seq_pgm.readlines()
input_seq_pgm.close()

inline_fn_input = open("pre_processor/inliner.txt")
fn_calls = inline_fn_input.readlines()
inline_fn_input.close()

# Start of inliner.txt
# input 2
# bubbleSort 3
# output 4
# End of inliner.txt

result = pd.DataFrame(columns=['id', 'code', 'name'])

#To be handled:
#   File naming in case of overloading
for i in range(len(fn_calls)):
    t1, t2 = tuple(fn_calls[i].split())
    t2 = int(t2)
    out_file = open(t1 + ".c", 'w')
    result.loc[len(result.index)] = [i, "".join(pgm_inp[fn_dict[t1][0]:fn_dict[t1][1]]), t1]
    out_file.write("".join(pgm_inp[fn_dict[t1][0]:fn_dict[t1][1]]))

outfile = "data/query.pkl"
with open(outfile, 'wb') as file_handler:
    pickle.dump(result, file_handler)







