#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include "Joueur.h"
#include "Cartes.hpp"

class Partie {
public:
    Partie(const std::vector<std::string>& nomsJoueurs);
    void demarrer();
    void jouerTour();
    bool estFinie() const;
    void annoncerVainqueur() const;
    void phaseAction(Joueur& joueur);
    void phaseAchat(Joueur& joueur);
    void phaseAjustement(Joueur& joueur);

private:
    std::vector<Joueur> joueurs;
    std::vector<Cartes> reserve;
    int joueurActuel;

    // Méthodes internes
    void initialiserReserve();
    void afficherEtat() const;

    // Nouvelles méthodes ajoutées
    void calculerOrEnMain(Joueur& joueur);
    void jouerCarteAction(Joueur& joueur);
    void acheterCarte(Joueur& joueur);
};

#endif // PARTIE_H
