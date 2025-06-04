#include "qtype.h"
#include <mutex>

std::mutex mtx;

Queue* init(void) {
    Queue* q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}
