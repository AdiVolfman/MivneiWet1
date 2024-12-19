//
// Created by meshi on 19/12/2024.
//
#include "Herd.h"

Herd::Herd(unsigned int id) : m_id(id), head(nullptr), tail(nullptr) {}

Herd::~Herd() {
    while (head) {
        Node* cur_node = head;
        head = head->next;
        delete cur_node;
    }
}

unsigned int Herd::getId() const {
    return m_id;
}

void Herd::addHorse(Horse& horse) {
    Node* new_HorseNode = new Node(horse);
    if (!head) {
        head = new_HorseNode;
        tail = new_HorseNode;
    } else {
        tail->next = new_HorseNode;
        tail = new_HorseNode;
    }
}

void Herd::removeHorse(unsigned int horseId) {
    Node* cur_node= head;
    Node* pre_node = nullptr;

    while (cur_node) {
        if (cur_node->horse.getId() == horseId) {
            if (pre_node) {
                pre_node->next = cur_node->next;
            } else {
                head = cur_node->next;
            }
            if (cur_node == tail) {
                tail = pre_node;
            }
            delete cur_node;
            return;
        }
        pre_node = cur_node;
        cur_node = cur_node->next;
    }
}


bool Herd::operator<(const Herd& other) const {
    return m_id < other.m_id;
}

bool Herd::operator>(const Herd& other) const {
    return m_id > other.m_id;
}
