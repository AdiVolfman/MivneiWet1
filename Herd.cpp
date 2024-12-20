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
    Node *first=nullptr;
    Node *second=nullptr;

    while (cur_node) {
        if (cur_node->horse->getId() == horseId) {
            first = cur_node;
        }
        if (cur_node->horse->getId() == otherHorseId) {
            second = cur_node;
        }
        cur_node = cur_node->next;
    }

    cur_node = first;

    while (cur_node) {
        if(cur_node->horse->isFollow(second->horse)) {
            found=true;
            break;
        }
        cur_node=cur_node->next;
    }
    return found;
}

bool Herd::can_run_together() const {

    Node* cur_node = head;
    Node* root=nullptr;

    while (cur_node) {
        std::shared_ptr<Horse> isLeader =
            cur_node->horse->getLeader().lock();

        if(!cur_node->horse->isFollow(isLeader)) {
            root=cur_node;
            break;
        }
        cur_node = cur_node->next;
    }

    if(!root) {
        return false;}

    cur_node=head;
    while (cur_node) {
        if(cur_node!=root) {
            if(!leads(cur_node->horse->getId(),
                root->horse->getHerd())) {
                return false;
            }
        }
        cur_node = cur_node->next;
    }
    return true;
}


bool Herd::operator<(const Herd& other) const {
    return m_id < other.m_id;
}

bool Herd::operator>(const Herd& other) const {
    return m_id > other.m_id;
}

Herd& Herd::operator=(const Herd& other) {
    if (this == &other) {
        return *this;
    }

    m_id = other.m_id;

    while (head) {
        Node* cur_node = head;
        head = head->next;
        delete cur_node;
    }

    tail = nullptr;
    m_size = SIZE0;

    Node* cur_other = other.head;
    while (cur_other) {
        addHorse(cur_other->horse); // Reuse the addHorse method
        cur_other = cur_other->next;
    }

    return *this;
}

