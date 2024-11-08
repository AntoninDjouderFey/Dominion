#include <iostream>
#include <vector>
#include "Partie.h"
#include "Joueur.h"
#include "Cartes.hpp"

int main() {
    // Initialiser une partie avec deux joueurs
    std::vector<std::string> nomsJoueurs = {"Nour", "Alex"};
    Partie partie(nomsJoueurs);

    // Démarrer la partie
    partie.demarrer();

     std::cout << "Fin de la partie !" << std::endl;

    return 0;
}
