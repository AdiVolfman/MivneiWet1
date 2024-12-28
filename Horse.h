#pragma once
#ifndef HORSE_H
#define HORSE_H

#include <memory>
#include "Herd.h"

#define START_KEY -1
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
    long m_key;
    long m_leaderKey;
    long m_circleCheck ;
    bool m_leadsRoot;
    static long keyCounter ;




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

    long getKey() const;

    long getCircleCheck() const;

    long getLeaderKey() const;

    bool isLeadsToRoot()const;

    void setLeadsToRoot(bool answer);

    void setCircleCheck(long newCircleCheck);

    void setKey();

    void leave();

    void setLeaderKey(long leaderId);

    bool isFollow (const std::shared_ptr<Horse> &other);

    void join_herd(std::shared_ptr<Herd> newHerd,std::shared_ptr<NodeList> newNode);

    void follow (const std::shared_ptr<Horse> &other);

    bool operator<(const Horse& other) const;

    bool operator>(const Horse& other) const;

    Horse& operator=(const Horse& other);
};

#endif //HORSE_H
