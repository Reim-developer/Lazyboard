#include <iostream>

using std::cout;

extern "C" {
    bool is_valid_path(char *path);
}

int main() {
    char path[] = "./src/lib.rs";
    
    auto result =  is_valid_path(path) ? "Valid path" : "Not valid path";

    cout << result << "\n";

    return 0;
}