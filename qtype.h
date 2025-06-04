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
