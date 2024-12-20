
//
// Created by meshi on 19/12/2024.
//
#include "Horse.h"
#define START_KEY -1

#include "Horse.h"
#define START_KEY -1

Horse::Horse(unsigned int id, int speed)
    : m_id(id), m_speed(speed), m_herd(nullptr), m_key(START_KEY), m_leaderKey(START_KEY) {}

unsigned int Horse::getId() const {
    return m_id;
}

int Horse::getSpeed() const {
    return m_speed;
}

const Herd* Horse::getHerd() const {
    return m_herd;
}

void Horse::setHerd(Herd* newHerd) {
    m_herd = newHerd;
}

void Horse::setLeader(const std::weak_ptr<Horse>& leader) {
    m_leader = leader;
}

const std::weak_ptr<Horse> Horse::getLeader() const {
    return m_leader;
}

int Horse::getKey() const {
    return m_key;
}

void Horse::setKey() {
    if (m_herd == nullptr) {
      throw std::runtime_error("");
    }
    m_key = m_herd->getId();
    int id = m_id;
    int num = 0;
    while (id > 0) {
        num = id % 10;
        id = id / 10;
        m_key = m_key * 10;
        m_key += num;
    }
}

int Horse::getLeaderKey() const {
    return m_leaderKey;
}

void Horse::setLeaderKey(int leaderId) {
    m_leaderKey = leaderId;
}

void Horse::leave_herd() {
    if (m_herd == nullptr) {
       throw std::runtime_error("");
    }

    m_leaderKey = START_KEY;
    m_key = START_KEY;
    m_leader.reset();
    m_herd=nullptr;
}


void Horse::join_herd(Herd* newHerd) {
    if (newHerd == nullptr) {
       throw std::invalid_argument("");
    }
    m_herd = newHerd;
    setKey();
}


bool Horse::operator<(const Horse& other) const {
    return m_id < other.m_id;
}

bool Horse::operator>(const Horse& other) const {
    return m_id > other.m_id;
}

bool Horse::follow(const std::shared_ptr<Horse> &other) {
    if (m_leader.lock()==other &&
        m_leader.lock()->getLeaderKey() == other->getKey()) {
        return true;
    }
    return false;
}

Horse& Horse::operator=(const Horse& other) {
    if (this != &other) {
        m_id = other.m_id;
        m_speed = other.m_speed;
        m_leader = other.m_leader;
        m_herd = other.m_herd;
        m_key = other.m_key;
        m_leaderKey = other.m_leaderKey;
    }
    return *this;
}
