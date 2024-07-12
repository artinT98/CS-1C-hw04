#include "hw04.h"

// Str2dup()
// Description: Duplicates the combo of 2 strings
char* str2dup(const char* str1, const char* str2) {
    //new buffer
    size_t newSize = strlen(str1) + strlen(str2) + 1; // +1 for the null terminator

    // Allocate the new buffer
    char* newBuffer = new char[newSize];

    // Copy the contents of the first string
    strcpy(newBuffer, str1);

    // Concatenate the contents of the second string
    strcat(newBuffer, str2);

    return newBuffer;
}

// strrev()
// Description: copies the reverse of src into dest
void strrev(char* dest, const char* src) {
    size_t len = strlen(src);
    for (size_t i = 0; i < len; ++i) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0'; // null-terminate string
}

void TestConstructorAndDeconstructor() {
    allocs = 0;
    deallocs = 0;
    //This is the first StringType being created, allocs starts @ 0 and ++ at each construction
    {
        StringType string;
    }
    if(allocs == 0  ) { throw 1; }
    std::cout << "TestConstructor passed." << std::endl;
    if(deallocs == 0) { throw 2; }

    //If no error:
    std::cout << "TestDeconstructor passed." << std::endl;

}

void TestLengthFunction() {
    // test string empty length
    {
        StringType str;
        if (str.length() != 0) {
            throw 3; // Fail if length is not zero for empty string
        }
    }

    // test non-empty string length
    {
        StringType str("hello");
        if (str.length() != 5) {
            throw 4; // Fail if length is not correct for non-empty string
        }
    }

    // If no exception was thrown, print success message
    std::cout << "TestLengthFunction passed." << std::endl;
}

void TestOperators() {
    //Equality operator ==
    {
        StringType str1("test");
        StringType str2("test");
        if (!(str1 == str2)) {
            throw 5; // throw if equality fail
        }
    }
    std::cout << "Test Equality operator(==) passed." << std::endl;

    //Assignment operator =
    {
        StringType str1("hello");
        StringType str2 = str1;
        if (!(str1 == str2)) {
            throw 6; // Fail if assignment operator doesn't work
        }
    }
    std::cout << "Test Assignment operator(=) passed." << std::endl;

    //Test Move assignment =std::move
    {
        StringType str1("world");
        StringType str2 = std::move(str1);
        if (!(str2 == "world")) {
            throw 7; // if move assignment fails
        }

        if (str1.length() != 0) {
            throw 8; // fail if original string non-empty
        }
    }
    std::cout << "Test Move Assignment operator(=std::move) passed." << std::endl;

    //Test concatonation operator +
    {
        StringType str1("concat");
        StringType str2("enation");
        StringType str3 = str1 + str2;
        if (!(str3 == "concatenation")) {
            throw 9; // if concatenation fails
        }
    }
    std::cout << "Test Concatonation operator(+) passed." << std::endl;

    //Test concatonation and equals operator +=
    {
        StringType str1("append");
        StringType str2("age");
        str1 += str2;
        if (!(str1 == "appendage")) {
            throw 10; // if concatenation and equals fails
        }
    }
    std::cout << "Test Concatonation and Equals operator(+=) passed." << std::endl;

    //Test indexing operator[]
     {
        StringType str1("index");
        if (str1[0] != 'i' || str1[1] != 'n' || str1[2] != 'd' || str1[3] != 'e' || str1[4] != 'x') {
            throw 11; // if full indexing fails
        }
    }
    std::cout << "Test Indexing operator([]) passed." << std::endl;
}

void TestCopyAndMoveConstructor() {
    // Test copy constructor
    {
        StringType str1("copy");
        StringType str2(str1); // copy constructor

        if (!(str1 == str2)) {
            throw 12; // if str2 != str1 fail
        }
    }
    std::cout << "TestCopyConstructor passed." << std::endl;

     // Test move constructor
    {
        StringType str1("move");
        StringType str2(std::move(str1)); //  move constructor

        if (!(str2 == "move")) {
            throw 13; // if str2 != "move" fail
        }
        if (str1.length() != 0) {
            throw 14; // fail if original string non-empty
        }
    }
    std::cout << "TestMoveConstructor passed." << std::endl;
}

void TestGetIndexCharAndString() {
    // Test GetIndex(char)
    {
        StringType str("hello");
        if (str.indexOf('e') != 1) {
            throw 15; // fail if index(e)!=1
        }
        if (str.indexOf('l') != 2) {
            throw 16; // fail if index(l)!=2
        }
        if (str.indexOf('z') != -1) {
            throw 17; // fail if index(z)!=-1 (not found)
        }
    }
    std::cout << "TestGetIndexChar passed." << std::endl;

    // Test GetIndex(StringType)
    {
        StringType str("hello world");
        StringType substr("world");
        if (str.indexOf(substr) != 6) {
            throw 18; // fail if indexOf("world") != 6
        }
        StringType substr2("lo");
        if (str.indexOf(substr2) != 3) {
            throw 19; // fail if indexOf("lo") != 3
        }
        StringType substr3("notfound");
        if (str.indexOf(substr3) != -1) {
            throw 20; // fail if indexOf("notfound") != -1 (not found)
        }
    }
    std::cout << "TestGetIndexString passed." << std::endl;
}

void TestReverse() {
    // Test reverse on a multi-character string
    {
        StringType str("hello");
        StringType reversed = str.reverse();
        if (!(reversed == "olleh")) {
            throw 21; // fail if reverse "hello" != "olleh"
        }
    }

    // Test reverse on a string with spaces
    {
        StringType str("hello world");
        StringType reversed = str.reverse();
        if (!(reversed == "dlrow olleh")) {
            throw 22; // fail if reverse "hello world" != "dlrow olleh"
        }
    }
    std::cout << "TestReverseFunction passed." << std::endl;
}

void TestReadAndPrintFunctions() {
    // Test read and print on a string
    {
        std::istringstream input("hello world");
        StringType str;
        str.read(input);

        std::ostringstream output;
        str.print(output);

        if (!(output.str() == "hello")) { // 'read' should only read "hello"
            throw 23; // if read or print fails
        }
    }
    std::cout << "TestReadAndPrintFunctions passed." << std::endl;
}

void TestNonMemberOperators() {
    // Test operator>>
    {
        std::istringstream input("hello world");
        StringType str;
        input >> str; // overloaded >> operator

        if (!(str == "hello")) { // hould only read "hello"
            throw 24; // if >> operator fails
        }
    }
    std::cout << "Test Non-Member Extraction Operator(>>) passed." << std::endl;

    // Test operator<<
    {
        StringType str("hello");
        std::ostringstream output;
        output << str; // overloaded << operator

        if (output.str() != "hello") {
            throw 25; // if << operator fails
        }
    }
    std::cout << "Test Non-Member Insertion operator(<<) passed." << std::endl;
}
