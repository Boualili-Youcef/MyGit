#pragma once
#include <string>

namespace commands
{
    // De ce que j'ai compris ca calcule et affiche le hash SHA-1 d'un fichier
    // puis on retourne le hash si  le stockage avec succès, sinon vide
    int hashObject(const std::string &filename, bool store = false);
}