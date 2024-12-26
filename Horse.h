#pragma once
#ifndef HORSE_H
#define HORSE_H

#include <memory>
#include "Herd.h"

#define START_KEY -1
#define START_COUNT 1
#define START_CIRCLE_CHECK 0

class Herd;     // הכרזה מוקדמת על Herd
struct  NodeList; // הכרזה מוקדמת על NodeList

class Horse {
private:
    unsigned int m_id;
    int m_speed;
    std::weak_ptr<Horse> m_leader;
    std::weak_ptr<Herd> m_herd;
    std::weak_ptr<NodeList> m_node;
    int m_key;
    int m_leaderKey;
    int m_myCount;
    long m_circleCheck ;
    static long keyCounter ;
    static long horseCounter ;



public:

    Horse(unsigned int id, int speed);

    Horse ();

    unsigned int getId() const;

    int getSpeed() const;

    void setLeader(const std::shared_ptr<Horse> &leader);

    void setHerd( const std::shared_ptr<Herd>& newHerd);

    void setNode (const std::shared_ptr<NodeList> &newNode);
    void resetNode ();

    const std::shared_ptr<Horse> getLeader() const;

    std::shared_ptr<Herd> getHerd() const;

    std::shared_ptr<NodeList>  getNode() const;

    int getKey() const;

    long getCircleCheck() const;

    int getMyCount() const;

    int getHorseCounter() const;

    int getkeyCounter() const;

    int getLeaderKey() const;

    void setCircleCheck(long newCircleCheck);

    void setKey();

    void leave();

    void setLeaderKey(int leaderId);

    bool isFollow (const std::shared_ptr<Horse> &other);

    void join_herd(std::shared_ptr<Herd> newHerd,std::shared_ptr<NodeList> newNode);

    void follow (const std::shared_ptr<Horse> &other);

    bool operator<(const Horse& other) const;

    bool operator>(const Horse& other) const;

    Horse& operator=(const Horse& other);
};

#endif //HORSE_H
