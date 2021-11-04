<?php
	extract($_POST);
	$myfile = fopen("prog.cpp", "w") or die("Unable to open the file!");

	fwrite($myfile, $code);

	$output = null;

	shell_exec(escapeshellcmd('/usr/local/bin/clang-tidy testfile.c -fix -checks="readability-braces-around-statements,readability-isolate-declaration" -- COMPILE_OPTIONS'));
	shell_exec("cd \"/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/Capstone_Project/Phase1/Thread_scheduling/\" && g++ thread_scheduling_generator_D.cpp");
	$op = shell_exec("cd \"/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/Capstone_Project/Phase1/Thread_scheduling/\" && ./a.out");
	// echo $op;
	$output = fopen("generated_thread.cpp","w") or die("Unable to open the file!");

	fwrite($output, $op);
	exec(escapeshellcmd("/usr/local/bin/gindent -linux generated_thread.cpp -o output.cpp"));

	echo file_get_contents("generated_thread.cpp");

	fclose($myfile);

?>
