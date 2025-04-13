#include "Utilities.hpp"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

namespace utils
{
    // calcule du SHA1
    std::string sha1(const std::string &contenu)
    {   
        // Trouvé sur le net sur un site bizarre
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char *>(contenu.c_str()),
             contenu.length(),
             hash);
        std::stringstream ss;
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return ss.str();
    }

    // lit le contenu d'un fichier
    std::string readFile(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Erreur lors de l'ouverture du fichier");
        }
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    // Après la lecture l'écriture
    bool writeFile(const std::filesystem::path &path, const std::string &content)
    {
        std::ofstream file(path, std::ios::binary);
        if (!file)
            return false;
        file << content;
        return true;
    }
}