
//
// Created by meshi on 19/12/2024.
//

#ifndef HORSE_H
#define HORSE_H
#include "Herd.h"
#include <memory>

class Herd;

class Horse {
private:
    unsigned int m_id;
    int m_speed;
    std::weak_ptr<Horse> m_leader;
    Herd* m_herd;
    int m_key;
    int m_leaderKey;
    static int keyCounter ;


public:

    Horse(unsigned int id, int speed);

    unsigned int getId() const;

    int getSpeed() const;

    void setLeader(const std::weak_ptr<Horse> &leader);

    void setHerd( Herd* newHerd);

    const std::weak_ptr<Horse> getLeader() const;

    const Herd* getHerd() const;

    int getKey() const;

    int getkeyCounter() const;

    int getLeaderKey() const;

    void setKey();

    void setLeaderKey(int leaderId);

    void leave_herd();

    bool isFollow (const std::shared_ptr<Horse> &other);

    void join_herd(Herd* newHerd);

    void follow (const std::shared_ptr<Horse> &other);

    bool operator<(const Horse& other) const;

    bool operator>(const Horse& other) const;

    Horse& operator=(const Horse& other);
};

#endif //HORSE_H
