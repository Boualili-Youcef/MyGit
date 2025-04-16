#include "index.hpp"
#include "Blob.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

namespace objects
{
    IndexEntry::IndexEntry(const std::string &path, const std::string &hash, uint32_t mode, uint32_t timestamp, uint32_t size)
        : path(path), hash(hash), mode(mode), timestamp(timestamp), size(size) {}

    // Charger
    bool Index::load()
    {
        // on lit le fichier .myGit/index
        fs::path indexPath = fs::current_path().parent_path() / ".myGit/index";
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
        while (std::getline(indexFile, line))
        {
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
        indexFile.close();
        return true;
    }

    bool Index::save()
    {
        // Chemin vers le fichier d'index
        fs::path indexPath = fs::current_path().parent_path() / ".myGit/index";

        // Ouvrir le fichier en écriture (écrase le contenu existant)
        std::ofstream indexFile(indexPath);
        if (!indexFile.is_open())
        {
            std::cerr << "Erreur lors de la création du fichier d'index" << std::endl;
            return false;
        }

        // Écrire toutes les entrées dans le fichier
        for (const auto &entry : entries)
        {
            indexFile << entry.getPath() << "|" << entry.getHash() << "|"
                      << entry.getMode() << "|" << entry.getTimestamp() << "|"
                      << entry.getSize() << std::endl;
        }

        indexFile.close();
        return true;
    }

    // Ajouter un fichier à l'index
    bool Index::addFile(const std::string &path)
    {
        // Vérifier que le fichier existe
        if (!fs::exists(path))
        {
            std::cerr << "Le fichier n'existe pas: " << path << std::endl;
            return false;
        }

        // Normaliser le chemin pour l'index

        // Lire le contenu du fichier (utiliser le chemin original)
        std::string content = utils::readFile(path);

        // Créer un blob et le stocker
        Blob blob(content);
        if (!blob.store())
        {
            std::cerr << "Erreur lors de la sauvegarde du blob" << std::endl;
            return false;
        }

        // Les métadonnées (utiliser le chemin original pour accéder au fichier)
        uint32_t fileSize = fs::file_size(path);
        uint32_t mode = 100644; // Mode standard pour un fichier normal
        uint32_t timestamp = static_cast<uint32_t>(fs::last_write_time(path).time_since_epoch().count());
        std::string hash = blob.getHash();

        // Vérifier si le fichier existe déjà dans l'index
        bool found = false;
        std::for_each(entries.begin(), entries.end(), [&path, &hash, &mode, &timestamp, &fileSize, &found](IndexEntry &entry)
                      {
                if (entry.getPath() == path && !found) {
                    // Mettre à jour l'entrée existante
                    entry.setHash(hash);
                    entry.setMode(mode);
                    entry.setTimestamp(timestamp);
                    entry.setSize(fileSize);
                    found = true;
                    std::cout << "Fichier " << path << " mis à jour dans l'index" << std::endl;
                } });

        // Si le fichier n'existe pas, l'ajouter
        if (!found)
        {
            entries.emplace_back(path, hash, mode, timestamp, fileSize);
            std::cout << "Fichier " << path << " ajouté à l'index avec succès" << std::endl;
        }

        return true;
    }
}