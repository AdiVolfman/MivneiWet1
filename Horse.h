//
// Created by meshi on 19/12/2024.
//

#ifndef HORSE_H
#define HORSE_H
#include "Followers.h"
#include <memory>

class Horse {
private:
    unsigned int m_id;
    int m_speed;
    Horse* m_leader;
    int m_herd;
    std::shared_ptr<Followers> m_followers;


public:

    Horse(unsigned int id, int speed);

    unsigned int getId() const;

    int getSpeed() const;

    void setLeader(Horse* leader);

    Horse* getLeader() const;

    void setFollowers();

    bool operator<(const Horse& other) const;

    bool operator>(const Horse& other) const;
};

#endif //HORSE_H
