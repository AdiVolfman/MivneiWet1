//
// Created by meshi on 19/12/2024.
//
#include "Herd.h"
#define SIZE0 0

Herd::Herd(unsigned int id) : m_id(id),m_size(SIZE0),head(nullptr), tail(nullptr) {}

Herd::~Herd() {
    while (head) {
        Node* cur_node = head;
        head = head->next;
        delete cur_node;
    }
}

unsigned int Herd::getId() const {
    return m_id;
}

int Herd::getSize() const {
    return m_size;
}


void Herd::addHorse(std::shared_ptr<Horse> &horse) {
    Node* new_HorseNode = new Node(horse);
    if (!head) {
        head = new_HorseNode;
        tail = new_HorseNode;
    } else {
        tail->next = new_HorseNode;
        tail = new_HorseNode;
    }
    horse->setKey();
    m_size++;

}

void Herd::removeHorse(unsigned int horseId) {
    Node* cur_node = head;
    Node* pre_node = nullptr;

    while (cur_node) {
        if (cur_node->horse && cur_node->horse->getId() == horseId) {
            // מחיקת הצומת הנוכחית
            if (pre_node) {
                pre_node->next = cur_node->next;
            } else {
                head = cur_node->next;
            }
            if (cur_node == tail) {
                tail = pre_node;
            }
            delete cur_node;
            m_size--; // עדכון גודל הרשימה רק אם סוס הוסר
            return;
        }
        pre_node = cur_node;
        cur_node = cur_node->next;
    }

    // אם לא נמצא הסוס עם ה-id, אין שינוי בגודל הרשימה
}


bool Herd::leads (int horseId, int otherHorseId) {

    bool found=false;
    Node* cur_node = head;
    std::shared_ptr<Horse> current = nullptr;
    std::shared_ptr<Horse> leader = nullptr;

    while (cur_node) {
        if (cur_node->horse->getId() == horseId) {
            current = cur_node->horse;
        }
        if (cur_node->horse->getId() == otherHorseId) {
            leader = cur_node->horse;
        }
        cur_node = cur_node->next;
    }

    while (current) {
        if(current -> isFollow(leader)) {
            found = true;
            break;
        }

        std::shared_ptr<Horse> next = current->getLeader().lock();

        if(current->isFollow(next)) {
            current = next;
        } else {
            break;
        }

    }
    return found;
}

bool Herd::can_run_together() const {

    Node* cur_node = head;
    Node* firstRoot=nullptr;
    Node* anotherRoot=nullptr;

   while (cur_node) {
        std::shared_ptr<Horse> isLeader = cur_node->horse->getLeader().lock();

        if (!cur_node->horse->isFollow(isLeader)) {
            if (firstRoot == nullptr) {
                firstRoot = cur_node;
            } else {
                anotherRoot = cur_node;
            }
        }
        cur_node = cur_node->next;
    }

    if (firstRoot == nullptr || anotherRoot != nullptr) {
        return false;
    }

    if (this->hasCycle()) {
        return false;
    }

    return true;
}

bool Herd::hasCycle() const {

    int arrSize = head->horse->getHorseCounter()+1;
    bool* visited = new bool[arrSize]();

    Node* cur_node = head;

    while (cur_node) {
        std::shared_ptr<Horse> cur_horse = cur_node->horse;

        if (visited[cur_horse->getMyCount()]) {
            cur_node = cur_node->next;
            continue;
        }

        while ( cur_horse ) {

            std::shared_ptr<Horse> next = cur_horse->getLeader().lock();

            if(next && next == cur_node->horse) {
                return true;
            }

            if(visited[cur_horse->getMyCount()]) {
                break;
            }

            visited[cur_horse->getMyCount()] = true;

            if (next && cur_horse->isFollow(next)) {
                cur_horse = next;
            } else {
                break;
            }

        }
        cur_node = cur_node->next;
    }
    delete[] visited;
    return false ;
}


bool Herd::operator<(const Herd& other) const {
    return m_id < other.m_id;
}

bool Herd::operator>(const Herd& other) const {
    return m_id > other.m_id;
}

Herd& Herd::operator=(const Herd& other) {
    if (this == &other) {
        return *this;
    }

    m_id = other.m_id;

    while (head) {
        Node* cur_node = head;
        head = head->next;
        delete cur_node;
    }

    tail = nullptr;
    m_size = SIZE0;

    Node* cur_other = other.head;
    while (cur_other) {
        addHorse(cur_other->horse); // Reuse the addHorse method
        cur_other = cur_other->next;
    }

    return *this;
}

