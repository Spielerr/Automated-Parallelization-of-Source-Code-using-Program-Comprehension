import re

file_ip = open("test_o_lara.txt",'r')

ip_str = file_ip.read()

file_ip.close()

file_input = open("input2.txt","w")


pat_ip1 = r"Start of Lara Output\ninput2.txt:\n(.*)\nEnd of input2.txt"
input2 = re.search(pat_ip1,ip_str,re.S)

if input2:
    #print(input2.group(1))
    file_input.write(input2.group(1))


file_input.close()

file_input_2 = open("input.txt","w")

pat_ip2 = r"input.txt:\n(.*)\nEnd of input.txt"
input1 = re.search(pat_ip2,ip_str,re.S)

if input1:
    #print(input1.group(1))
    file_input_2.write(input1.group(1))
