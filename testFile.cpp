#include <iostream>
#include "plains25a1.h"

void runTests() {


    Plains plains;

    // Test 1: Add Herd
    std::cout << "Test 1: Add Herd" << std::endl;
    std::cout
            << (plains.add_herd(1) == StatusType::SUCCESS ? "Passed" : "Failed")
            << std::endl;

    // Test 2: Add Duplicate Herd
    std::cout << "Test 2: Add Duplicate Herd" << std::endl;
    std::cout
            << (plains.add_herd(1) == StatusType::FAILURE ? "Passed" : "Failed")
            << std::endl;

    // Test 3: Remove Herd
    std::cout << "Test 3: Remove Herd" << std::endl;
    std::cout << (plains.remove_herd(1) == StatusType::SUCCESS ? "Passed"
                                                               : "Failed")
              << std::endl;

    // Test 4: Remove Non-Existent Herd
    std::cout << "Test 4: Remove Non-Existent Herd" << std::endl;
    std::cout << (plains.remove_herd(2) == StatusType::FAILURE ? "Passed"
                                                               : "Failed")
              << std::endl;

    // Test 5: Add Horse
    std::cout << "Test 5: Add Horse" << std::endl;
    std::cout << (plains.add_horse(1, 10) == StatusType::SUCCESS ? "Passed"
                                                                 : "Failed")
              << std::endl;

    // Test 6: Add Duplicate Horse
    std::cout << "Test 6: Add Duplicate Horse" << std::endl;
    std::cout << (plains.add_horse(1, 10) == StatusType::FAILURE ? "Passed"
                                                                 : "Failed")
              << std::endl;

    // Test 7: Join Herd
    plains.add_herd(2);
    std::cout << "Test 7: Join Herd" << std::endl;
    std::cout << (plains.join_herd(1, 2) == StatusType::SUCCESS ? "Passed"
                                                                : "Failed")
              << std::endl;

    // Test 8: Leave Herd
    std::cout << "Test 8: Leave Herd" << std::endl;
    std::cout << (plains.leave_herd(1) == StatusType::SUCCESS ? "Passed"
                                                              : "Failed")
              << std::endl;

    // Test 9: Get Speed
    std::cout << "Test 9: Get Speed" << std::endl;
    auto speed = plains.get_speed(1);
    std::cout << (speed.status() == StatusType::SUCCESS && speed.ans() == 10
                  ? "Passed" : "Failed") << std::endl;

    // Test 10: Leads
    plains.add_herd(3);
    plains.add_horse(2, 15);
    plains.add_horse(4, 15);
    plains.add_horse(3, 15);
    plains.join_herd(2, 3);
    plains.join_herd(3, 3);
    plains.join_herd(4, 3);
    plains.follow(2, 3);
    plains.follow(3, 4);
    std::cout << "Test 10: Leads" << std::endl;
    auto leads = plains.leads(2, 4);
    std::cout
            << (leads.status() == StatusType::SUCCESS && leads.ans() ? "Passed"
                                                                     : "Failed")
            << std::endl;

    // Test 11: Can Run Together
    std::cout << "Test 11: Can Run Together" << std::endl;
    auto canRun = plains.can_run_together(3);
    std::cout << (canRun.status() == StatusType::SUCCESS && canRun.ans()
                  ? "Passed" : "Failed") << std::endl;
}

int main() {
    runTests();
    /*
    Plains plains;


    // הוספת עדר
    StatusType status = plains.add_herd(1);
    if (status == StatusType::SUCCESS) {
        std::cout << "Herd 1 added successfully!" << std::endl;
    } else {
        std::cout << "Failed to add Herd 1." << std::endl;
    }

    // הוספת סוס
    status = plains.add_horse(1, 50);  // סוס עם מזהה 101 ומהירות 50
    if (status == StatusType::SUCCESS) {
        std::cout << "Horse 101 added successfully!" << std::endl;
    } else {
        std::cout << "Failed to add Horse 101." << std::endl;
    }
    // הוספת סוס
    status = plains.add_horse(2, 50);  // סוס עם מזהה 101 ומהירות 50


    // הוספת סוס
    status = plains.add_horse(3, 50);  // סוס עם מזהה 101 ומהירות 50


    // חיבור סוס לעדר
    status = plains.join_herd(1, 1);  // סוס 101 יתחבר לעדר 1
    if (status == StatusType::SUCCESS) {
        std::cout << "Horse 101 joined Herd 1!" << std::endl;
    } else {
        std::cout << "Failed to join Herd 1." << std::endl;
    }
    status = plains.join_herd(2, 1);  // סוס 101 יתחבר לעדר 1
    if (status == StatusType::SUCCESS) {
        std::cout << "Horse 101 joined Herd 1!" << std::endl;
    } else {
        std::cout << "Failed to join Herd 1." << std::endl;
    }
    status = plains.join_herd(3, 1);  // סוס 101 יתחבר לעדר 1
    if (status == StatusType::SUCCESS) {
        std::cout << "Horse 101 joined Herd 1!" << std::endl;
    } else {
        std::cout << "Failed to join Herd 1." << std::endl;
    }

    plains.follow(1,2);
    plains.follow(2,3);


    auto leads = plains.leads(1, 3);
    std::cout
            << (leads.status() == StatusType::SUCCESS && leads.ans() ? "Passed"
                                                                     : "Failed")
            << std::endl;

*/
    return 0;
}
