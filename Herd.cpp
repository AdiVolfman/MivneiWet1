
#include <iostream>
#include "Herd.h"
#define SIZE0 0

Herd::Herd(unsigned int id) : m_id(id),m_size(SIZE0),head(nullptr), tail(nullptr) {}

Herd::Herd():m_id(0),m_size(SIZE0),head(nullptr), tail(nullptr) {}

Herd::~Herd() {
    while (head) {
        NodeList* cur_node = head;
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

    NodeList* new_HorseNode = nullptr;

    try {
        new_HorseNode = new NodeList(horse);
    } catch (const std::bad_alloc& e) {
        throw;
    }

    if (!head) {
        head = new_HorseNode;
        tail = new_HorseNode;
    }  else {
        tail->next = new_HorseNode;
        new_HorseNode->prev = tail;
        tail = new_HorseNode;
    }
    m_size++;;
    horse->join_herd( this, new_HorseNode );

}

/*
void Herd::removeHorse(unsigned int horseId) {
    NodeList* cur_node = head;
    NodeList* pre_node = nullptr;

    while (cur_node) {
        if (cur_node->horse && cur_node->horse->getId() == horseId) {
            if (pre_node) {
                pre_node->next = cur_node->next;
                if (cur_node->next) {
                    cur_node->next->prev = pre_node;
                }
            } else {
                head = cur_node->next;
                if (head) {
                    head->prev = nullptr;
                }
            }
            if (cur_node == tail) {
                tail = pre_node;
            }
            delete cur_node;
            m_size--;
            return;
        }
        pre_node = cur_node;
        cur_node = cur_node->next;
    }
}
*/

void Herd::removeHorse(NodeList* nodeToRemove) {
    if (!nodeToRemove) {
        return;
    }

    if (nodeToRemove == head) {
        head = nodeToRemove->next; // עדכון הראש לצומת הבא
        if (head) {
            head->prev = nullptr; // הראש החדש צריך להצביע ל-null ב-prev
        } else {
            tail = nullptr; // אם הרשימה ריקה, tail גם מתאפס
        }
    } else if (nodeToRemove == tail) {
        tail = nodeToRemove->prev; // עדכון הסוף לצומת הקודם
        if (tail) {
            tail->next = nullptr; // tail החדש צריך להצביע ל-null ב-next
        }
    } else {
        if (nodeToRemove->prev) {
            nodeToRemove->prev->next = nodeToRemove->next;
        }
        if (nodeToRemove->next) {
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
    }
    m_size--;
    delete nodeToRemove;
}



bool Herd::leads (int horseId, int otherHorseId) {

    bool found=false;
    NodeList* cur_node = head;
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

    NodeList* cur_node = head;
    NodeList* firstRoot=nullptr;
    NodeList* anotherRoot=nullptr;

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

    int arrSize = head->horse->getHorseCounter() + 1;
    bool* visited = nullptr;

    try {
        visited = new bool[arrSize]();
    } catch (const std::bad_alloc& e) {
        throw;
    }

    NodeList* cur_node = head;

    while (cur_node) {
        std::shared_ptr<Horse> cur_horse = cur_node->horse;

        if (visited[cur_horse->getMyCount()]) {
            cur_node = cur_node->next;
            continue;
        }

        while ( cur_horse ) {

            std::shared_ptr<Horse> next = cur_horse->getLeader().lock();

            if(next && next == cur_node->horse) {
                delete[] visited;
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
    try {
    m_id = other.m_id;

    while (head) {
        NodeList* cur_node = head;
        head = head->next;
        delete cur_node;
    }

    tail = nullptr;
    m_size = SIZE0;

    NodeList* cur_other = other.head;
    while (cur_other) {
        addHorse(cur_other->horse); // Reuse the addHorse method
        cur_other = cur_other->next;
    }
    } catch (const std::bad_alloc&) {
        throw;
    }

    return *this;
}

void Herd::printList() const {
    NodeList* current = head;
    std::cout << "Herd ID: " << m_id << " | Size: " << m_size << " | Horses: ";

    // מעבר על הרשימה והדפסת כל סוס
    while (current) {
        if (current->horse) {
            std::cout << current->horse->getId() << " ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}



