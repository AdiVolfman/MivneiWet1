
//
// Created by meshi on 19/12/2024.
//
#include <stdexcept>
#include "Horse.h"
#include "Herd.h"
#define START_KEY -1
#define START_COUNT 1

Horse::Horse( unsigned int id , int speed )
    : m_id(id), m_speed(speed), m_herd(nullptr), m_key(START_KEY), m_leaderKey(START_KEY) {
    m_myCount=horseCounter;
    horseCounter++;
}

int Horse::keyCounter = START_KEY;
int Horse::horseCounter = START_COUNT;

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

int Horse::getkeyCounter() const {
    return keyCounter;
}

 int Horse::getMyCount() const {
     return m_myCount;
 }

int Horse::getHorseCounter() const {
    return horseCounter;
}

void Horse::setKey() {

    keyCounter++;
    m_key = keyCounter;

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


void Horse::join_herd(Herd* newHerd ) {
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


bool Horse::isFollow(const std::shared_ptr<Horse>& other) {
    auto leader = m_leader.lock();
    if (other && leader && leader == other && this->getLeaderKey() == other->getKey()) {
        return true;
    }
    return false;
}


void Horse::follow(const std::shared_ptr<Horse> &other) {
    m_leader = other;
   // m_leader.lock()->setLeaderKey(other->getKey());
    m_leaderKey = other->getKey();

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
