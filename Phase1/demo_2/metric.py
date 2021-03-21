import argparse
import subprocess
import time
import sys

parallelCode = sys.argv[2]
sequentialCode = sys.argv[1]


testcase_size = 1000

seqTime = []
parallelTime = []


for _ in range(100):
    begin = time.time()
    seq = subprocess.Popen(
        ["./" + sequentialCode], stdin=subprocess.PIPE, stdout=subprocess.PIPE
    )
    seq.stdin.write(bytes(str(testcase_size), "utf-8"))
    seq.communicate()
    seq.stdin.close()
    end = time.time()
    seqTime.append(end - begin)

    begin = time.time()

    para = subprocess.Popen(
        ["./" + parallelCode], stdin=subprocess.PIPE, stdout=subprocess.PIPE
    )
    para.stdin.write(bytes(str(testcase_size), "utf-8"))
    para.communicate()
    para.stdin.close()
    end = time.time()
    parallelTime.append(end - begin)

    testcase_size *= 10

print(seqTime)
print(parallelTime)