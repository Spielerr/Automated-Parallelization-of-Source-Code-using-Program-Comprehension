import re
file_ip = open("test_o_lara_5.txt",'r')

ip_str = file_ip.read()

file_ip.close()

file_input = open("input5.txt","w")


pat_ip1 = r"Start of Input5.txt\n(.*)\nEnd of Input5.txt"
input5 = re.search(pat_ip1,ip_str,re.S)

if input5:
    #print(input5.group(1))
    file_input.write(input5.group(1))


file_input.close()