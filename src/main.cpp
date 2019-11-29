// STL
#include <iostream>
#include <cstdio>

// LibLo (OSC)
#include <lo/lo.h>
#include <lo/lo_cpp.h>

// TCLAP (command processing)
#include <tclap/ValueArg.h>
#include <tclap/CmdLine.h>

// Unrelated me testing things
#include <sol/sol.hpp>

int main(int argc, const char** argv) {
    TCLAP::CmdLine cmd("echo OSC messages");
    TCLAP::ValueArg<int> port_arg("p", "port", "port to listen on", false, 8000, "int", cmd);

    try {
        cmd.parse(argc, argv);
    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        return 1;
    }

    int port = port_arg.getValue();
    lo::ServerThread server(port);

    server.add_method(nullptr, "f", [](const char* path, const char* type, lo_arg** argv, int argc) {
        if (argc <= 0) {
            return;
        }

        lo_arg* arg = argv[0];
        std::cout << path << " (" << type << ") " << arg->f << std::endl;
    });

    std::cout << "Listening on UDP port " << port << std::endl;
    server.start();

    // Proceed to exit when the user hits enter.
    std::cout << "Press enter key to exit" << std::endl;
    getchar();

    return 0;
}
