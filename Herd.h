//
// Created by meshi on 19/12/2024.
//

#ifndef HERD_H
#define HERD_H
#include "Horse.h"
#include <memory>
class Herd {

private:
    unsigned int m_id;
    int m_size;

    struct Node {
        std::shared_ptr<Horse> horse;
        Node* next;
        Node( std::shared_ptr<Horse> horse, Node* next = nullptr) : horse(horse),
        next(next) {}
     };

    Node* head;
    Node* tail;


public:

    Herd(unsigned int id);

    ~Herd();

    unsigned int getId() const;

    void addHorse(std::shared_ptr<Horse> &horse);

    void removeHorse(unsigned int horseId);

    bool leads (int horseId, int otherHorseId);

    bool operator<(const Herd& other) const;

    bool operator>(const Herd& other) const;
};

#endif //HERD_H
