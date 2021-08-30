file_ip = open("print_output_gen_pgm.txt","r")
ip_str = file_ip.readlines()


for i in range(len(ip_str)):
    if 'Time Taken' in ip_str[i]:
        rem_ind = i

time_taken = ip_str.pop(rem_ind)

ip_str = sorted(ip_str, key = lambda x: int(x.split(":")[0]))

for line in ip_str:
    print(line, end = '')

print(time_taken)

