#include <sodium/core.h>
#include "lib/include/encrypt.h"
#include <cassert>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int main() {
    const int INIT_RESULT = sodium_init();

    if (INIT_RESULT != 0) {
        cerr << "Could not init sodium";
        return 1;
    }

    const char *myPassword = "mySecretPassword";
    char hashed[256];

    const int HASH_STATUS = hash_password(myPassword, hashed);

    if (HASH_STATUS == MEMORY_ERROR) {
        cerr << "Memory error when hash passsword" << endl;
        return 1;
    }

    cout << "Hashed password: " << hashed << endl;

    const char *wrongPassword = "MyWrongPassword";
    assert(is_hash_matches(hashed, myPassword) == HASH_MATCHES);
    /*
    * Always failed, in case wrong password
    */
    assert(is_hash_matches(hashed, wrongPassword) == HASH_MATCHES);

    return 0;
}