// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"


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
    return StatusType::FAILURE;
}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
    return StatusType::FAILURE;
}

StatusType Plains::leave_herd(int horseId)
{
    //find the horse
    //chack if in any herd
    //apply removeHorse at Herd
    //remove follow from followers- apply leave_herd at Horse
    // update at Horse class

    return StatusType::FAILURE;
}

output_t<int> Plains::get_speed(int horseId)
{
    return 0;
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)
{
    //find hourse one, hourse two
    //check if they at the same herd- else return false
    // apply leads at the herd

    return false;
}

output_t<bool> Plains::can_run_together(int herdId)
{
    return false;
}
