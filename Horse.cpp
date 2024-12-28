
#include <stdexcept>
#include "Horse.h"


long Horse::keyCounter = START_KEY;

Horse::Horse( unsigned int id , int speed )
    : m_id(id), m_speed(speed),m_leadsRoot(false), m_key(START_KEY) ,m_circleCheck(START_CIRCLE_CHECK), m_leaderKey(START_KEY) {
}

Horse::Horse(): m_id(0), m_speed(0),m_leadsRoot(false),
          m_key(START_KEY), m_leaderKey(START_KEY),m_circleCheck(START_CIRCLE_CHECK) {
}

unsigned int Horse::getId() const {
    return m_id;
}

int Horse::getSpeed() const {
    return m_speed;
}

long Horse::getCircleCheck() const {
    return m_circleCheck;
}


std::shared_ptr<Herd> Horse::getHerd() const {
    if (m_herd.expired()) {
        return nullptr;
    }
    return m_herd.lock();
}

 std::shared_ptr<NodeList> Horse::getNode() const {
    if (m_node.expired()) {
        return nullptr;
    }
    return m_node.lock();
}

bool Horse::isLeadsToRoot() const {
    return m_leadsRoot;
}

void Horse::setLeadsToRoot(bool answer) {
    m_leadsRoot=answer;
}

void Horse::setCircleCheck(long newCircleCheck) {

    m_circleCheck=newCircleCheck;
}

void Horse::setHerd(const std::shared_ptr<Herd>& newHerd) {
    m_herd = newHerd;
}

void Horse::setLeader(const std::shared_ptr<Horse>& leader) {
    m_leader = leader;
}

void Horse::setNode(const std::shared_ptr<NodeList> &newNode) {
    m_node=newNode;
}

void Horse::resetNode() {
    m_node.reset();
}

void Horse::leave() {

    m_herd.reset();
    m_leaderKey = START_KEY;
    m_key = START_KEY;
    m_leader.reset();
    m_node.reset();

}

const std::shared_ptr<Horse> Horse::getLeader() const {
    if (m_leader.expired()) {
        return nullptr;
    }
    return m_leader.lock();
}

long Horse::getKey() const {
    return m_key;
}

void Horse::setKey() {

    keyCounter++;
    m_key = keyCounter;

}

long Horse::getLeaderKey() const {
    return m_leaderKey;
}

void Horse::setLeaderKey( long leaderId) {
    m_leaderKey = leaderId;
}

void Horse::join_herd(std::shared_ptr<Herd> newHerd , std::shared_ptr<NodeList> newNode ) {
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


bool Horse::isFollow(const std::shared_ptr<Horse>& other) {
    if (m_leader.expired()) {
        return false;
    }
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
