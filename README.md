# Capstone Project
## Automated Parallelization of Source Code using Program Comprehension

### Team Members

* Darshan D
* Karan Kumar G
* Manu M Bhat
* Mayur Peshve

**Mentor**: Prof. NS Kumar

## Summary

A Research exploration aimed at exploring methods to improve the performance of sequential source code by automatically converting it to its functionally accurate parallel equivalent by implementing Intra-Function and Inter-Function Parallelism, thereby ensuring effective and efficient utilization of the underlying hardware resources. This project was developed and implemented as part of the Capstone Project during our Undergraduate Study.

## Abstract

 * There has been a rapid improvement in hardware and compute platforms and their capabilities
 * But the performance gain achieved is limited by the software and programs written to run on these platforms
 * Sequential software does not exploit these hardware capabilities to the maximum possible extent
 * This is with respect to the utilization of multiple threads, processors, cores, and other available resources
 * Therefore, there is an impetus for developing Parallel programs that can effectively utilize these resources
 * But developing Parallel software brings its own challenges as follows:
    * It requires highly skilled programmers
    * It requires fundamental changes in approach due to the non-intuitive nature of parallel programming
    * It increases testing and debugging complexity due to issues like race conditions, deadlocks, busy waiting, etc.
 * These challenges increase the development time and the costs involved, thereby rendering it infeasible
 * Auto-parallelization techniques help in addressing these challenges and mitigating the costs
 * Contemporary approaches involve loop parallelization and other techniques specific to an application
 * The goal of this Research project was to enable parallelization for a wide variety of programs and achieve the maximum possible parallelism
 * The project involved the implementation of the following two paradigms of parallelization:
    * **Intra-Function parallelism**: This was implemented using the concept of program comprehension that enabled the identification of the intent and the algorithm implemented in a particular code section and consequent replacement with the optimized parallel version based on the defined mapping in the backend database
    * **Inter-Function parallelism**: This was implemented using a novel thread scheduling algorithm that enabled the parallel execution of the different functions in the original sequential program

## Implementation Details

### Program Comprehension Phase
 * The input source code is represented as Vector Embeddings
 * The similarities between the vector embeddings of different programs are found, to group them into clusters
 * Each of the clusters corresponds to a previously defined category that has a mapped parallel version in the backend database
 * The input program is tried to be associated into one such cluster by using appropriate thresholds
 * Dynamic Verification is used to additionally verify if the predicted label is accurate
 * The "Others" Category is introduced to ensure correctness of the program by avoiding any misclassification
 * Additionally, this phase involves the generation of an enriched Abstract Syntax Tree and its use to perform data-dependency, control, and data-flow analysis, which are pre-requisites for the parallelization phase

### Parallelization Phase
 * This phase involved the utilization of all the generated information and analysis regarding the program to perform parallelization
 * There were four different approaches that were experimented with and researched up on as follows:
    * Parallelism by AST Querying and OpenMP Directives
    * Naive Thread Scheduling using C++ Promises and Futures
    * Master-Worker based Optimized Thread Scheduling
    * Non Master-Worker based Optimized Thread Scheduling
 * With each of these incremental approaches, there was an improvement in the parallel code being generated with respect to the different cases handled and the performance gain achieved. Further, the transition through these incremental approaches enabled a more fine-grained control over the different aspects concerning parallelization due to the lowering of the layers of abstraction.

## Conclusion

The project successfully achieved the research and development of techniques to automatically convert the sequential source code to its functionally accurate parallel equivalent with a substantial performance speedup (up to 500 times for larger data), thereby enabling the efficient and effective utilization of the underlying hardware resources.

## Details about running the Software

### Requirements

* Python3:
   * tensorflow==2.0.0-beta1
   * numpy
   * pandas
   * tabulate
   * sklearn
   * pickle

* Java:
   * sudo apt install default-jdk
   * sudo apt install default-jre

* Get mysql:
   * sudo apt-get install mysql

* Run the init_db.sql to create and fill the database
   * sql init_db.sql

* Set up docker on your system.
   * https://docs.docker.com/engine/install/ubuntu/
   * https://docs.docker.com/get-started/

### Code Execution

The application can be run using a GUI or a CLI as follows:

* **GUI**:

   * Apache2 is required to run the GUI for the application: <br>
     ```sudo apt-get apache2```
   * Edit the apache2.conf file in /etc/apache2/: <br>
     ```
     <Directory "path/to/the/demo/folder">
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
     </Directory>
     ```
   * Edit the 000-default.conf file in sites-available:
      * Change document root to point to the demo folder
   * Restart apache2: <br>
     ```sudo service apache2 restart```
   * The web-app can now be accessed at http://localhost/WePar.html

* **CLI**:

   * cd to ```Phase2/Final_Demo/demo_4``` folder of this repository
   * Rewrite testfile_demo_4.cpp with the sequential input program
   * Run the bash script
     * Method-3 (Master-Worker based) - ```bash script_3.1.sh``` <br>
        OR
     * Method-4 (Non Master-Worker based) - ```bash script_3.2.sh```
   * The output is written into the ```model_3/output``` folder
