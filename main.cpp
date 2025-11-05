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
    auto abq = ABQ<int>();

    abq.enqueue(1);
    abq.enqueue(2);
    abq.enqueue(3);
    abq.enqueue(4);

    std::cout << abq.getSize() << std::endl;

    const auto size = abq.getSize();
    for (size_t i = 0; i < size; ++i) {
        std::cout << abq.dequeue() << ", " << abq.getSize() << "remaining" << std::endl;
    }
}

#endif
