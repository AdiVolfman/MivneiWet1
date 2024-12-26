#include "plains25a1.h"
#include <iostream>
#include <string>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void print(string cmd, output_t<bool> res);

/*
int main()


    /*
    Herd herd1(1);

    // יצירת סוסים
    auto horse1 = std::make_shared<Horse>(1, 100);
    auto horse2 = std::make_shared<Horse>(2, 200);
    auto horse3 = std::make_shared<Horse>(3, 300);

    // הוספת סוסים לעדר
    herd1.addHorse(horse1);
    herd1.addHorse(horse2);
    herd1.addHorse(horse3);

    horse1->follow(horse2);
    horse2->follow(horse3);
    herd1.removeHorse(3);
    herd1.addHorse(horse3);

    if(herd1.can_run_together()) {
        cout<< "run" <<endl;
    }
    if(!herd1.hasCycle()) {
        cout<< " no cycle" <<endl;
    }
    horse1->follow(horse2);
    horse2->follow(horse3);
    horse3->follow(horse1);
    if(herd1.hasCycle()) {
        cout<< "  cycle" <<endl;
    }
    if(herd1.can_run_together()) {
        cout<< "run" <<endl;
    }



    Plains *obj = new Plains();

    print("add_horse 1 100", obj->add_horse(1, 100));
    print("add_horse 2 200", obj->add_horse(2, 200));
    print("add_horse 3 300", obj->add_horse(3, 300));
    print("add_horse 4 400", obj->add_horse(4, 300));

    print("add_herd 1", obj->add_herd(1));

    print("join_herd 1 1", obj->join_herd(1, 1));
    print("join_herd 2 1", obj->join_herd(2, 1));
    print("join_herd 3 1", obj->join_herd(3, 1));

    print("----- ", obj->print_herd(1));

    print("follow 1 2", obj->follow(1, 2));
    print("can_run_together 1", obj->can_run_together(1));

    print("follow 2 3", obj->follow(2, 3));
    print("can_run_together 1", obj->can_run_together(1));

    print("----- ", obj->print_herd(1));

    print("leave_herd 3", obj->leave_herd(3));

    print("-----", obj->print_herd(1));

    print("join_herd 3 1", obj->join_herd(3, 1));

    print("-----  ", obj->print_herd(1));

    print("can_run_together 1", obj->can_run_together(1));


    print("follow 3 1", obj->follow(3, 1));
    print("can_run_together 1", obj->can_run_together(1));

  //  print("follow 2 3", obj->follow(2, 3));
  //  print("can_run_together 1", obj->can_run_together(1));
    print("-----  ", obj->print_herd(1));

    print("leads 1 3", obj->leads(1, 3));
    print("leads 1 4", obj->leads(1, 4));

    print("get_speed 1", obj->get_speed(1));
    print("get_speed 2", obj->get_speed(2));
    print("get_speed 3", obj->get_speed(3));

    delete obj;

    return 0;
}

void print(string cmd, StatusType res) {
    static const char *StatusTypeStr[] = {"SUCCESS", "ALLOCATION_ERROR", "INVALID_INPUT", "FAILURE"};
    cout << cmd << ": " << StatusTypeStr[(int)res] << endl;
}

void print(string cmd, output_t<int> res) {
    static const char *StatusTypeStr[] = {"SUCCESS", "ALLOCATION_ERROR", "INVALID_INPUT", "FAILURE"};
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << endl;
    }
}

void print(string cmd, output_t<bool> res) {
    static const char *StatusTypeStr[] = {"SUCCESS", "ALLOCATION_ERROR", "INVALID_INPUT", "FAILURE"};
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << ", " << (res.ans() ? "True" : "False") << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << endl;
    }
}
*/