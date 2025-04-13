#include "HashObject.hpp"
#include "../objets/Blob.hpp"
#include "../objets/Utilities.hpp"
#include <iostream>
#include <fstream>

namespace commands
{
    int hashObject(const std::string& filename, bool store)
    {
        // Révision des exceptions
        try {
            // Lire le contenu du fichier
            std::string content = utils::readFile(filename);
            
            // Créer un objet Blob
            objects::Blob blob(content);
            
            // Stocker l'objet si true pour la suite la je veux juste tester 
            if (store) {
                if (!blob.store()) {
                    std::cerr << "Erreur lors du stockage de l'objet" << std::endl;
                    return 1;
                }
            }
            
            // Afficher le hash
            std::cout << blob.getHash() << std::endl;
            return 0;
        }
        catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << std::endl;
            return 1;
        }
    }
}