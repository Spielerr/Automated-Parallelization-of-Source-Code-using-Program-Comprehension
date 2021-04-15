import re

file_ip = open("client.cpp","r")

ip = file_ip.read()

file_ip.close()

pat = r"int main\(.*?\)(.*)"

match = re.search(pat,ip,re.S)

if match:
    print(match.group(1))

