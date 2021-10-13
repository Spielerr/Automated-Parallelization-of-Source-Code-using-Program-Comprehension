<?php
	extract($_POST);
	$myfile = fopen("./demo_4/testfile_demo_4.cpp", "w") or die("Unable to open the file!");

	fwrite($myfile, $code);

	$output = null;

	// shell_exec(escapeshellcmd('/usr/local/bin/clang-tidy testfile_demo_4.cpp -fix -checks="readability-braces-around-statements,readability-isolate-declaration" -- COMPILE_OPTIONS'));
	shell_exec(escapeshellcmd("bash demo_4/script_3.2.sh"));

    echo file_get_contents("demo_4/output.cpp");
	// $op = shell_exec("cd \"/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/Capstone_Project/Phase1/Thread_scheduling/\" && ./a.out");
	// echo $op;
	// $output = fopen("generated_thread.cpp","w") or die("Unable to open the file!");

	// fwrite($output, $op);
	// exec(escapeshellcmd("/usr/local/bin/gindent -linux generated_thread.cpp -o output.cpp"));

	// echo file_get_contents("generated_thread.cpp");

	fclose($myfile);

?>
