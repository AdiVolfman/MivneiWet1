
#include <iostream>
#include "Herd.h"
#define SIZE0 0

Herd::Herd(unsigned int id) : m_id(id), m_size(SIZE0), head(nullptr), tail(nullptr) {
}

Herd::Herd(): m_id(0), m_size(SIZE0), head(nullptr), tail(nullptr) {
}

Herd::~Herd() {
    while (head) {
        std::shared_ptr<NodeList> cur_node = head;
        head = head->next;
    }
}

unsigned int Herd::getId() const {
    return m_id;
}

int Herd::getSize() const {
    return m_size;
}


void Herd::addHorse(const std::shared_ptr<Herd> &herd, std::shared_ptr<Horse> &horse) {
    std::shared_ptr<NodeList> new_HorseNode = nullptr;

    try {
        new_HorseNode = std::make_shared<NodeList>(horse);
    } catch (const std::bad_alloc &e) {
        throw;
    }

    if (!head) {
        head = new_HorseNode;
        tail = new_HorseNode;
    } else {
        tail->next = new_HorseNode;
        new_HorseNode->prev = tail;
        tail = new_HorseNode;
    }
    m_size++;;
    horse->join_herd(herd, new_HorseNode);
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

void Herd::removeHorse(std::shared_ptr<NodeList> nodeToRemove) {
    if (!nodeToRemove) {
        return;
    }

    const auto& horse = nodeToRemove->horse;

    // איפוס המצביע ב-Horse
    if (horse) {
        horse->resetNode(); // איפוס ל-weak_ptr ריק
    }

    // עדכון הקשרים ברשימה הכפולה
    if (nodeToRemove == head) {
        head = nodeToRemove->next;
        if (head) {
            head->prev.reset(); // איפוס prev ב-NodeList החדש
        } else {
            tail = nullptr;
        }
    } else if (nodeToRemove == tail) {
        tail = nodeToRemove->prev.lock();
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        if (auto prev = nodeToRemove->prev.lock()) {
            prev->next = nodeToRemove->next;
        }
        if (nodeToRemove->next) {
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
    }

    m_size--;
}


bool Herd::leads(int horseId, int otherHorseId) {
    bool found = false;
    std::shared_ptr<NodeList> cur_node = head;
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

    std::shared_ptr<Horse> circleCheck = current;
    while (current) {
        if (current->isFollow(leader)) {
            found = true;
            break;
        }

        std::shared_ptr<Horse> next = current->getLeader();

        if (circleCheck == next) {
            break;
        }

        if (current->isFollow(next)) {
            current = next;
        } else {
            break;
        }
    }
    return found;
}

bool Herd::can_run_together() const {
    std::shared_ptr<NodeList> cur_node = head;
    std::shared_ptr<NodeList> firstRoot = nullptr;
    std::shared_ptr<NodeList> anotherRoot = nullptr;

    while (cur_node) {
        std::shared_ptr<Horse> isLeader = cur_node->horse->getLeader();

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
    bool *visited = nullptr;

    try {
        visited = new bool[arrSize]();
    } catch (const std::bad_alloc &e) {
        throw;
    }

    std::shared_ptr<NodeList> cur_node = head;

    while (cur_node) {
        std::shared_ptr<Horse> cur_horse = cur_node->horse;

        if (visited[cur_horse->getMyCount()]) {
            cur_node = cur_node->next;
            continue;
        }

        while (cur_horse) {
            std::shared_ptr<Horse> next = cur_horse->getLeader();

            if (next && next == cur_node->horse) {
                delete[] visited;
                return true;
            }

            if (visited[cur_horse->getMyCount()]) {
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
    return false;
}


bool Herd::operator<(const Herd &other) const {
    return m_id < other.m_id;
}

bool Herd::operator>(const Herd &other) const {
    return m_id > other.m_id;
}

// Herd &Herd::operator=(const Herd &other) {
//     if (this == &other) {
//         return *this;
//     }
//     try {
//         m_id = other.m_id;
//
//         while (head) {
//             std::shared_ptr<NodeList> cur_node = head;
//             head = head->next;
//         }
//
//         tail = nullptr;
//         m_size = SIZE0;
//
//         std::shared_ptr<NodeList> cur_other = other.head;
//         while (cur_other) {
//             addHorse(cur_other->horse); // Reuse the addHorse method
//             cur_other = cur_other->next;
//         }
//     } catch (const std::bad_alloc &) {
//         throw;
//     }
//
//     return *this;
// }

void Herd::printList() const {
    std::shared_ptr<NodeList> current = head;
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



