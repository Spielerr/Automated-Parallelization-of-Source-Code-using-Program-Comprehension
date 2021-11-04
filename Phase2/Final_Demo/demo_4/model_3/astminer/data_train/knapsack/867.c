

typedef struct{
    int weight;
    int value;
}Item;

int knapsack_search(int item_num, Item* item_list, int knapsack_capacity);


int knapsack_search(int item_num, Item* item_list, int knapsack_capacity){
    int val_max = 0;
    for(int state_cnt = 0; state_cnt < (0x1 << item_num); ++state_cnt){
        int weight = 0;
        int val = 0;
        for(int i = 0; i < item_num; ++i){
            int flag = (state_cnt >> i) & 0x1;
            weight = flag? (weight + item_list[i].weight): weight;
            val = flag? (val + item_list[i].value): val;
        }
        if(weight <= knapsack_capacity && val > val_max)val_max = val;
    }
    return val_max;
}
