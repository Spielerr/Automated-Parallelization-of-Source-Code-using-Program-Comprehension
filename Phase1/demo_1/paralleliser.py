import sys
import re

# def func(line):
#     m = re.search(r".*\(((.*?)\s*,?\s*([a-zA-Z_][a-zA-Z_0-9]*=0[xX][0-9a-fA-F]+))\s*,?\s*(.*)\).*", line)
#     if m:
#         return m


def main():
    filename = sys.argv[1]
    with open(filename, "r") as infile, open("generated_parallel.cpp", "w+") as outfile, open("out.txt", "r") as programFile:
        outfile.write('#include <iostream>\n#include "parallel_qs.h"\n')
        program = programFile.read().split("\n")
        m = 0
        m1 = 0
        ptr_addr = 0
        for line in program:
            if not m:
                m = re.search(r"\bsort.*\(((.*?)\s*,?\s*[a-zA-Z_][a-zA-Z_0-9]*=(0[xX][0-9a-fA-F]+))\s*,?\s*(.*)\).*", line)
            if m and not m1:
                ptr_addr = m.group(3)
                m1 = re.search(r"#1.*([a-zA-Z_][a-zA-Z_0-9]*)\s*=\s*"+ptr_addr+".*:(\d+)", line)
            if m and m1:
                # ptr_addr = m.group(3)
                # # length = m.group(2)
                # outfile.write("")
                # outfile.write("{} = vectorise({});\n".format(var + "Vector", var))
                # outfile.write("quicksort({}Vector,{},0);\n".format(var, length))
                # outfile.write("deVectorise({}Vector, {});\n".format(var, var))
                ptr_addr = m.group(3)
                # print(ptr_addr)
                var = m1.group(1)
                size = m1.group(2)
                length = 0

                grp = m.group(2) if m.group(2) else m.group(4)

                length = re.search(r".*[a-zA-Z_][a-zA-Z_0-9]*\s*=\s*(\d+).*", grp).group(1)


                lines = infile.readlines()
                # print(len(lines))

                for i in range(int(size)-1):
                    outfile.write(lines[i])

                outfile.write("{} = vectorise({}, {});\n".format("auto " + var + "Vector", var, length))
                outfile.write("my_sort({}Vector, 0, {});\n".format(var, int(length) - 1))
                outfile.write("deVectorise({}Vector, {});\n".format(var, var))

                for i in range(1, len(lines) - (int(size)-1)):
                    outfile.write(lines[int(size) + i - 1])
                break





main()