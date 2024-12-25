#pragma once
#ifndef HORSE_H
#define HORSE_H

#include <memory>
#include "Herd.h"

#define START_KEY -1
#define START_COUNT 1

class Herd;     // הכרזה מוקדמת על Herd
struct  NodeList; // הכרזה מוקדמת על NodeList

class Horse {
private:
    unsigned int m_id;
    int m_speed;
    std::weak_ptr<Horse> m_leader;
    std::shared_ptr<Herd> m_herd;
    NodeList* m_node;
    int m_key;
    int m_leaderKey;
    int m_myCount;
    static int keyCounter ;
    static int horseCounter ;



public:

    Horse(unsigned int id, int speed);

    Horse ();

    unsigned int getId() const;

    int getSpeed() const;

    void setLeader(const std::weak_ptr<Horse> &leader);

    void setHerd( std::shared_ptr<Herd> newHerd);

    const std::weak_ptr<Horse> getLeader() const;

    std::shared_ptr<Herd> getHerd() const;

    NodeList* getNode() const;

    int getKey() const;

    int getMyCount() const;

    int getHorseCounter() const;

    int getkeyCounter() const;

    int getLeaderKey() const;

    void setKey();

    void leave();

    void setLeaderKey(int leaderId);

    bool isFollow (const std::shared_ptr<Horse> &other);

    void join_herd(std::shared_ptr<Herd> newHerd,NodeList* newNode);

    void follow (const std::shared_ptr<Horse> &other);

    bool operator<(const Horse& other) const;

    bool operator>(const Horse& other) const;

    Horse& operator=(const Horse& other);
};

#endif //HORSE_H
