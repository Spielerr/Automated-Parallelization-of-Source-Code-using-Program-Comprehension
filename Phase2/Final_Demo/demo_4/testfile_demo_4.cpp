#include <parallel/algorithm>
#include <parallel/numeric>
#include <stdio.h>
#include <stdlib.h>

// Map Reduce Program to find distributed count
// Given the batsmen scores from every match 
// in the Cricket World Cup, 
// find the frequency of the scores

struct node_results
{
    int score;
    int count;
};
typedef struct node_results node_results;


void fill(int a[], int n)
{
	for(int i = 0; i < n; ++i)
	{
		a[i] = rand() % 300;
	}
}

void map(int *arr, int *count_arr, int n)
{
    for(int i = 0; i<n; ++i)
    {
        count_arr[i] = 1;
    }

}

void merge_arr(int *arr1, int n1, int *arr2, int n2, int *arr3, int n3, int *merged_arr)
{
    int ind = 0;

    for(int i = 0; i<n1; ++i)
    {
        merged_arr[ind] = arr1[i];
        ++ind;
    }

    for(int i = 0; i<n2; ++i)
    {
        merged_arr[ind] = arr2[i];
        ++ind;
    }

    for(int i = 0; i<n3; ++i)
    {
        merged_arr[ind] = arr3[i];
        ++ind;
    }

}

void sort(int *arr, int n)
{
    int min_key, min_ind;
    int temp;

    for(int i = 0; i<n-1; ++i)
    {
        min_key = arr[i];
        min_ind = i;

        for(int j = i+1; j<n; ++j)
        {
            if(arr[j] < min_key)
            {
                min_key = arr[j];
                min_ind = j;
            }
        }

        temp = arr[i];
        arr[i] = min_key;
        arr[min_ind] = temp;

    }


}

//returns the ending index in the sorted_scores_arr 
//for the range defined
int partition(int *sorted_scores_arr, int n, int range_start, int range_end, int start_ind)
{
    if(start_ind < n && sorted_scores_arr[start_ind] >= range_start && sorted_scores_arr[start_ind] <= range_end)
    {
        int end_ind = start_ind;
        int i = start_ind + 1;
        while(i<n && sorted_scores_arr[i] <= range_end)
        {
            end_ind = i;
            ++i;
        }

        return end_ind;

    }

    //partition is empty
    else
    {
        return -1;
    }
}


// returns the length of the node_results arr after performing the reduce operation
int reduce(int *sorted_scores_arr, int l, int r, node_results *arr, int n)
{
    
    int count_score = 1;
    int ind = 0;

    for(int i = l+1; i<=r; ++i)
    {
        if(sorted_scores_arr[i] == sorted_scores_arr[i-1])
        {
            count_score += 1;
        }

        else
        {
            arr[ind].score = sorted_scores_arr[i-1];
            arr[ind].count = count_score;
            count_score = 1;
            ind += 1;
            
        }

    }

    
    arr[ind].score = sorted_scores_arr[r];
    arr[ind].count = count_score;
    ind += 1;

    return ind;

}

//ranges are defined as follows:
// range 1 : 0-99
// range 2 : 100 - 199
// range 3 : 200 - 300

//returns the length of the combined array 
//generates the combined array
int combiner(node_results *arr1, int n1, node_results *arr2, int n2, node_results *arr3, int n3, node_results *combined_arr)
{
    int ind = 0;
    for(int i = 0; i<n1; ++i)
    {
        combined_arr[ind].count = arr1[i].count;
        combined_arr[ind].score = arr1[i].score;
        ++ind;
    }

    for(int i = 0; i<n2; ++i)
    {
        combined_arr[ind].count = arr2[i].count;
        combined_arr[ind].score = arr2[i].score;
        ++ind;
    }

    for(int i = 0; i<n3; ++i)
    {
        combined_arr[ind].count = arr3[i].count;
        combined_arr[ind].score = arr3[i].score;
        ++ind;
    }

    return ind;

}

void display(node_results *arr, int n)
{
    printf("The Distributed Count of the Batsmen Scores are:\n");
    for(int i = 0; i<n; ++i)
    {
        printf("Score: %d, Count: %d\n", arr[i].score, arr[i].count);
    }
}

	