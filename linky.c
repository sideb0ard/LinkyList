#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

int list_length(node *head)
{
    int count = 0;

    struct node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void change_to_null(struct node **head_ref)
{
    *head_ref = NULL;
}

void print_list_data(node *head)
{
    int node_num = 0;

    struct node *cur = head;
    while (cur != NULL)
    {
        printf("Node_num:%d contains data %d\n", ++node_num, cur->data);
        cur = cur->next;
    }
}


struct node* calloc_node(int data)
{
    struct node *m_node = calloc(1, sizeof(struct node));
    m_node->data = data;
    m_node->next = NULL;
    return m_node;
}

void push_node(struct node** head_ref, int new_data)
{
    struct node* new_node = calloc_node(new_data);

    if (*head_ref)
        new_node->next = *head_ref;

    *head_ref = new_node;
}

struct node* build_one_two_three()
{
    struct node *new_node;
    struct node **head_ptr = &new_node;
    for (int i = 1; i < 4; ++i)
    {
        push_node(head_ptr, i);
        head_ptr = &((*head_ptr)->next);
    }

    return new_node;
}

struct node* build_five_at_tail()
{
    struct node *head = NULL;
    struct node *tail;

    push_node(&head, 1);
    tail = head;

    for (int i = 2; i < 6; ++i)
    {
        push_node(&(tail->next), i);
        tail = tail->next;
    }
    return head;
}

struct node *build_five_with_dummy()
{
    struct node dummy;
    struct node* tail = &dummy;

    for (int i = 1; i < 6; ++i)
    {
        push_node(&(tail->next), i);
        tail = tail->next;
    }
    return dummy.next;
}

struct node *build_with_local_ref()
{
    struct node *head = NULL;
    struct node **head_ref = &head;

    for (int i = 1; i < 6; ++i)
    {
        push_node(head_ref, i);
        head_ref = &((*head_ref)->next);
    }
    return head;
}

int count_for_item(struct node *head, int item)
{
    int count = 0;
    struct node *cur = head;
    while (cur != NULL)
    {
        if (cur->data == item)
            count++;
        cur = cur->next;
    }
    return count;
}

void insert_nth(struct node **list_ptr, int pos, int val)
{
    int len = list_length(*list_ptr);
    if (pos > len)
    {
        printf("GTFO!\n");
        return;
    }
    struct node *cur = *list_ptr;
    int cur_idx = 0;

    if (cur == NULL)
    {
        push_node(list_ptr, val);
    }
    else {
        while (cur != NULL)
        {
            if (cur_idx == (pos-1))
            {
                push_node(&(cur->next), val);
                return;
            }
            cur_idx++;
            cur = cur->next;
        }
    }
}

int get_nth(struct node* list, int n)
{
    if ( list_length(list) <= n)
    {
        printf("Barf! 'n' is longer than list!\n");
        return -1;
    }
    
    int node_num = 0;
    struct node *cur = list;
    while (cur != NULL)
    {
        if (node_num == n)
            return cur->data;
        node_num++;
        cur = cur->next;
    }
    return -1;
}

void delete_list(struct node** list)
{
    struct node *cur = *list;
    struct node *next_node;

    while (cur != NULL)
    {
        next_node = cur->next;
        free(cur);
        cur = next_node;
    }

    *list = NULL;
}

int pop(struct node **list)
{
    struct node *head;
    int result;

    head = *list;
    if (!head)
        return -1;

    result = head->data;
    *list = head->next;
    free(head);
    return result;

}

void dump_list(struct node *list)
{
    printf("Len is %d\n", list_length(list));
    print_list_data(list);
}

void sorted_insert(struct node **headref, struct node *new_node)
{
    if (!new_node)
        return;

    struct node *head = *headref;
    if (!head)
    {
        printf("Empty list - adding at front\n");
        *headref = new_node;
        return;
    }

    struct node *cur = head;
    if (cur->data > new_node->data) // add at head
    {
        printf("curdata %d is GREATER than %d - adding at head\n", cur->data, new_node->data);
        new_node->next = cur;
        *headref = new_node;
        return;
    }
    while (cur != NULL)
    {
        if (cur->next && cur->next->data < new_node->data)
        {
            printf("Next contains %d which iss till LESS than %d - continuing\n", cur->next->data, new_node->data);
            cur = cur->next;
            continue;
        }
        else if (cur->next && cur->next->data > new_node->data)
        {
            printf("Next contains %d which is GREATER than %d - INSERTING\n", cur->next->data, new_node->data);
            new_node->next = cur->next;
            cur->next = new_node;
            return;
        }
        else // end of list, insert here
        {
            printf("End of list - add to tail\n");
            cur->next = new_node;
            return;
        }
    }
}

int main()
{
    printf("Yarly!\n");

    struct node* head = NULL;

    struct node *node1 = calloc_node(3);
    sorted_insert(&head, node1);
    dump_list(head);

    struct node *node2 = calloc_node(2);
    sorted_insert(&head, node2);
    dump_list(head);

    struct node *node3 = calloc_node(7);
    sorted_insert(&head, node3);
    dump_list(head);

    struct node *node4 = calloc_node(1);
    sorted_insert(&head, node4);
    dump_list(head);

    delete_list(&head);

}

