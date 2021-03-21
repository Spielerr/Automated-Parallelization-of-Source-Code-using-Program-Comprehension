import argparse
import subprocess
import time
import sys
from timeit import timeit

sequentialCode = sys.argv[1]
parallelCode = sys.argv[2]


testcase_size = 50000000

seqTime = []
parallelTime = []


for _ in range(2):

    begin = time.perf_counter()
    seq = subprocess.Popen(
        ["./" + sequentialCode, str(50000000)], stdin=subprocess.PIPE, stdout=subprocess.PIPE
    )
    seq.stdin.write(bytes(str(testcase_size), "utf-8"))
    # seq.communicate(input = (str(testcase_size)).encode('utf-8'))
    out, err = seq.communicate()
    print(out.decode('utf-8'), err)
    end = time.perf_counter()
    seq.stdin.close()
    seqTime.append(end - begin)

    begin = time.perf_counter()

    para = subprocess.Popen(
        ["./" + parallelCode, str(50000000)], stdin=subprocess.PIPE, stdout=subprocess.PIPE
    )
    para.stdin.write(bytes(str(testcase_size), "utf-8"))
    # para.communicate(input = (str(testcase_size)).encode('utf-8'))
    out, err = para.communicate()
    print(out, err)
    para.stdin.close()
    end = time.perf_counter()

    # para.stdin.close()
    parallelTime.append(end - begin)

    testcase_size *= 10

print(seqTime)
print(parallelTime)