echo here1
cd ./demo_1
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" OmpPragmaAdder.lara -p testfile_demo_1.cpp 2>&1
mv -f ./woven_code/testfile_demo_1.cpp ./testfile_demo_1_2.cpp
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" FunctionReplacer.lara -p testfile_demo_1_2.cpp 2>&1
echo here2