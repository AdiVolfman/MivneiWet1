// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"


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
    if (herdTree->find(herdId)) {
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

StatusType Plains::join_herd(int horseId, int herdId) {//couldnt implement due to lack of herd key in horse
    if (horseId <= 0 || herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Herd> herdFound = herdTree->find(herdId);
    std::shared_ptr<Horse> horseFound = horseTree->find(horseId)

    //find horse
    //Check if m_key =START
    //If so, the horse is not in any herd
    //find herd- Check if the herd exists?
    //apply add_horse at herd
    //add line: horse->join_herd(this);

    return StatusType::FAILURE;
}

StatusType Plains::follow(int horseId, int horseToFollowId) {
    //find 2 horses
    //chack they are at same herd
    //apply follow(horse2) at horse1

    return StatusType::FAILURE;
}

StatusType Plains::leave_herd(int horseId) {
    //find the horse
    //chack if in any herd
    //apply removeHorse at Herd
    //remove follow from followers- apply leave_herd at Horse
    // update at Horse class

    return StatusType::FAILURE;
}

output_t<int> Plains::get_speed(int horseId) {
    //apply get speed

    return 0;
}

output_t<bool> Plains::leads(int horseId, int otherHorseId) {
    //find hourse one, hourse two
    //check if they at the same herd- else return false
    // apply leads at the herd

    return false;
}

output_t<bool> Plains::can_run_together(int herdId) {
    //find herd
    //apply can_run_together at herd

    return false;
}
