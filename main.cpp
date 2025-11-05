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
    auto abs = ABS<int>();

    abs.push(5);
    std::cout << abs.peek() << std::endl;
    abs.push(10);
    std::cout << abs.peek() << std::endl;
    abs.push(15);
    std::cout << abs.peek() << std::endl;

    const auto size = abs.getSize();
    for (size_t i = 0; i < size; ++i) {
        std::cout << abs.pop() << std::endl;
    }
}

#endif
