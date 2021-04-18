import re

file_ip = open("client.cpp","r")

ip = file_ip.read()

file_ip.close()

pat = r"int main\(.*?\)(.*)"

match = re.search(pat,ip,re.S)

file_op = open("main_code_client.txt","w")

if match:
    #print(match.group(1))
    file_op.write(match.group(1))

