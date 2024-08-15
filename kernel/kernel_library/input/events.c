void event_push(event_t event) {
    // allocate memory for the new node
    node_t *new_node = (node_t *)mmu_allocate(sizeof(node_t), false);
    if(new_node == NULL) return;
    // initialize the new node
    new_node->event = event;
    new_node->next = event_head;
    new_node->prev = NULL;
    // push the node to the start
    if (event_head != NULL)
        event_head->prev = new_node;
    event_head = new_node;
    // If the list was empty, set the tail to the new node
    if (event_tail == NULL)
        event_tail = new_node;
}

event_t event_pop(void) {
    // if the list is empty, return
    if(event_head == NULL) return (event_t){0};
    // pop the event from the tail/end of the list
    node_t *temp = event_tail;
    event_tail = event_tail->prev;
    if(event_tail != NULL)
        event_tail->next = NULL;
    else
        event_head = NULL;
    // free the memory of the popped node
    event_t event = temp->event;
    mmu_free(temp);
    return event;
}