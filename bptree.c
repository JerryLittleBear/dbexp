    #include"bptree.h"
    // FUNCTION DEFINITIONS.  
      
    // OUTPUT AND UTILITIES  
      
    int order = DEFAULT_ORDER;  
      
    node * queue = NULL;  
      
    bool verbose_output = false;
    
      
    /* First message to the user. 
     */  
    void usage_1( void ) {  
        printf("B+ Tree of Order %d.\n", order);  
        printf("Following Silberschatz, Korth, Sidarshan, Database Concepts, 5th ed.\n\n");  
        printf("To build a B+ tree of a different order, start again and enter the order\n");  
        printf("as an integer argument:  bpt <order>  ");  
        printf("(%d <= order <= %d).\n", MIN_ORDER, MAX_ORDER);  
        printf("To start with input from a file of newline-delimited integers, \n"  
                "start again and enter ");  
        printf("the order followed by the filename:\n"  
                "bpt <order> <inputfile> .\n");  
    }  
      
      
    /* Second message to the user. 
     */  
    void usage_2( void ) {  
        printf("Enter any of the following commands after the prompt > :\n");  
        printf("\ti <k>  -- Insert <k> (an integer) as both key and value).\n");  
        printf("\tf <k>  -- Find the value under key <k>.\n");  
        printf("\tp <k> -- Print the path from the root to key k and its associated value.\n");  
        printf("\tr <k1> <k2> -- Print the keys and values found in the range "  
                "[<k1>, <k2>\n");  
        printf("\td <k>  -- Delete key <k> and its associated value.\n");  
        printf("\tx -- Destroy the whole tree.  Start again with an empty tree of the same order.\n");  
        printf("\tt -- Print the B+ tree.\n");  
        printf("\tl -- Print the keys of the leaves (bottom row of the tree).\n");  
        printf("\tv -- Toggle output of pointer addresses (\"verbose\") in tree and leaves.\n");  
        printf("\tq -- Quit. (Or use Ctl-D.)\n");  
        printf("\t? -- Print this help message.\n");  
    }  
      
      
    /* Brief usage note. 
     */  
    void usage_3( void ) {  
        printf("Usage: ./bpt [<order>]\n");  
        printf("\twhere %d <= order <= %d .\n", MIN_ORDER, MAX_ORDER);  
    }  
      
      
    /* Helper function for printing the 
     * tree out.  See print_tree. 
     */  
    void enqueue( node * new_node ) {  
        node * c;  
        if (queue == NULL) {  
            queue = new_node;  
            queue->next = NULL;  
        }  
        else {  
            c = queue;  
            while(c->next != NULL) {  
                c = c->next;  
            }  
            c->next = new_node;  
            new_node->next = NULL;  
        }  
    }  
      
      
    /* Helper function for printing the 
     * tree out.  See print_tree. 
     */  
    node * dequeue( void ) {  
        node * n = queue;  
        queue = queue->next;  
        n->next = NULL;  
        return n;  
    }  
      
      
    /* Prints the bottom row of keys 
     * of the tree (with their respective 
     * pointers, if the verbose_output flag is set. 
     */  
    void print_leaves( node * root ) {  
        int i;  
        node * c = root;  
        if (root == NULL) {  
            printf("Empty tree.\n");  
            return;  
        }  
        while (!c->is_leaf)  
            c = c->pointers[0];  
        while (true) {  
            for (i = 0; i < c->num_keys; i++) {  
                if (verbose_output)  
                    printf("%lx ", (unsigned long)c->pointers[i]);  
                printf("%d ", c->keys[i]);  
            }  
            if (verbose_output)  
                printf("%lx ", (unsigned long)c->pointers[order - 1]);  
            if (c->pointers[order - 1] != NULL) {  
                printf(" | ");  
                c = c->pointers[order - 1];  
            }  
            else  
                break;  
        }  
        printf("\n");  
    }  
      
      
    /* Utility function to give the height 
     * of the tree, which length in number of edges 
     * of the path from the root to any leaf. 
     */  
    int height( node * root ) {  
        int h = 0;  
        node * c = root;  
        while (!c->is_leaf) {  
            c = c->pointers[0];  
            h++;  
        }  
        return h;  
    }  
      
      
    /* Utility function to give the length in edges 
     * of the path from any node to the root. 
     */  
    int path_to_root( node * root, node * child ) {  
        int length = 0;  
        node * c = child;  
        while (c != root) {  
            c = c->parent;  
            length++;  
        }  
        return length;  
    }  
      
      
    /* Prints the B+ tree in the command 
     * line in level (rank) order, with the  
     * keys in each node and the '|' symbol 
     * to separate nodes. 
     * With the verbose_output flag set. 
     * the values of the pointers corresponding 
     * to the keys also appear next to their respective 
     * keys, in hexadecimal notation. 
     */  
    void print_tree( node * root ) {  
      
        node * n = NULL;  
        int i = 0;  
        int rank = 0;  
        int new_rank = 0;  
      
        if (root == NULL) {  
            printf("Empty tree.\n");  
            return;  
        }  
        queue = NULL;  
        enqueue(root);  
        while( queue != NULL ) {  
            n = dequeue();  
            if (n->parent != NULL && n == n->parent->pointers[0]) {  
                new_rank = path_to_root( root, n );  
                if (new_rank != rank) {  
                    rank = new_rank;  
                    printf("\n");  
                }  
            }  
            if (verbose_output)   
                printf("(%lx)", (unsigned long)n);  
            for (i = 0; i < n->num_keys; i++) {  
                if (verbose_output)  
                    printf("%lx ", (unsigned long)n->pointers[i]);  
                printf("%d ", n->keys[i]);  
            }  
            if (!n->is_leaf)  
                for (i = 0; i <= n->num_keys; i++)  
                    enqueue(n->pointers[i]);  
            if (verbose_output) {  
                if (n->is_leaf)   
                    printf("%lx ", (unsigned long)n->pointers[order - 1]);  
                else  
                    printf("%lx ", (unsigned long)n->pointers[n->num_keys]);  
            }  
            printf("| ");  
        }  
        printf("\n");  
    }  
      
      
    /* Finds the record under a given key and prints an 
     * appropriate message to stdout. 
     */  
    void find_and_print(node * root, int key, bool verbose) {  
        record * r = find(root, key, verbose);  
        if (r == NULL)  
            printf("Record not found under key %d.\n", key);  
        else   
            printf("Record at %lx -- key %d, value %d.\n",  
                    (unsigned long)r, key, r->value);  
    }  
      
      
    /* Finds and prints the keys, pointers, and values within a range 
     * of keys between key_start and key_end, including both bounds. 
     */  
    void find_and_print_range( node * root, int key_start, int key_end,  
            bool verbose ) {  
        int i;  
        int array_size = key_end - key_start + 1;  
        int returned_keys[array_size];  
        void * returned_pointers[array_size];  
        int num_found = find_range( root, key_start, key_end, verbose,  
                returned_keys, returned_pointers );  
        if (!num_found)  
            printf("None found.\n");  
        else {  
            for (i = 0; i < num_found; i++)  
                printf("Key: %d   Location: %lx  Value: %d\n",  
                        returned_keys[i],  
                        (unsigned long)returned_pointers[i],  
                        ((record *)  
                         returned_pointers[i])->value);  
        }  
    }  
      
      
    /* Finds keys and their pointers, if present, in the range specified 
     * by key_start and key_end, inclusive.  Places these in the arrays 
     * returned_keys and returned_pointers, and returns the number of 
     * entries found. 
     */  
    int find_range( node * root, int key_start, int key_end, bool verbose,  
            int returned_keys[], void * returned_pointers[]) {  
        int i, num_found;  
        num_found = 0;  
        node * n = find_leaf( root, key_start, verbose );  
        if (n == NULL) return 0;  
        for (i = 0; i < n->num_keys && n->keys[i] < key_start; i++) ;  
        if (i == n->num_keys) return 0;  
        while (n != NULL) {  
            for ( ; i < n->num_keys && n->keys[i] <= key_end; i++) {  
                returned_keys[num_found] = n->keys[i];  
                returned_pointers[num_found] = n->pointers[i];  
                num_found++;  
            }  
            n = n->pointers[order - 1];  
            i = 0;  
        }  
        return num_found;  
    }  
      
      
    /* Traces the path from the root to a leaf, searching 
     * by key.  Displays information about the path 
     * if the verbose flag is set. 
     * Returns the leaf containing the given key. 
     */  
    node * find_leaf( node * root, int key, bool verbose ) {  
        int i = 0;  
        node * c = root;  
        if (c == NULL) {  
            if (verbose)   
                printf("Empty tree.\n");  
            return c;  
        }  
        while (!c->is_leaf) {  
            if (verbose) {  
                printf("[");  
                for (i = 0; i < c->num_keys - 1; i++)  
                    printf("%d ", c->keys[i]);  
                printf("%d] ", c->keys[i]);  
            }  
            i = 0;  
            while (i < c->num_keys) {  
                if (key >= c->keys[i]) i++;  
                else break;  
            }  
            if (verbose)  
                printf("%d ->\n", i);  
            c = (node *)c->pointers[i];  
        }  
        if (verbose) {  
            printf("Leaf [");  
            for (i = 0; i < c->num_keys - 1; i++)  
                printf("%d ", c->keys[i]);  
            printf("%d] ->\n", c->keys[i]);  
        }  
        return c;  
    }  
      
      
    /* Finds and returns the record to which 
     * a key refers. 
     */  
    record * find( node * root, int key, bool verbose ) {  
        int i = 0;  
        node * c = find_leaf( root, key, verbose );  
        if (c == NULL) return NULL;  
        for (i = 0; i < c->num_keys; i++)  
            if (c->keys[i] == key) break;  
        if (i == c->num_keys)   
            return NULL;  
        else  
            return (record *)c->pointers[i];  
    }  
      
    /* Finds the appropriate place to 
     * split a node that is too big into two. 
     */  
    int cut( int length ) {  
        if (length % 2 == 0)  
            return length/2;  
        else  
            return length/2 + 1;  
    }  
      
      
    // INSERTION  
      
    /* Creates a new record to hold the value 
     * to which a key refers. 
     */  
    record * make_record(int value) {  
        record * new_record = (record *)malloc(sizeof(record));  
        if (new_record == NULL) {  
            perror("Record creation.");  
            exit(EXIT_FAILURE);  
        }  
        else {  
            new_record->value = value;  
        }  
        return new_record;  
    }  
      
      
    /* Creates a new general node, which can be adapted 
     * to serve as either a leaf or an internal node. 
     */  
    node * make_node( void ) {  
        node * new_node;  
        new_node = malloc(sizeof(node));  
        if (new_node == NULL) {  
            perror("Node creation.");  
            exit(EXIT_FAILURE);  
        }  
        new_node->keys = malloc( (order - 1) * sizeof(int) );  
        if (new_node->keys == NULL) {  
            perror("New node keys array.");  
            exit(EXIT_FAILURE);  
        }  
        new_node->pointers = malloc( order * sizeof(void *) );  
        if (new_node->pointers == NULL) {  
            perror("New node pointers array.");  
            exit(EXIT_FAILURE);  
        }  
        new_node->is_leaf = false;  
        new_node->num_keys = 0;  
        new_node->parent = NULL;  
        new_node->next = NULL;  
        return new_node;  
    }  
      
    /* Creates a new leaf by creating a node 
     * and then adapting it appropriately. 
     */  
    node * make_leaf( void ) {  
        node * leaf = make_node();  
        leaf->is_leaf = true;  
        return leaf;  
    }  
      
      
    /* Helper function used in insert_into_parent 
     * to find the index of the parent's pointer to  
     * the node to the left of the key to be inserted. 
     */  
    int get_left_index(node * parent, node * left) {  
      
        int left_index = 0;  
        while (left_index <= parent->num_keys &&   
                parent->pointers[left_index] != left)  
            left_index++;  
        return left_index;  
    }  
      
    /* Inserts a new pointer to a record and its corresponding 
     * key into a leaf. 
     * Returns the altered leaf. 
     */  
    node * insert_into_leaf( node * leaf, int key, record * pointer ) {  
      
        int i, insertion_point;  
      
        insertion_point = 0;  
        while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)  
            insertion_point++;  
      
        for (i = leaf->num_keys; i > insertion_point; i--) {  
            leaf->keys[i] = leaf->keys[i - 1];  
            leaf->pointers[i] = leaf->pointers[i - 1];  
        }  
        leaf->keys[insertion_point] = key;  
        leaf->pointers[insertion_point] = pointer;  
        leaf->num_keys++;  
        return leaf;  
    }  
      
      
    /* Inserts a new key and pointer 
     * to a new record into a leaf so as to exceed 
     * the tree's order, causing the leaf to be split 
     * in half. 
     */  
    node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer) {  
      
        node * new_leaf;  
        int * temp_keys;  
        void ** temp_pointers;  
        int insertion_index, split, new_key, i, j;  
      
        new_leaf = make_leaf();  
      
        temp_keys = malloc( order * sizeof(int) );  
        if (temp_keys == NULL) {  
            perror("Temporary keys array.");  
            exit(EXIT_FAILURE);  
        }  
      
        temp_pointers = malloc( order * sizeof(void *) );  
        if (temp_pointers == NULL) {  
            perror("Temporary pointers array.");  
            exit(EXIT_FAILURE);  
        }  
      
        insertion_index = 0;  
        while (insertion_index < order - 1 && leaf->keys[insertion_index] < key)  
            insertion_index++;  
      
        for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {  
            if (j == insertion_index) j++;  
            temp_keys[j] = leaf->keys[i];  
            temp_pointers[j] = leaf->pointers[i];  
        }  
      
        temp_keys[insertion_index] = key;  
        temp_pointers[insertion_index] = pointer;  
      
        leaf->num_keys = 0;  
      
        split = cut(order - 1);  
      
        for (i = 0; i < split; i++) {  
            leaf->pointers[i] = temp_pointers[i];  
            leaf->keys[i] = temp_keys[i];  
            leaf->num_keys++;  
        }  
      
        for (i = split, j = 0; i < order; i++, j++) {  
            new_leaf->pointers[j] = temp_pointers[i];  
            new_leaf->keys[j] = temp_keys[i];  
            new_leaf->num_keys++;  
        }  
      
        free(temp_pointers);  
        free(temp_keys);  
      
        new_leaf->pointers[order - 1] = leaf->pointers[order - 1];  
        leaf->pointers[order - 1] = new_leaf;  
      
        for (i = leaf->num_keys; i < order - 1; i++)  
            leaf->pointers[i] = NULL;  
        for (i = new_leaf->num_keys; i < order - 1; i++)  
            new_leaf->pointers[i] = NULL;  
      
        new_leaf->parent = leaf->parent;  
        new_key = new_leaf->keys[0];  
      
        return insert_into_parent(root, leaf, new_key, new_leaf);  
    }  
      
      
    /* Inserts a new key and pointer to a node 
     * into a node into which these can fit 
     * without violating the B+ tree properties. 
     */  
    node * insert_into_node(node * root, node * n,   
            int left_index, int key, node * right) {  
        int i;  
      
        for (i = n->num_keys; i > left_index; i--) {  
            n->pointers[i + 1] = n->pointers[i];  
            n->keys[i] = n->keys[i - 1];  
        }  
        n->pointers[left_index + 1] = right;  
        n->keys[left_index] = key;  
        n->num_keys++;  
        return root;  
    }  
      
      
    /* Inserts a new key and pointer to a node 
     * into a node, causing the node's size to exceed 
     * the order, and causing the node to split into two. 
     */  
    node * insert_into_node_after_splitting(node * root, node * old_node, int left_index,   
            int key, node * right) {  
      
        int i, j, split, k_prime;  
        node * new_node, * child;  
        int * temp_keys;  
        node ** temp_pointers;  
      
        /* First create a temporary set of keys and pointers 
         * to hold everything in order, including 
         * the new key and pointer, inserted in their 
         * correct places.  
         * Then create a new node and copy half of the  
         * keys and pointers to the old node and 
         * the other half to the new. 
         */  
      
        temp_pointers = malloc( (order + 1) * sizeof(node *) );  
        if (temp_pointers == NULL) {  
            perror("Temporary pointers array for splitting nodes.");  
            exit(EXIT_FAILURE);  
        }  
        temp_keys = malloc( order * sizeof(int) );  
        if (temp_keys == NULL) {  
            perror("Temporary keys array for splitting nodes.");  
            exit(EXIT_FAILURE);  
        }  
      
        for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {  
            if (j == left_index + 1) j++;  
            temp_pointers[j] = old_node->pointers[i];  
        }  
      
        for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {  
            if (j == left_index) j++;  
            temp_keys[j] = old_node->keys[i];  
        }  
      
        temp_pointers[left_index + 1] = right;  
        temp_keys[left_index] = key;  
      
        /* Create the new node and copy 
         * half the keys and pointers to the 
         * old and half to the new. 
         */    
        split = cut(order);  
        new_node = make_node();  
        old_node->num_keys = 0;  
        for (i = 0; i < split - 1; i++) {  
            old_node->pointers[i] = temp_pointers[i];  
            old_node->keys[i] = temp_keys[i];  
            old_node->num_keys++;  
        }  
        old_node->pointers[i] = temp_pointers[i];  
        k_prime = temp_keys[split - 1];  
        for (++i, j = 0; i < order; i++, j++) {  
            new_node->pointers[j] = temp_pointers[i];  
            new_node->keys[j] = temp_keys[i];  
            new_node->num_keys++;  
        }  
        new_node->pointers[j] = temp_pointers[i];  
        free(temp_pointers);  
        free(temp_keys);  
        new_node->parent = old_node->parent;  
        for (i = 0; i <= new_node->num_keys; i++) {  
            child = new_node->pointers[i];  
            child->parent = new_node;  
        }  
      
        /* Insert a new key into the parent of the two 
         * nodes resulting from the split, with 
         * the old node to the left and the new to the right. 
         */  
      
        return insert_into_parent(root, old_node, k_prime, new_node);  
    }  
      
      
      
    /* Inserts a new node (leaf or internal node) into the B+ tree. 
     * Returns the root of the tree after insertion. 
     */  
    node * insert_into_parent(node * root, node * left, int key, node * right) {  
      
        int left_index;  
        node * parent;  
      
        parent = left->parent;  
      
        /* Case: new root. */  
      
        if (parent == NULL)  
            return insert_into_new_root(left, key, right);  
      
        /* Case: leaf or node. (Remainder of 
         * function body.)   
         */  
      
        /* Find the parent's pointer to the left  
         * node. 
         */  
      
        left_index = get_left_index(parent, left);  
      
      
        /* Simple case: the new key fits into the node.  
         */  
      
        if (parent->num_keys < order - 1)  
            return insert_into_node(root, parent, left_index, key, right);  
      
        /* Harder case:  split a node in order  
         * to preserve the B+ tree properties. 
         */  
      
        return insert_into_node_after_splitting(root, parent, left_index, key, right);  
    }  
      
      
    /* Creates a new root for two subtrees 
     * and inserts the appropriate key into 
     * the new root. 
     */  
    node * insert_into_new_root(node * left, int key, node * right) {  
      
        node * root = make_node();  
        root->keys[0] = key;  
        root->pointers[0] = left;  
        root->pointers[1] = right;  
        root->num_keys++;  
        root->parent = NULL;  
        left->parent = root;  
        right->parent = root;  
        return root;  
    }  
      
      
      
    /* First insertion: 
     * start a new tree. 
     */  
    node * start_new_tree(int key, record * pointer) {  
      
        node * root = make_leaf();  
        root->keys[0] = key;  
        root->pointers[0] = pointer;  
        root->pointers[order - 1] = NULL;  
        root->parent = NULL;  
        root->num_keys++;  
        return root;  
    }  
      
      
      
    /* Master insertion function. 
     * Inserts a key and an associated value into 
     * the B+ tree, causing the tree to be adjusted 
     * however necessary to maintain the B+ tree 
     * properties. 
     */  
    node * insert( node * root, int key, int value ) {  
      
        record * pointer;  
        node * leaf;  
      
        /* The current implementation ignores 
         * duplicates. 
         */  
      
        if (find(root, key, false) != NULL)  
            return root;  
      
        /* Create a new record for the 
         * value. 
         */  
        pointer = make_record(value);  
      
      
        /* Case: the tree does not exist yet. 
         * Start a new tree. 
         */  
      
        if (root == NULL)   
            return start_new_tree(key, pointer);  
      
      
        /* Case: the tree already exists. 
         * (Rest of function body.) 
         */  
      
        leaf = find_leaf(root, key, false);  
      
        /* Case: leaf has room for key and pointer. 
         */  
      
        if (leaf->num_keys < order - 1) {  
            leaf = insert_into_leaf(leaf, key, pointer);  
            return root;  
        }  
      
      
        /* Case:  leaf must be split. 
         */  
      
        return insert_into_leaf_after_splitting(root, leaf, key, pointer);  
    }  


void destroy_tree_nodes(node * root) {    
    int i;    
    if (root->is_leaf)    
        for (i = 0; i < root->num_keys; i++)    
            free(root->pointers[i]);    
    else    
        for (i = 0; i < root->num_keys + 1; i++)    
            destroy_tree_nodes(root->pointers[i]);    
    free(root->pointers);    
    free(root->keys);    
    free(root);    
}  

node * destroy_tree(node * root) {    
    destroy_tree_nodes(root);    
    return NULL;    
} 
