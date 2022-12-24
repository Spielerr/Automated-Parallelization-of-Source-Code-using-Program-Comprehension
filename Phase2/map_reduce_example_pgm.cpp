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

int max_score(int* a, int n)
{
    int max = a[0];
    for (int i = 1; i < n; ++i)
    {
        if(a[i]>max)
        {
            max = a[i];
        }
    }
	
    return max;
}

int min_score(int* a, int n)
{
    int min = a[0];
    for (int i = 1; i < n; ++i)
    {
        if(a[i]<min)
        {
            min = a[i];
        }
    }
    return min;
	
}

int main()
{
    int match_1_len = 20000;
    int match_2_len = 10000;
    int match_3_len = 80000;

    int *match_1_scores = (int*)malloc( sizeof(int) * match_1_len );
    int *match_2_scores = (int*)malloc( sizeof(int) * match_2_len );
    int *match_3_scores = (int*)malloc( sizeof(int) * match_3_len );

    fill(match_1_scores, match_1_len);
    fill(match_2_scores, match_2_len);
    fill(match_3_scores, match_3_len);

    int max1 = max_score(match_1_scores, match_1_len);
    int min1 = min_score(match_1_scores, match_1_len);
    int range1 = max1 - min1;
    printf("Range of Scores in first array: %d - %d\n", min1, max1);

    int max2 = max_score(match_2_scores, match_2_len);
    int min2 = min_score(match_2_scores, match_2_len);
    int range2 = max2 - min2;
    printf("Range of Scores in second array: %d - %d\n", min2, max2);

    int max3 = max_score(match_3_scores, match_3_len);
    int min3 = min_score(match_3_scores, match_3_len);
    int range3 = max3 - min3;
    printf("Range of Scores in third array: %d - %d\n", min3, max3);


    int *count_1 = (int*)malloc( sizeof(int) * match_1_len );
    int *count_2 = (int*)malloc( sizeof(int) * match_2_len );
    int *count_3 = (int*)malloc( sizeof(int) * match_3_len );

    map(match_1_scores, count_1, match_1_len);
    map(match_2_scores, count_2, match_2_len);
    map(match_3_scores, count_3, match_3_len);



    int n = match_1_len + match_2_len + match_3_len;
    int *merged_arr = (int*)malloc( sizeof(int) * n );

    merge_arr(match_1_scores, match_1_len, match_2_scores, match_2_len, match_3_scores, match_3_len, merged_arr);
    sort(merged_arr, n);

    int start_ind = 0;

    // range 1 : 0-99
    // range 2 : 100 - 199
    // range 3 : 200 - 300

    node_results *arr1 = (node_results*)malloc( sizeof(node_results) * 100 );
    node_results *arr2 = (node_results*)malloc( sizeof(node_results) * 100 );
    node_results *arr3 = (node_results*)malloc( sizeof(node_results) * 101 );
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

    int range1_ind = partition(merged_arr, n, 0, 99, 0);
    
    if(range1_ind != -1)
    {
        n1 = reduce(merged_arr, 0, range1_ind, arr1, 100);
        // start_ind = range1_ind + 1;
    }

    int range2_ind = partition(merged_arr, n, 100, 199, range1_ind + 1);

    if(range2_ind != -1)
    {
        n2 = reduce(merged_arr, range1_ind + 1, range2_ind, arr2, 100);
        // start_ind = range2_ind + 1;
    }

    int range3_ind = partition(merged_arr, n, 200, 300, range2_ind + 1);

    if(range3_ind != -1)
    {
        n3 = reduce(merged_arr, range2_ind + 1, range3_ind, arr3, 101);
        // start_ind = range3_ind + 1;
    }

    node_results *final_results = (node_results*)malloc((n1+n2+n3)*sizeof(node_results));
    int combined_length = combiner(arr1, n1, arr2, n2, arr3, n3, final_results);

    display(final_results, combined_length);

}