#pragma once

#include <mutex>

typedef int Key;
typedef void* Value;

typedef struct {
    Key   key;
    Value value;
    int   value_size;
} Item;

typedef struct node_t {
    Item item;
    struct node_t* next;
    struct node_t* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    std::mutex  mtx;
} Queue;

typedef struct {
    bool success;
    Item item;
} Reply;

Node*  nalloc(Item item);
void   nfree(Node* node);
Node*  nclone(Node* node);

Reply  enqueue(Queue* queue, Item item);
Reply  dequeue(Queue* queue);
Queue* range(Queue* queue, Key start, Key end);
