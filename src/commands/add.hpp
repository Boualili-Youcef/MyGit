#pragma once
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Pas sur pour la division hpp cpp si c'est necessaire
namespace commands
{
    // Pour ajouter le fichier a l'index
    int add(const std::string& filepath);
}