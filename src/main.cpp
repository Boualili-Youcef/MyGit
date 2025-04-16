#include <iostream>
#include <string>
#include "commands/init.hpp"
#include "commands/HashObject.hpp"
#include "commands/add.hpp"


int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: mygit <command> [options]" << std::endl;
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "init") {
        return commands::init();
    }
    else if (cmd == "hash-object" || cmd == "hash") {
        bool store = false;
        std::string filename;

        // Cas avec -w : ./mygit hash-object -w fichier.txt
        if (argc >= 4 && std::string(argv[2]) == "-w") {
            store = true;
            filename = argv[3];
        }
        // Cas sans -w : ./mygit hash-object fichier.txt
        else if (argc >= 3) {
            filename = argv[2];
        }
        else {
            std::cout << "Usage: mygit hash-object [-w] <file>" << std::endl;
            return 1;
        }

        return commands::hashObject(filename, store);
    }

    if(cmd == "add")
    {
        if (argc < 3) {
            std::cout << "Usage: mygit add <file>" << std::endl;
            return 1;
        }
        std::string filepath = argv[2];
        if(filepath == ".")
        {
            return commands::addAll();
        }
        return commands::add(filepath);
    }
    std::cout << "Commande inconnue: " << cmd << std::endl;
    return 1;
}
