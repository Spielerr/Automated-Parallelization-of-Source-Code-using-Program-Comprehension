

typedef struct{
    int weight;
    int value;
}Item;

int knapsack_dp_loop(int item_num, Item* item_list, int knapsack_capacity);




int knapsack_dp_loop(int item_num, Item* item_list, int knapsack_capacity){
    int cache_ptr[MAX_CAPACITY + 1] = {0};
    for(int i = 0; i < item_num; ++i){
        int weight = item_list[i].weight;
        int val = item_list[i].value;
        for(int j = knapsack_capacity; j >= 0; --j){
            if(j >= weight){
                cache_ptr[j] = 
                    (cache_ptr[j] > cache_ptr[j - weight] + val)? 
                    cache_ptr[j]: 
                    cache_ptr[j - weight] + val;
            }
        }
    }
    return cache_ptr[knapsack_capacity];
}
