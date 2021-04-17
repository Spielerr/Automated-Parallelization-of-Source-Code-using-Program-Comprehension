#!/bin/bash


g++ -g client_k.cpp prog.cpp -o seq

n_values=(1000 10000 100000 500000 750000 1000000)

# n_values[0]=1000
# n_values[1]=10000
# n_values[2]=100000
# n_values[3]=500000
# n_values[4]=750000
# n_values[5]=1000000

num=6
i=0
j=0
iter=5
n_fn_call=$1

while [ $i -lt $num ]
do
    sum=0
    j=0
    while [ $j -lt $iter ]
    do
        temp=`./seq ${n_values[$i]}`
        sum=$(($temp+$sum))
        # sum=`expr $sum+$temp`
        #write n_fn_call, $i, avg into some file
        # j=$[$j+1]
        ((j++))
    done
    # avg=`expr $sum/10`
    avg=$(($sum/$iter))
    echo "$avg"
    # i=$[$i+1]
    ((i++))
done
