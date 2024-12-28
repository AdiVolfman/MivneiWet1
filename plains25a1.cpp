// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"

#include "Herd.h"
#include "Horse.h"

long Plains::circleCheck = START_KEY;

Plains::Plains() {
    try {
        this->horseTree = new AVLTree<Horse>();
    }
    catch (const std::bad_alloc &e) {
        throw std::bad_alloc();
    }
    try {
        this->herdTree = new AVLTree<Herd>();
    }
    catch (const std::bad_alloc &e) {
        throw std::bad_alloc();
    }
    try {
        this->emptyHerdTree = new AVLTree<Herd>();
    }
    catch (const std::bad_alloc &e) {
        throw std::bad_alloc();
    }
}

Plains::~Plains() {
    delete this->horseTree;
    delete this->herdTree;
    delete this->emptyHerdTree;
}


StatusType Plains::add_herd(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if ((herdTree->find(herdId)) != nullptr || emptyHerdTree->find(herdId)) {
        return StatusType::FAILURE;
    }
    try {
        // Directly create shared_ptr without using raw pointer
        std::shared_ptr<Herd> sharedPtr = std::make_shared<Herd>(herdId);
        emptyHerdTree->insert(herdId, sharedPtr);
    }
    catch (std::bad_alloc &e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::remove_herd(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!(emptyHerdTree->find(herdId))) {
        return StatusType::FAILURE;
    }

    emptyHerdTree->remove(herdId);
    return StatusType::SUCCESS;
}

StatusType Plains::add_horse(int horseId, int speed) {
    if (horseId <= 0 || speed <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (horseTree->find(horseId)) {
        return StatusType::FAILURE;
    }
    try {
        // Directly create shared_ptr without using raw pointer
        std::shared_ptr<Horse> sharedPtr = std::make_shared<Horse>(horseId,
                                                                   speed);
        horseTree->insert(horseId, sharedPtr);
    }
    catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::join_herd(int horseId, int herdId) {
    //find horse
    //Check if m_key =START
    //If so, the horse is not in any herd
    //find herd- Check if the herd exists?
    //apply add_horse at herd
    //add line: horse->join_herd(this);

    if (horseId <= 0 || herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<Horse> found_horse = horseTree->find(horseId);
    if (!found_horse) {
        return StatusType::FAILURE;
    }

    if (found_horse->getHerd() || found_horse->getKey() != START_KEY) {
        return StatusType::FAILURE;
    }

    std::shared_ptr<Herd> found_herd;
    bool isEmptyHerd = false;

    if (!herdTree->find(herdId)) {
        if (emptyHerdTree->find(herdId)) {
            found_herd = emptyHerdTree->find(herdId);
            isEmptyHerd = true;
        } else {
            return StatusType::FAILURE;
        }
    } else {
        found_herd = herdTree->find(herdId);
    }

    try {
        found_herd->addHorse(found_herd, found_horse);

        if (isEmptyHerd) {
            emptyHerdTree->remove(herdId);
            herdTree->insert(herdId, found_herd);
        }
    }
    catch (std::bad_alloc &e) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId) {
    //find 2 horses
    //chack they are at same herd
    //apply follow(horse2) at horse1


    if (horseId <= 0 || horseToFollowId <= 0 || horseId == horseToFollowId) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Horse> horse = horseTree->find(horseId);
    std::shared_ptr<Horse> horseToFollow = horseTree->find(horseToFollowId);

    if (!horse || !horseToFollow) {
        return StatusType::FAILURE;
    }

    if (horse->getHerd() != horseToFollow->getHerd() ||
        horseToFollow->getKey() == START_KEY
        || horse->getKey() == START_KEY) {
        return StatusType::FAILURE;
    }

    horse->follow(horseToFollow);

    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId) {
    //find the horse
    //chack if in any herd
    //apply removeHorse at Herd
    //remove follow from followers- apply leave_herd at Horse
    // update at Horse class

    if (horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    const std::shared_ptr<Horse> &found_horse = horseTree->find(horseId);
    if (!found_horse) {
        return StatusType::FAILURE;
    }

    const std::shared_ptr<Herd> &found_herd = found_horse->getHerd();

    if (!found_herd) {
        return StatusType::FAILURE;
    }
//---שגיאה מכאן
    const std::shared_ptr<NodeList> &horseToRemove = found_horse->getNode();
    if (!horseToRemove) {
        return StatusType::FAILURE;
    }

    found_herd->removeHorse(horseToRemove);
    found_horse->leave();

    const int herdId = found_herd->getId();

    if (found_herd->getSize() < 1) {
        emptyHerdTree->insert(herdId, found_herd);
        herdTree->remove(herdId);
    }

    return StatusType::SUCCESS;
}


output_t<int> Plains::get_speed(int horseId) {

    if (horseId < 1) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<Horse> found_horse;
    if (!horseTree->find(horseId)) {
        return StatusType::FAILURE;

    }
    found_horse = horseTree->find(horseId);
    if (!found_horse) {
        return StatusType::FAILURE;
    }
    int answer = found_horse->getSpeed();
    return answer;

}

output_t<bool> Plains::leads(int horseId, int otherHorseId) {
    //find hourse one, hourse two
    //check if they at the same herd- else return false
    // apply leads at the herd

    if (horseId <= 0 || otherHorseId <= 0 || horseId == otherHorseId) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Horse> horse = horseTree->find(horseId);
    std::shared_ptr<Horse> otherHors = horseTree->find(otherHorseId);

    if (!horse || !otherHors) {
        return StatusType::FAILURE;
    }

    if (horse->getHerd() != otherHors->getHerd()) {
        return false;
    }

    std::shared_ptr<Herd> common_herd = horse->getHerd();
    if (!common_herd) {
        return false;
    }
    circleCheck++;
    return common_herd->leads(horseId, otherHorseId, circleCheck);
}

output_t<bool> Plains::can_run_together(int herdId) {
    //find herd
    //apply can_run_together at herd

    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<Herd> found_herd = herdTree->find(herdId);
    if (!found_herd) {
        return StatusType::FAILURE;
    }

    bool answer;
    try {
        circleCheck++;
        answer = found_herd->can_run_together(circleCheck);
        return answer;
    }
    catch (std::bad_alloc &e) {
        return StatusType::FAILURE;
    }
}
