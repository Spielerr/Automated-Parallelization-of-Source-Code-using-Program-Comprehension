import re

# Won't work for single line functions
def remove_main(lines):
    lines2 = []
    lines3 = []
    pat = r"int main\(.*?\)"
    pat1 = r"\s*\{\s*"
    pat2 = r"\s*\}\s*"
    num_ = 0
    found = 0
    for i in range(len(lines)):
        to_append = 0
        if(not found and re.search(pat, lines[i])):
            print("1 ", lines[i])
            found = 1
            lines3.append(lines[i])
            continue
        if(not found):
            lines2.append(lines[i])
        if(found and re.search(pat1, lines[i])):
            num_ += 1
            # lines3.append(lines[i])
            to_append = 1
            print("2 ", lines[i])
        if(found and re.search(pat2, lines[i])):
            num_ -= 1
            # lines3.append(lines[i])
            to_append = 1
            print("3 ", lines[i])
        if(num_ != 0 or to_append):
            print(lines[i])
            lines3.append(lines[i])
        if(found and num_ == 0):
            found = 0

    return ("".join(lines2), "".join(lines3))


file_ip = open("testfile_demo_4.cpp","r")
ip = file_ip.readlines()
file_ip.close()

ip_without_main, main = remove_main(ip)

file_op = open("main_code_client.txt","w")
file_op.writelines(main)
file_op.close()

file_ip = open("testfile_demo_4.cpp","w")
file_ip.writelines(ip_without_main)
file_ip.close()