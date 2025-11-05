#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include "LinkedList.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    auto lldq = LLDQ<int>();

    lldq.pushBack(1);
    lldq.pushBack(2);
    lldq.pushBack(3);
    lldq.pushBack(4);
    lldq.pushBack(5);
    lldq.pushBack(6);

    const auto size = lldq.getSize();

    for (size_t i = 0; i < size; ++i) {
        if (i < 3) {
            std::cout << lldq.popBack() << std::endl;
        }
        else {
            std::cout << lldq.popFront() << std::endl;
        }
    }
}

#endif
