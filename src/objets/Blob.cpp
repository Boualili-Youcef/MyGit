#include "Blob.hpp"
#include "Utilities.hpp" // Pour le stockage
#include <iostream>
#include <fstream>    // Pour l'écriture du fichier
#include <filesystem> // Pour le stockage

namespace fs = std::filesystem;

namespace objects
{
    Blob::Blob(const std::string &content) : content(content)
    {
        // de ce que j'ai trouvé le format est "blob <taille>\0<contenu>"
        std::string header = "blob " + std::to_string(content.size()) + "\0";
        hash = utils::sha1(header + content);
    }

    std::string Blob::getHash() const
    {
        return hash;
    }
    std::string Blob::getContent() const
    {
        return content;
    }
    bool Blob::store() const
    {
        fs::path gitDir = fs::current_path().parent_path() / ".myGit";
        // Dans git On découpe le hash SHA-1 en 2 parties pour ce faire il doit surremnt y'avoir un truc dans la STL
        std::string dir = hash.substr(0, 2);
        std::string file = hash.substr(2);

        fs::path objectDir = gitDir / "objects" / dir;
        // si il n'existe pas on le crée
        if (!fs::exists(objectDir))
        {
            fs::create_directories(objectDir);
        }
        // On crée le fichier maintenant
        fs::path objectFile = objectDir / file;
        // On écrit le contenu dans le fichier
        // Si le fichier existe pas on l'écrit
        if (fs::exists(objectFile))
        {
            return true;
        }
        // On écrit le contenu dans le fichier
        std::string fullcontent = "blob " + std::to_string(content.size()) + "\0" + content;
        return utils::writeFile(objectFile, fullcontent);
    }
}
