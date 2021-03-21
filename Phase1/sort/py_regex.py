import re
import sys

# fn_name =  sys.argv[1]

# regex - \bsort.*\(((.*?)\s*,?\s*[a-zA-Z_][a-zA-Z_0-9]*=(0[xX][0-9a-fA-F]+))\s*,?\s*(.*)\).*

re_sort = r'#0.*?\bsort.*\(((.*?)\s*,?\s*[a-zA-Z_][a-zA-Z_0-9]*=(0[xX][0-9a-fA-F]+))\s*,?\s*(.*)\).*'

gdb_input = readline()

m = re.search(re_sort,gdb_input)

if m:
    pointer_address = m.group(3)

    re_id_size = r'\b(.*?)=.*'

    if m.group(2):
        var = m.group(2)
        m2 = re.search(re_id_size,var)
        if m2:
            size_id = m2.group(1)
        
    elif m.group(4):
        var = m.group(4)
        m2 = re.search(re_id_size,var)
        if m2:
            size_id = m2.group(1)

    

    re_fn_call = r'#1.*?([a-zA-Z_][a-zA-Z_0-9]*)=' + pointer_address

    m3 = re.search(re_fn_call,gdb_input)

    if m3:
        iterable_id = re.group(1)

    



