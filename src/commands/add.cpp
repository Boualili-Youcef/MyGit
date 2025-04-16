#include "add.hpp"
#include "../objets/index.hpp"
#include "../objets/Utilities.hpp"

namespace commands
{
    int add(const std::string &filepath)
    {
        // Vérifier que le fichier existe
        if (!fs::exists(filepath))
        {
            std::cerr << "Erreur: " << filepath << " n'existe pas" << std::endl;
            return 1;
        }

        // Créer et charger l'index
        objects::Index index;

        index.load();

        // Ajouter le fichier à l'index
        if (!index.addFile(filepath))
        {
            std::cerr << "Erreur lors de l'ajout du fichier à l'index" << std::endl;
            return 1;
        }

        // Sauvegarder l'index
        if (!index.save())
        {
            std::cerr << "Erreur lors de la sauvegarde de l'index" << std::endl;
            return 1;
        }

        return 0;
    }
}