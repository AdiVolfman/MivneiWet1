
#include <stdexcept>
#include "Horse.h"


int Horse::keyCounter = START_KEY;
int Horse::horseCounter = START_COUNT;

Horse::Horse( unsigned int id , int speed )
    : m_id(id), m_speed(speed), m_herd(nullptr),m_node(nullptr),m_leader(nullptr),
m_key(START_KEY), m_leaderKey(START_KEY) {
    m_myCount = horseCounter;
    horseCounter++;
}

Horse::Horse(): m_id(0), m_speed(0), m_herd(nullptr),m_node(nullptr),m_leader(nullptr),
          m_key(START_KEY), m_leaderKey(START_KEY), m_myCount(horseCounter) {
     horseCounter++;
}

unsigned int Horse::getId() const {
    return m_id;
}

int Horse::getSpeed() const {
    return m_speed;
}

std::shared_ptr<Herd> Horse::getHerd() const {
    return m_herd;
}

 NodeList* Horse::getNode() const {
    return m_node;
}


void Horse::setHerd(std::shared_ptr<Herd> newHerd) {
    m_herd = newHerd;
}

void Horse::setLeader( std::shared_ptr<Horse> leader) {
    m_leader = leader;
}

void Horse::setNode(NodeList* newNode) {
    m_node=newNode;
}


void Horse::leave() {

    m_herd=nullptr;
    m_leaderKey = START_KEY;
    m_key = START_KEY;
    m_leader = nullptr;
    m_node= nullptr;

}

 std::shared_ptr<Horse> Horse::getLeader() const {
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

void Horse::join_herd( std::shared_ptr<Herd> newHerd , NodeList* newNode ) {
    m_herd = newHerd;
    m_node = newNode;
    setKey();
}


bool Horse::operator<(const Horse& other) const {
    return m_id < other.m_id;
}

bool Horse::operator>(const Horse& other) const {
    return m_id > other.m_id;
}


bool Horse::isFollow( std::shared_ptr<Horse> other) {
    auto leader = m_leader;
    if (other && leader && leader == other && this->getLeaderKey() == other->getKey()) {
        return true;
    }
    return false;
}


void Horse::follow( std::shared_ptr<Horse> other) {
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