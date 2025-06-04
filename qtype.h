//// qtype.h: Thread-safe Queue 타입 정의

#pragma once

typedef int Key;
typedef int Value;

typedef struct {
    Key key;
    Value value;
} Item;

typedef struct node_t {
    Item item;
    struct node_t* next;
    struct node_t* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

typedef struct {
    bool success;
    Item item;
} Reply;

Queue* init(void);
void release(Queue* queue);
Reply enqueue(Queue* queue, Item item);
Reply dequeue(Queue* queue);
Queue* range(Queue* queue, Key start, Key end);
