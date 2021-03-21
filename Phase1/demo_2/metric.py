import resource
import subprocess
import time
import sys
from timeit import timeit

sequentialCode = sys.argv[1]
parallelCode = sys.argv[2]


testcase_size = 500

seqTime = {}
parallelTime = {}


for _ in range(3):

    begin = resource.getrusage(resource.RUSAGE_CHILDREN)
    seq = subprocess.Popen(
        ["./" + sequentialCode, str(testcase_size).encode("utf-8")],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
    )
    # seq.stdin.write(bytes(str(testcase_size), "utf-8"))
    # seq.communicate(input = (str(testcase_size)).encode('utf-8'))
    out, err = seq.communicate()

    end = resource.getrusage(resource.RUSAGE_CHILDREN)
    seq.stdin.close()
    seqTime[str(testcase_size)] = end.ru_utime - begin.ru_utime

    begin = resource.getrusage(resource.RUSAGE_CHILDREN)

    para = subprocess.Popen(
        ["./" + parallelCode, str(testcase_size).encode("utf-8")],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
    )
    # para.stdin.write(bytes(str(testcase_size), "utf-8"))
    # para.communicate(input = (str(testcase_size)).encode('utf-8'))
    out, err = para.communicate()

    para.stdin.close()
    end = resource.getrusage(resource.RUSAGE_CHILDREN)

    # para.stdin.close()
    parallelTime[str(testcase_size)] = end.ru_utime - begin.ru_utime

    testcase_size *= 1000

print(seqTime)
print(parallelTime)