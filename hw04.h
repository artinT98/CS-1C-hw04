#ifndef HW04
#define HW04
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <sstream>

/*Static Counters;*/
static int allocs = 0;
static int deallocs = 0;

/*Function Prototypes*/
//Helper functions
char* str2dup(const char* str1, const char* str2);
void strrev(char* dest, const char* src);
//Test Functions
void TestConstructorAndDeconstructor();
void TestLengthFunction();
void TestOperators();
void TestCopyAndMoveConstructor();
void TestGetIndexCharAndString();
void TestReverse();
void TestReadAndPrintFunctions();
void TestNonMemberOperators();

class StringType {
    private:
        char *buffer; // string pointer
        size_t capacity; // string length

    public:

        /* ProtoTypes
        // Default/Overloaded Constructor
        StringType(const char *s="");

        // Copy Constructor
        StringType (const StringType& s);

        // Move Constructor 
        StringType(StringType&& s) noexcept;

        // Overloading Operator=
        StringType& operator=(const StringType& s);

        // Move Assignment Overloading Operator=
        StringType& operator=(StringType &&s) noexcept;

        // Overloading Operator[]
        char& operator[](const int index);

        // GetLength
        int length() const;

        // GetIndex char
        int indexOf(char c) const;

        // GetIndex string
        int indexOf(const StringType& pat) const;

        // Overloading Operator==
        bool operator==(const StringType& s) const;

        // Overloading Operator+
        StringType operator+(const StringType& s) const;

        // Overloading Operater+=
        StringType& operator+=(const StringType& s);

        // Reverse
        StringType reverse() const;

        // Print
        void print(std::ostream& out) const;

        // Read
        void read(std::istream& in);

        // Deconstructor
        ~StringType();
        End Prototypes*/
            
        // Default/Overloaded Constructor
        // Description: Passes in a string for initialization, default included as "" ('\0') empty string
        /*StringType::*/StringType(const char *s="") {
            allocs++;
            buffer = strdup(s);        // strdup() dups string object, returns pointer to obj
            capacity = strlen(s);      // strlen() returns len bfr '\0'
        }

        // Copy Constructor
        // Descripion: Passes a constant reference (original object cannot be mutated) to be copied into new obj
        /*StringType::*/StringType (const StringType& s) {
            buffer = strdup(s.buffer);  //Copy buffer
            capacity = s.capacity;      //Copy capacity
        }

        // Move Constructor
        // Description: Uses no exception to not throw exceptions, member list initalizer to initialize members
        // before body of constructor is executed. Transfers ownershp of resources (&& is ref. to rvalue).
        /*StringType::*/StringType(StringType&& s) noexcept : buffer(s.buffer), capacity(s.capacity) {
            //Set source to NULL
            s.buffer = nullptr;
            s.capacity = 0;
        }

        // Overloading Operator=
        // Description: checks for self assignment, prevents memory leak, copies assignment object(r) into target object(l)
        StringType& /*StringType::*/operator=(const StringType &s) {
            if (this != &s) { //self assignment check
                delete[] buffer; //free memory from prev. strdup() (prevent memory leaks)

                //copy to target object (left hand) from assignment (right hand)
                buffer = strdup(s.buffer);
                capacity = s.capacity;
            }

            return *this; //return StringType object (return type is object reference)
        }

        // Move Assignment Overloading Operator=
        // Descrption: checks for self assignment, prevents leaks, copies assignment to targer then delets assignment object
        StringType& /*StringType::*/operator=(StringType&& s) noexcept {
            if (this != &s) { // Check for self-assignment
                delete[] buffer; // Free existing memory

                // copy to target object (left hand) from assignment (right hand)
                buffer = s.buffer;
                capacity = s.capacity;

                // clear assignment object
                s.buffer = nullptr;
                s.capacity = 0;
            }
            return *this; //return StringType object (return type is object reference)
        }

        // Overloading Operator[]
        // Description: checks bounds, returns desired element
        char& /*StringType::*/operator[](const int index) {
                //check bounds
                if (index < 0 || static_cast<size_t>(index) >= capacity) {
                    throw std::out_of_range("Index out of bounds");
                }

                return buffer[index];
        }

        // GetLength
        // Description: returns length. example: String a = "hi"; int b = a.length() [which == 2] 
        int /*StringType::*/length() const {
            return capacity;
        }

        // GetIndex
        // Description: returns the index of the the first element containing the desired char
        int /*StringType::*/indexOf(char c) const {
            for (size_t i = 0; i < capacity; i++) {
                if(buffer[i] == c) {
                    return static_cast<int>(i); //Return Index
                }
            }

            return -1; //String not found
        }

        // GetIndex
        // Description: returns the index of the the first element containing the desired string
        int /*StringType::*/indexOf(const StringType& pat) const {
            //Error check
            if (pat.capacity == 0 || pat.capacity > this->capacity) {
                return -1; 
            }

            //use strstr(main string, substring).
            const char* result = strstr(this->buffer, pat.buffer); //returns pointer to first character of substring if found, else null
            if (result) {
                return static_cast<int>(result - this->buffer); //Return Index:difference in mem. due to contigual storage C++
            }

            return -1; //String not found
        }

        // Overloading Operator==
        // Description: returns a boolean using strcmp() to compare if 2 strings equal each other
        bool /*StringType::*/operator==(const StringType& s) const {
            //Pre length check
            if(this->capacity != s.capacity) {
                return false;
            }

            //strcmp() comparison (true if ==0)
            return strcmp(this->buffer, s.buffer) == 0;
        }

        // Overloading Operator+
        // Description: uses str2dup() to concatonate 2 strings using '+' operator
        StringType /*StringType::*/operator+(const StringType &s) const {
            // make new buffer, str2dup() defined at top of file
            char* newBuffer = str2dup(this->buffer, s.buffer);
            
            //create new StringType with result
            StringType result(newBuffer);

            //cleanup buffer
            delete[] newBuffer;

            return result;
        }

        // Overloading Operator+=
        // Description: uses str2dup() to concatonate 2 strings and store using '+=' operator
        StringType& /*StringType::*/operator+=(const StringType& s) {
            // make new buffer
            char* newBuffer = str2dup(this->buffer, s.buffer);

            // free  existing buffer
            delete[] buffer;

            // update current buffer & capacity
            buffer = newBuffer;
            capacity = strlen(newBuffer);

            return *this;
        }

        // Reverse()
        // Description: returns another StringType that is the reverse of current StringType
        StringType /*StringType::*/reverse() const {
            //new buffer
            char* newBuffer = new char[capacity + 1]; //+1 for '\0'

            strrev(newBuffer, buffer); //reverse buffer, store in newBuffer
            StringType revStr(newBuffer); //create new string
            delete[] newBuffer; //free buffer

            return revStr;
        }

        // Print()
        // Description: prints string to ostream
        void /*StringType::*/print(std::ostream& out) const {
            out << buffer;
        }

        // Read()
        // Description: reads a word in from istream 
        void /*StringType::*/read(std::istream& in) {
            char temp[1024]; // temp buffer
            in.getline(temp, sizeof(temp), ' '); // Read a word from the input stream

            // Allocate a new buffer with the size of the word plus null terminator
            delete[] buffer; // Free existing buffer
            capacity = strlen(temp);
            buffer = new char[capacity + 1]; // +1 for null terminator

            // Copy the word into the buffer
            strcpy(buffer, temp);
        }

        // Deconstructor
        // Description: frees the allocated mem.
        /*StringType::*/~StringType() {
            deallocs++;
            delete[] buffer; // Free the dynamically allocated memory
        }
};

// Overloading Operator<< 
inline std::ostream& operator<<(std::ostream& out, const StringType& str) {
    str.print(out);
    return out;
}

// Overloading Operator>>
inline std::istream& operator>>(std::istream& in, StringType& str) {
    str.read(in);
    return in;
}

#endif