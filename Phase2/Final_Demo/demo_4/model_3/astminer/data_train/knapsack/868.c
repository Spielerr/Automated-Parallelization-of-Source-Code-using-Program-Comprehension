

typedef struct{
    int weight;
    int value;
}Item;

int knapsack_dp_recursion(int item_num, Item* item_list, int knapsack_capacity);


int knapsack_dp_recursion(int item_num, Item* item_list, int knapsack_capacity){
    if(item_num == 0)return 0;
    if(item_num == 1){
        return (knapsack_capacity >= item_list[0].weight)? item_list[0].value: 0;
    }
    int val_out = knapsack_dp_recursion(item_num - 1, item_list + 1, knapsack_capacity);
    int val_in = knapsack_dp_recursion(item_num - 1, item_list + 1, knapsack_capacity - item_list[0].weight) + item_list[0].value;
    if(knapsack_capacity < item_list[0].weight)return val_out;
    else return (val_out > val_in)? val_out: val_in;
}


