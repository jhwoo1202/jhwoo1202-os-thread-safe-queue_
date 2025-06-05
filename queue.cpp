#include "qtype.h"
#include <cstdlib>
#include <cstring>
#include <mutex>

Queue* init(void) {
    Queue* q = (Queue*)std::malloc(sizeof(Queue));
    if (!q) return nullptr;
    q->head = nullptr;
    q->tail = nullptr;

    return q;
}
