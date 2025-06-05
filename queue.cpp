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

Reply enqueue(Queue* queue, Item item) {
    if (!queue) {
        return { false, {0, nullptr, 0} };
    }
    Node* newNode = nalloc(item);
    if (!newNode) {
        return { false, {0, nullptr, 0} };
    }
    std::lock_guard<std::mutex> lock(queue->mtx);
}

 Node* curr = queue->head;
    while (curr) {
        if (curr->item.key == item.key) {
            if (curr->item.value) {
                std::free(curr->item.value);
            }
            curr->item.value_size = item.value_size;
            if (item.value_size > 0 && item.value != nullptr) {
                curr->item.value = std::malloc(item.value_size);
                std::memcpy(curr->item.value, item.value, item.value_size);
            } else {
                curr->item.value = nullptr;
            }
            nfree(newNode);
            return { true, curr->item };
        }
        curr = curr->next;
    }
}

    if (!queue->head) {
        queue->head = queue->tail = newNode;
    } else {
        Node* pos = queue->head;
        while (pos && pos->item.key <= newNode->item.key) {
            pos = pos->next;
        }
        if (pos == queue->head) {
            newNode->next = queue->head;
            queue->head->prev = newNode;
            queue->head = newNode;
        } else if (!pos) {
            newNode->prev = queue->tail;
            queue->tail->next = newNode;
            queue->tail = newNode;
        } else {
            newNode->next = pos;
            newNode->prev = pos->prev;
            pos->prev->next = newNode;
            pos->prev = newNode;
        }

    return { true, newNode->item };
}
Reply dequeue(Queue* queue) {
    if (!queue) {
        return { false, {0, nullptr, 0} };
    }
    std::lock_guard<std::mutex> lock(queue->mtx);
    if (!queue->head) {
        return { false, {0, nullptr, 0} };
    }
    Node* node = queue->head;
    Item result = node->item;

    queue->head = node->next;
    if (queue->head) {
        queue->head->prev = nullptr;
    } else {
        queue->tail = nullptr;
    }

    std::free(node);
    return { true, result };
}
