#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

// Pas sur pour la division hpp cpp si c'est necessaire
namespace commands
{
    // Pour ajouter le fichier a l'index
    int add(const std::string& filepath);

    // Pour l'ajout de tous les fichiers
    int addAll(const std::string& dirPath = ".");
}