#pragma once
#include <string>
#include <filesystem>
#include <vector>

namespace objects
{
    // Représente un fichier suivi par le systeme
    class IndexEntry
    {
    private:
        // je vais utiliser des uint32_t car de ce que j'ai vu c'est plus sûre et portable
        // ici on a besoin du chemin, hash, mode, Timestamp de modif, et la taille
        std::string path; // chemin du fichier
        std::string hash; // hash du fichier
        uint32_t mode;
        uint32_t timestamp;
        uint32_t size;

        // getters
    public:
        std::string getPath() const { return path; }
        std::string getHash() const { return hash; }
        uint32_t getMode() const { return mode; }
        uint32_t getTimestamp() const { return timestamp; }
        uint32_t getSize() const { return size; }

        // setters
        void setHash(const std::string &h) { hash = h; }
        void setMode(uint32_t m) { mode = m; }
        void setTimestamp(uint32_t t) { timestamp = t; }
        void setSize(uint32_t s) { size = s; }

        IndexEntry(const std::string &path, const std::string &hash, uint32_t mode, uint32_t timestamp, uint32_t size);
    };

    // Ici c'est pour contenir tous les fichiers suivis par le systeme
    /* TODO:
        - charger l'index depuis le fichier .mygit/index
        - le sauvgarder dans le fichier .mygit/index
        - ajouter un nouveau fichier à l'index
    On va essayer deja de faire ca
    */
    class Index
    {
    public:
        // Charger:
        bool load();
        // Sauvegarder:
        bool save();
        // Ajouter un fichier à l'index
        bool addFile(const std::string &path);

    private:
        std::vector<IndexEntry> entries;
    };

}