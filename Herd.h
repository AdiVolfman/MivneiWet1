#pragma once
#ifndef HERD_H
#define HERD_H

#include <memory>
#include <utility>
#include "Horse.h"


class Horse;


struct NodeList {
    std::shared_ptr<Horse> horse;
    std::shared_ptr<NodeList> next;
    std::weak_ptr<NodeList> prev;
    explicit NodeList( std::shared_ptr<Horse> horse, std::shared_ptr<NodeList> next = nullptr,std::weak_ptr<NodeList>
        prev = std::weak_ptr<NodeList>() ) :
    horse(std::move(horse)), next(std::move(next)),prev(std::move(prev))  {};
};

class Herd {

private:
    unsigned int m_id;

    int m_size;

     std::shared_ptr<NodeList> head;

     std::shared_ptr<NodeList> tail;


public:

    Herd(unsigned int id);

    Herd();

    ~Herd();

    unsigned int getId() const;

    std::shared_ptr<NodeList> addHorse(std::shared_ptr<Horse> &horse);
    void addHorse(const std::shared_ptr<Herd> &herd, std::shared_ptr<Horse> &horse);

    void removeHorse(unsigned int horseId);

    void removeHorse(std::shared_ptr<NodeList> nodeToRemove);

    bool leads (int horseId, int otherHorseId, long circleCheck);

    bool can_run_together ( long circleCheck )  const;

    bool hasCycle( long circleCheck ) const;

    int getSize
    () const;

    bool operator<(const Herd& other) const;

    bool operator>(const Herd& other) const;

    Herd& operator=(const Herd& other);

    void printList() const;

};



#endif //HERD_H