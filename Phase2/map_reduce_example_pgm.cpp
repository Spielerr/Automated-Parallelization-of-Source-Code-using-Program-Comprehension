#include <stdio.h>
#include <stdlib.h>

// Map Reduce Program to find distributed count
// Given the batsmen scores from every match in the Cricket World Cup, find the frequency of the scores

struct node_results
{
    int score;
    int count;
};
typedef struct node_results node_results;



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

//returns the ending index in the sorted_scores_arr for the range defined
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

//returns the length of the combined array generates the combined array
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

int main()
{
    int match_1_scores[] = {12,0,89,43,22,78,67};
    int match_1_len = 7;

    int match_2_scores[] = {0,22,97,150,0,1,7,12,0,1};
    int match_2_len = 10;

    int match_3_scores[] = {100,89,2,1,0,8,7,12};
    int match_3_len = 8;

    int count_1[match_1_len];
    int count_2[match_2_len];
    int count_3[match_3_len];

    map(match_1_scores, count_1, match_1_len);
    map(match_2_scores, count_2, match_2_len);
    map(match_3_scores, count_3, match_3_len);

    int n = match_1_len + match_2_len + match_3_len;
    int merged_arr[n];

    merge_arr(match_1_scores, match_1_len, match_2_scores, match_2_len, match_3_scores, match_3_len, merged_arr);
    sort(merged_arr, n);

    int start_ind = 0;
    int range1_ind = -1; 
    int range2_ind = -1; 
    int range3_ind = -1;

    // range 1 : 0-99
    // range 2 : 100 - 199
    // range 3 : 200 - 300

    node_results arr1[100];
    node_results arr2[100];
    node_results arr3[101];
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

    range1_ind = partition(merged_arr, n, 0, 99, 0);
    
    if(range1_ind != -1)
    {
        n1 = reduce(merged_arr, start_ind, range1_ind, arr1, 100);
        start_ind = range1_ind + 1;
    }

    range2_ind = partition(merged_arr, n, 100, 199, start_ind);

    if(range2_ind != -1)
    {
        n2 = reduce(merged_arr, start_ind, range2_ind, arr2, 100);
        start_ind = range2_ind + 1;
    }

    range3_ind = partition(merged_arr, n, 200, 300, start_ind);

    if(range3_ind != -1)
    {
        n3 = reduce(merged_arr, start_ind, range3_ind, arr3, 101);
        start_ind = range3_ind + 1;
    }

    node_results *final_results = (node_results*)malloc((n1+n2+n3)*sizeof(node_results));
    int combined_length = combiner(arr1, n1, arr2, n2, arr3, n3, final_results);

    display(final_results, combined_length);

}