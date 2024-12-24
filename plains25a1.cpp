// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"

#include "Horse.h"


Plains::Plains()
{
    
}

Plains::~Plains()
{
    
}

StatusType Plains::add_herd(int herdId)
{
    return StatusType::FAILURE;
}

StatusType Plains::remove_herd(int herdId)
{
    return StatusType::FAILURE;
}

StatusType Plains::add_horse(int horseId, int speed)
{
    return StatusType::FAILURE;
}

StatusType Plains::join_herd(int horseId, int herdId)
{
    //find horse
    //Check if m_key =START
    //If so, the horse is not in any herd
    //find herd- Check if the herd exists?
    //apply add_horse at herd
    //add line: horse->join_herd(this);

    std::shared_ptr<Horse> found_horse ;
    std::shared_ptr<Herd> found_herd ;

    if ( horseId <= 0 || herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (found_horse -> getKey() != START_KEY) {
        return StatusType::FAILURE;
    }

    found_herd->addHorse(found_horse);

    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
    //find 2 horses
    //chack they are at same herd
    //apply follow(horse2) at horse1

    std::shared_ptr<Horse> found_horse1 ;
    std::shared_ptr<Horse> found_horse2 ;

    if ( horseId <= 0 || horseToFollowId <= 0 || horseId == horseToFollowId ) {
        return StatusType::FAILURE;
    }

    if (found_horse1->getHerd() != found_horse2->getHerd()) {
        return StatusType::FAILURE;
    }

    if (found_horse1->getKey() == START_KEY ||  found_horse1->getKey() ==
        START_KEY) {
        return StatusType::FAILURE;
    }

    found_horse1->follow( found_horse2 );

    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId)
{
    //find the horse
    //chack if in any herd
    //apply removeHorse at Herd
    //remove follow from followers- apply leave_herd at Horse
    // update at Horse class

    std::shared_ptr<Horse> found_horse ;

    Herd* found_herd = found_horse->getHerd();

    if ( horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if ( found_horse->getKey() == START_KEY || found_horse->getHerd() == nullptr) {
        return StatusType::FAILURE;
    }

    found_herd->removeHorse(horseId);
    found_horse->leave_herd();

    return StatusType::SUCCESS;
}

output_t<int> Plains::get_speed(int horseId)
{
    //find horse
    //apply get speed

    std::shared_ptr<Horse> found_horse ;

    if ( horseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    return found_horse->getSpeed();
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)
{
    //find hourse one, hourse two
    //check if they at the same herd- else return false
    // apply leads at the herd

    std::shared_ptr<Horse> found_horse1 ;
    std::shared_ptr<Horse> found_horse2 ;

    if ( horseId <= 0 || otherHorseId <= 0 || horseId == otherHorseId ) {
        return StatusType::FAILURE;
    }
    if ( found_horse1->getHerd() != found_horse2->getHerd() ) {
        return false;
    }
    if ( found_horse1->getKey() == START_KEY || found_horse2->getKey() == START_KEY) {
        return false;
    }

    Herd * common_herd = found_horse1->getHerd();

    return common_herd->leads( horseId, otherHorseId );
}

output_t<bool> Plains::can_run_together(int herdId)
{
    //find herd
    //apply can_run_together at herd

    std::shared_ptr<Herd> found_herd ;

    if ( herdId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if ( found_herd->getSize() < 1) {
        return StatusType::FAILURE;
    }

    return found_herd->can_run_together();
}
