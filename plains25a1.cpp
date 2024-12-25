// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"

#include "Horse.h"


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


StatusType Plains::add_herd(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!(herdTree->find(herdId))) {
        return StatusType::FAILURE;
    }
    Herd *h = nullptr;
    try {
        h = new Herd(herdId);
    }
    catch (std::bad_alloc &e) {
        return StatusType::FAILURE;
    }
    std::shared_ptr<Herd> sharedPtr = std::make_shared<Herd>(*h);
    herdTree->insert(herdId, sharedPtr);
    return StatusType::SUCCESS;
}

StatusType Plains::remove_herd(int herdId) {
    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!(herdTree->find(herdId))) {
        return StatusType::FAILURE;
    }
    herdTree->remove(herdId);
    return StatusType::SUCCESS;
}

StatusType Plains::add_horse(int horseId, int speed) {
    if (horseId <= 0 || speed <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (horseTree->find(horseId)) {
        return StatusType::FAILURE;
    }
    Horse *h;
    try {
        h = new Horse(horseId, speed);
    }
    catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    std::shared_ptr<Horse> sharedP = make_shared<Horse>(*h);
    horseTree->insert(horseId, sharedP);
    return StatusType::SUCCESS;
}

StatusType Plains::join_herd(int horseId,
                             int herdId) {//couldnt implement due to lack of herd key in horse
    if (horseId <= 0 || herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Herd> herdFound = herdTree->find(herdId);
    std::shared_ptr<Horse> horseFound = horseTree->find(horseId);

    //find horse
    //Check if m_key =START
    //If so, the horse is not in any herd
    //find herd- Check if the herd exists?
    //apply add_horse at herd
    //add line: horse->join_herd(this);

    std::shared_ptr<Horse> found_horse;
    std::shared_ptr<Herd> found_herd;

    if (horseId <= 0 || herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (found_horse->getKey() != START_KEY) {
        return StatusType::FAILURE;
    }

    found_herd->addHorse(found_horse);

    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId) {
    //find 2 horses
    //chack they are at same herd
    //apply follow(horse2) at horse1

    std::shared_ptr<Horse> found_horse1;
    std::shared_ptr<Horse> found_horse2;

    if (horseId <= 0 || horseToFollowId <= 0 || horseId == horseToFollowId) {
        return StatusType::FAILURE;
    }

    if (found_horse1->getHerd() != found_horse2->getHerd()) {
        return StatusType::FAILURE;
    }

    if (found_horse1->getKey() == START_KEY || found_horse1->getKey() ==
                                               START_KEY) {
        return StatusType::FAILURE;
    }

    found_horse1->follow(found_horse2);

    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId) {
    //find the horse
    //chack if in any herd
    //apply removeHorse at Herd
    //remove follow from followers- apply leave_herd at Horse
    // update at Horse class

    std::shared_ptr<Horse> found_horse;

    Herd *found_herd = found_horse->getHerd();

    if (horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (found_horse->getKey() == START_KEY ||
        found_horse->getHerd() == nullptr) {
        return StatusType::FAILURE;
    }

    found_herd->removeHorse(horseId);
    found_horse->leave_herd();

    return StatusType::SUCCESS;
}


output_t<int> Plains::get_speed(int horseId) {
    if (horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    //find horse
    //apply get speed
    std::shared_ptr<Horse> found_horse;

    if (horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    return found_horse->getSpeed();
}

output_t<bool> Plains::leads(int horseId, int otherHorseId) {
    //find hourse one, hourse two
    //check if they at the same herd- else return false
    // apply leads at the herd

    std::shared_ptr<Horse> found_horse1;
    std::shared_ptr<Horse> found_horse2;

    if (horseId <= 0 || otherHorseId <= 0 || horseId == otherHorseId) {
        return StatusType::FAILURE;
    }
    if (found_horse1->getHerd() != found_horse2->getHerd()) {
        return false;
    }
    if (found_horse1->getKey() == START_KEY ||
        found_horse2->getKey() == START_KEY) {
        return false;
    }

    Herd *common_herd = found_horse1->getHerd();

    return common_herd->leads(horseId, otherHorseId);
}

output_t<bool> Plains::can_run_together(int herdId) {
    //find herd
    //apply can_run_together at herd

    std::shared_ptr<Herd> found_herd;

    if (herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (found_herd->getSize() < 1) {
        return StatusType::FAILURE;
    }

    return found_herd->can_run_together();
}
