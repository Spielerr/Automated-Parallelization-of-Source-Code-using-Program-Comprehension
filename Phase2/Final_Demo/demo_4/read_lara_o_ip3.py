import re

file_ip = open("test_o_lara.txt",'r')

ip_str = file_ip.read()

file_ip.close()

file_input = open("input3.txt","w")


pat_ip1 = r"Start of Input3.txt\n(.*)\nEnd of Input3.txt"
input3 = re.search(pat_ip1,ip_str,re.S)

if input3:
    #print(input3.group(1))
    file_input.write(input3.group(1))


file_input.close()