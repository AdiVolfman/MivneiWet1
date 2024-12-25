#pragma once
#ifndef HERD_H
#define HERD_H

#include <memory>
#include <utility>
#include "Horse.h" // אין בעיה לכלול אותו פה


class Horse;


struct NodeList {
    std::shared_ptr<Horse> horse;
    NodeList* next;
    NodeList* prev;
    explicit NodeList( std::shared_ptr<Horse> horse, NodeList* next = nullptr,NodeList* prev = nullptr ) :
    horse(std::move(horse)), next(next), prev(prev)  {};
};

class Herd {

private:
    unsigned int m_id;

    int m_size;

    NodeList* head;

    NodeList* tail;


public:

    Herd(unsigned int id);

    Herd();

    ~Herd();

    unsigned int getId() const;

    void addHorse(std::shared_ptr<Horse> &horse);

    void removeHorse(unsigned int horseId);

    void removeHorse(NodeList* nodeToRemove);

    bool leads (int horseId, int otherHorseId);

    bool can_run_together () const;

    bool hasCycle() const;

    int getSize() const;

    bool operator<(const Herd& other) const;

    bool operator>(const Herd& other) const;

    Herd& operator=(const Herd& other);

};

#endif //HERD_H