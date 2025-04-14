#include "index.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

namespace objects
{
    IndexEntry::IndexEntry(const std::string &path, const std::string &hash, uint32_t mode, uint32_t timestamp, uint32_t size)
        : path(path), hash(hash), mode(mode), timestamp(timestamp), size(size) {}

    // Charger 
    bool Index::load(){
        // on lit le fichier .myGit/index
        fs::path indexPath = fs::current_path().parent_path()/ ".myGit/index";
        if (!fs::exists(indexPath))
        {
            std::cerr << "Le fichier d'index n'existe pas" << std::endl;
            return false;
        }

        std::ifstream indexFile(indexPath);
        if (!indexFile.is_open())
        {
            std::cerr << "Erreur lors de l'ouverture du fichier d'index" << std::endl;
            return false;
        }
        entries.clear(); // Pour s'assurer que c'est propre

        std::string line;
        // Le format c'est  path|hash|mode|timestamp|size a voir
        while(std::getline(indexFile, line)){
            std::string path, hash, modeStr, timestampStr, sizeStr;
            // Heureusement que sstream existe
            std::istringstream iss(line);
            std::getline(iss, path, '|');
            std::getline(iss, hash, '|');
            std::getline(iss, modeStr, '|');
            std::getline(iss, timestampStr, '|');
            std::getline(iss, sizeStr, '|');
            
            // Je dois les convertir en uint32_t
            uint32_t mode = std::stoul(modeStr);
            uint32_t timestamp = std::stoul(timestampStr);
            uint32_t size = std::stoul(sizeStr);

            // au lieu du bon vieux push_back emplace_back pas de move 
            entries.emplace_back(path, hash, mode, timestamp, size);
        }
    }
}