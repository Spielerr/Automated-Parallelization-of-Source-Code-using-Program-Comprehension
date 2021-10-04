CREATE USER 'test_user'@'localhost' IDENTIFIED BY 'test_user123';
GRANT ALL PRIVILEGES ON * . * TO 'test_user'@'localhost';
CREATE DATABASE parallel_code;
USE parallel_code;
CREATE TABLE mapping (fn_name VARCHAR(20) NOT NULL, parallel_code TEXT(60000) NOT NULL, PRIMARY KEY(fn_name));
INSERT INTO mapping VALUES ('parallel_sort', 'void __my_mapped_parallel_function_(int *arr, int n)
{
    __gnu_parallel::sort(arr, arr + n);
}\n');
INSERT INTO mapping VALUES ('parallel_max', 'int __my_mapped_parallel_function_(int *arr, int n)
{
    return *__gnu_parallel::max_element(arr, arr + n);
}\n');
INSERT INTO mapping VALUES ('parallel_min', 'int __my_mapped_parallel_function_(int *arr, int n)
{
    return *__gnu_parallel::min_element(arr, arr + n);
}\n');
INSERT INTO mapping VALUES ('parallel_mean', 'double __my_mapped_parallel_function_(int *arr, int n)
{
    double* s = (double*)malloc(sizeof(double));
    __gnu_parallel::partial_sum(arr, arr + n, s);
    double temp = *s;
    free(s);
    return temp;
}\n');