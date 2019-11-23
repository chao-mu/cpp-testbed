// STL
#include <iostream>
#include <cstdio>

// LibLo (OSC)
#include <lo/lo.h>
#include <lo/lo_cpp.h>

// Unrelated me testing things
#include <sol/sol.hpp>

#define PORT 8000

int main(int /* argc */, const char** /* argv */) {
    lo::ServerThread server(PORT);

    server.add_method(nullptr, "f", [](const char* path, const char* type, lo_arg** argv, int argc) {
        if (argc <= 0) {
            return;
        }

        lo_arg* arg = argv[0];
        std::cout << path << " (" << type << ") " << arg->f << std::endl;
    });

    std::cout << "Listening on UDP port " << PORT << std::endl;
    server.start();

    // Proceed to exit when the user hits enter.
    std::cout << "Press enter key to exit" << std::endl;
    getchar();

    return 0;
}
