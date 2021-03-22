import resource
import subprocess
import time
import sys
from timeit import timeit

sequentialCode = sys.argv[1]
parallelCode = sys.argv[2]


testcase_size = 100

seqTime = {}
parallelTime = {}


for _ in range(5):
    seqAvg = []
    paraAvg = []
    for _ in range(5):
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
        seqAvg.append(end.ru_utime - begin.ru_utime)

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
        paraAvg.append(end.ru_utime - begin.ru_utime)

    parallelTime[str(testcase_size)] = sum(paraAvg[1:]) / 4
    seqTime[str(testcase_size)] = sum(seqAvg[1:]) / 4
    testcase_size *= 10


print(seqTime)
print(parallelTime)