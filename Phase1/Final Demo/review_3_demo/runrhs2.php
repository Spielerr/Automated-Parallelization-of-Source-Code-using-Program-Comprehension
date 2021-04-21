<?php
	extract($_POST);
	$myfile = fopen("testfile.cpp", "w") or die("Unable to open the file!");
    // echo $code;
	fwrite($myfile, $code);

	$output = null;

	shell_exec(escapeshellcmd('/usr/local/bin/clang-tidy testfile.cpp -fix -checks="readability-braces-around-statements,readability-isolate-declaration" -- COMPILE_OPTIONS'));
	// echo shell_exec("echo here");
	// echo shell_exec(escapeshellcmd("g++ -pthread testfile.cpp -o thread1 -lboost_thread -lboost_system && echo here"));
	// echo shell_exec("gcc testfile.c -o test1");
	$op = shell_exec("g++ -pthread -g testfile.cpp && ./a.out");
	echo $op;
	// $output = fopen("generated_thread.cpp","w") or die("Unable to open the file!");

	// fwrite($output, $op);
	// exec(escapeshellcmd("/usr/local/bin/gindent -linux generated_thread.cpp -o output.cpp"));

	// echo file_get_contents("generated_thread.cpp");

	// fclose($myfile);

?>
