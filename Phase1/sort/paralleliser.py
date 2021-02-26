import sys
import re


def main():
    filename = sys.argv[1]
    with open(filename, "r") as programFile, open("parallelCode.cpp", "w+") as outfile:
        outfile.write('#include <iostream>\n#include "parallel.h"\n')
        program = programFile.read().split("\n")
        for line in program:
            m = re.search(r"\(\w*\s*(\w*)\s*,\s*\w*\s*(\w*).*", line)

            if m:
                var = m.group(1)
                length = m.group(2)

                outfile.write("{} = vectorise({});\n".format(var + "Vector", var))
                outfile.write("quicksort({}Vector,{},0);\n".format(var, length))
                outfile.write("deVectorise({}Vector, {});\n".format(var, var))


main()