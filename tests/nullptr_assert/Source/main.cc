#include "../../../Source/Utils/Include/AssertNullPtr.hpp"
#include <stdio.h>

class myObject {
    public:
        int myField;
};

int main() {
    myObject *my = new myObject();
    delete my;
    my = nullptr;

    int *myPtr = nullptr;
    int notPtrValue;
    /*
    * Will failed.
    */
    AssertContext{}.RequireNonNullPtr(my);
    printf("%d", my->myField);

    return 0;
}