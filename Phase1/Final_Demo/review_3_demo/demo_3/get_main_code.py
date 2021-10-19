import re

file_ip = open("input_prog_test.cpp","r")

ip = file_ip.read()

file_ip.close()

pat = r"int main\(.*?\)(.*)"

match = re.search(pat,ip,re.S)

file_op = open("main_code_client.txt","w")

if match:
    #print(match.group(1))
    file_op.write(match.group(1))

file_op.close()

new_client = re.sub(pat,"",ip,flags=re.S)
file_ip = open("input_prog_test.cpp","w")
file_ip.write(new_client)
file_ip.close()