//
// Created by meshi on 19/12/2024.
//

#ifndef HERD_H
#define HERD_H
#include "Horse.h"
#include <memory>

class Horse;


struct Node {
    std::shared_ptr<Horse> horse;
    Node* next;
    Node* prev;
    Node( std::shared_ptr<Horse> horse, Node* next = nullptr) : horse(horse),
    next(next), prev(prev)  {};
};

class Herd {

private:
    unsigned int m_id;

    int m_size;

    Node* head;

    Node* tail;


public:

    Herd(unsigned int id);

    ~Herd();

    unsigned int getId() const;

    void addHorse(std::shared_ptr<Horse> &horse);

    void removeHorse(unsigned int horseId);

    void removeHorse(Node* nodeToRemove);

    bool leads (int horseId, int otherHorseId);

    bool can_run_together () const;

    bool hasCycle() const;

    int getSize() const;

    bool operator<(const Herd& other) const;

    bool operator>(const Herd& other) const;

    Herd& operator=(const Herd& other);

};

#endif //HERD_H