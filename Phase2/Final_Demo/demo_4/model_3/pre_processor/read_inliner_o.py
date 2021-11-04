import re

file_ip = open("inliner_o_lara.txt",'r')
ip_str = file_ip.read()
file_ip.close()

file_input = open("inliner.txt","w")
pat_ip1 = r"Start of inliner.txt\n(.*)\nEnd of inliner.txt"
input5 = re.search(pat_ip1,ip_str,re.S)

if input5:
    file_input.write(input5.group(1))

file_input.close()