#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace utils
{
    // calcule du SHA1
    std::string sha1(const std::string &contenu);

    // lit le contenu d'un fichier
    std::string readFile(const std::string &filename);

    // Après la lecture l'écriture
    bool writeFile(const std::filesystem::path &path, const std::string &content);
}