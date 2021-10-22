




void solve_bfs(struct Problem *problem)
{
    struct List open_list;
    list_init(&open_list);

    struct HashSet *visited = hash_set_new();

    int size = problem->size;
    struct TreeNode *root = tree_node_new(&problem->init_state, 0, 0);

    list_push(&open_list, root);
    hash_set_found_or_add(visited, root->state, size);
    do {
        struct TreeNode *node = list_pop_front(&open_list);
        if (state_is_equal(node->state, &problem->goal, size)) {
            fill_result(node, &problem->result);
            break;
        }

        struct TreeNode ** childs = tree_node_expand(node, size);
        for (; *childs; childs++) {
            struct TreeNode *child = *childs;
            if (!hash_set_found_or_add(visited, child->state, size))
                list_push(&open_list, child);
        }
    } while (!list_is_empty(&open_list));
    problem->result.tree = root;
    list_delete(&open_list);
    hash_set_delete(visited);
    return;
}
