<?php
	extract($_POST);
	$myfile = fopen("testfile.cpp", "w") or die("Unable to open the file!");
    // echo $code;
	fwrite($myfile, $code);

	$output = null;

	// shell_exec(escapeshellcmd('/usr/local/bin/clang-tidy testfile.cpp -fix -checks="readability-braces-around-statements,readability-isolate-declaration" -- COMPILE_OPTIONS'));
	// echo shell_exec("echo here");
	// echo shell_exec(escapeshellcmd("g++ -pthread testfile.cpp -o thread1 -lboost_thread -lboost_system && echo here"));
	// echo shell_exec("gcc testfile.c -o test1");
	// shell_exec("python3 py_replace_m1.py testfile.cpp");
	echo shell_exec("g++ -std=c++2a -pthread -fopenmp -g testfile.cpp && ./time ./a.out");
	// echo shell_exec("g++ -std=c++2a -pthread -fopenmp -g testfile.cpp && ./time ./a.out");
	// shell_exec("g++ -std=c++2a -pthread -fopenmp -g testfile.cpp && ./a.out > print_output_gen_pgm.txt");
	// shell_exec("./time ./a.out >> print_output_gen_pgm.txt");
	// $op = shell_exec("python3 py_sort_output_order_fn_calls.py");
	// echo $op;
	// $output = fopen("generated_thread.cpp","w") or die("Unable to open the file!");

	// fwrite($output, $op);
	// exec(escapeshellcmd("/usr/local/bin/gindent -linux generated_thread.cpp -o output.cpp"));

	// echo file_get_contents("generated_thread.cpp");

	// fclose($myfile);

?>
