#ifdef MAIN
#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>
/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.
*/
int main() {
    auto abs = ABS<int>();
    auto abq = ABQ<int>();
    auto lls = LLS<int>();
    auto llq = LLQ<int>();
    auto abdq = ABDQ<int>();
    auto lldq = LLDQ<int>();

    abdq.pushBack(1);
    abdq.pushBack(2);
    abdq.pushFront(3);

    auto copy = abdq;

    std::cout << "Back: " << copy.front() << std::endl;
    std::cout << copy.getMaxCapacity() << std::endl;

    std::cout << copy.popBack() << std::endl;
    std::cout << copy.popBack() << std::endl;
    std::cout << copy.popBack() << std::endl;
    return 0;
}
#endif
