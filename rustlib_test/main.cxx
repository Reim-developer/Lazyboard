#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

extern "C" {
    void greet();
    char *get_reim_name();
    void free_name(char *name);
}

int main() {
    greet();

    auto raw_name = get_reim_name();
    auto name_string = string(raw_name);
    free_name(raw_name);

    cout << name_string << endl;
}