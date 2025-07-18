#include "../../../Source/Utils/Include/AssertNullPtr.hpp"

int main() {

    int *myPtr;
    int notPtrValue;
    /*
    * Will failed.
    */
    AssertContext{}.RequireNonNullPtr(myPtr);

    return 0;
}