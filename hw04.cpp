#include "hw04.h"

int main() {
    try {
        TestConstructorAndDeconstructor();
        TestLengthFunction();
        TestOperators();
        TestCopyAndMoveConstructor();
        TestGetIndexCharAndString();
        TestReverse();
        TestReadAndPrintFunctions();
        TestNonMemberOperators();
    }
    catch (int e) {
        std::cout << "Caught exception: " << e << std::endl; //Output exception
    }

    std::cout << "\nNo exceptions found, Goodbye!\n";
    return 0;
}
