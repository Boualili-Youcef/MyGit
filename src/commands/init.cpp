#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "init.hpp"

namespace fs = std::filesystem;

namespace commands
{
    int init()
    {
        fs::path current_path = fs::current_path().parent_path();	 // Dans le repertoire parent
        std::cout << "Current path: " << current_path << std::endl;

        fs::path git_dir = current_path / ".myGit";
        if (fs::exists(git_dir))
        {
            std::cout << "Le depot .myGit existe deja" << std::endl;
            return 1;
        }
        fs::create_directory(git_dir);
        fs::create_directory(git_dir / "objects");

        std::cout << "Depot myGit initialisé avec succès" << std::endl;
        return 25;
    }
}