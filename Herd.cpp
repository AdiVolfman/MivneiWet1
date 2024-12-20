//
// Created by meshi on 19/12/2024.
//
#include "Herd.h"
#define SIZE0 0

Herd::Herd(unsigned int id) : m_id(id),m_size(SIZE0),head(nullptr), tail(nullptr) {}

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

void Herd::addHorse(std::shared_ptr<Horse> &horse) {
    Node* new_HorseNode = new Node(horse);
    if (!head) {
        head = new_HorseNode;
        tail = new_HorseNode;
    } else {
        tail->next = new_HorseNode;
        tail = new_HorseNode;
    }
    m_size++;
}

void Herd::removeHorse(unsigned int horseId) {
    Node* cur_node = head;
    Node* pre_node = nullptr;

    while (cur_node) {
        if (cur_node->horse->getId() == horseId) {
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
    m_size--;
}

bool Herd::leads (int horseId, int otherHorseId) {

    bool found=false;
    Node* cur_node = head;
    Node *first;
    Node *second;

    for (int i = 0; i < m_size; i++) {
        if ( horseId == cur_node->horse->getId()) {
            first->horse = cur_node->horse;
            break;
        }
        cur_node = cur_node->next;
    }
    for (int i = 0; i < m_size; i++) {
        if ( otherHorseId == cur_node->horse->getId()) {
            second->horse = cur_node->horse;
            break;
        }
        cur_node = cur_node->next;
    }

    Node *curHorse = first;
    Node* next;

    for (int i = 0; i < m_size; i++) {
        if(curHorse->horse->follow(next->horse)) {
            found=true;
            break;
        }
        curHorse=next;
    }
    return found;
}

bool Herd::operator<(const Herd& other) const {
    return m_id < other.m_id;
}

bool Herd::operator>(const Herd& other) const {
    return m_id > other.m_id;
}
