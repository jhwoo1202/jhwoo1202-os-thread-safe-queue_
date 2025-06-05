#include "qtype.h"
#include <cstdlib>
#include <cstring>
#include <mutex>

Node* nalloc(Item item) {
    Node* node = (Node*)std::malloc(sizeof(Node));
    if (!node) return nullptr;
    node->item.key = item.key;
    node->item.value_size = item.value_size;
    if (item.value_size > 0 && item.value != nullptr) {
        node->item.value = std::malloc(item.value_size);
        if (node->item.value) {
            std::memcpy(node->item.value, item.value, item.value_size);
        } else {
            std::free(node);
            return nullptr;
        }
    } else {
        node->item.value = nullptr;
    }
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void nfree(Node* node) {
    if (!node) return;
    if (node->item.value) {
        std::free(node->item.value);
    }
    std::free(node);
}

Node* nclone(Node* node) {
    if (!node) return nullptr;
    return nalloc(node->item);
}

void release(Queue* queue) {
    if (!queue) return;
    {
        std::lock_guard<std::mutex> lock(queue->mtx);
        Node* curr = queue->head;
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            nfree(tmp);
        }
        queue->head = queue->tail = nullptr;
    }
    std::free(queue);
}

Queue* init(void) {
    Queue* q = (Queue*)std::malloc(sizeof(Queue));
    if (!q) return nullptr;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}
