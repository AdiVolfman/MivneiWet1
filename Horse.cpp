
//
// Created by meshi on 19/12/2024.
//
#include "Horse.h"
#define NO_HERD -1

Horse::Horse(unsigned int id, int speed) : m_id(id), m_speed(speed),
m_leader(nullptr),m_herd(nullptr), m_followers(nullptr){
}

unsigned int Horse::getId() const {
    return m_id;
}

int Horse::getSpeed() const {
    return m_speed;
}

void Horse::setHerd(Herd* newHerd) {
    m_herd=newHerd;
}

void Horse::setLeader(Horse* leader) {
     m_leader=leader;
}

Horse *Horse::getLeader() const {
    return m_leader;
}

void Horse::leave_herd(int horseId) {
    m_followers.reset();
    Horse::setFollowers();
    m_herd=nullptr;
    m_leader=nullptr;

}


void Horse::setFollowers() {
    try {
        m_followers = std::make_shared<Followers>(m_id);
    } catch (const std::bad_alloc) {
        m_followers.reset();
        throw;
    }
}


bool Horse::operator<(const Horse& other) const {
    return m_id < other.m_id;
}

bool Horse::operator>(const Horse& other) const {
    return m_id > other.m_id;
}

