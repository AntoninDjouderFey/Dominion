#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <string>
#include "Cartes.hpp"

class Joueur {
private:
    std::string nom;
    int pointsVictoire;
    int nombreActions;
    int nombreAchats;
    int argent;
    std::vector<Cartes> deck;
    std::vector<Cartes> main; // Ajoute l'attribut main
    std::vector<Cartes> defausse;

public:
    // Constructeur
    Joueur(const std::string& nom);
    // Getters et setters
    const std::vector<Cartes>& getMain() const; // Retourne la main du joueur
    void setMain(const std::vector<Cartes>& mano);
    int getArgent() const;
    void setArgent(int n_argent);

    // Autres méthodes
    void setDeck(const std::vector<Cartes>& nouveauDeck);
    void setNombreActions(int nbactions);
    void piocher(int nombre = 1);
    void piocherMalediction();
    int getNombreAchats() const;
    int getNombreActions() const;
    void ajouterArgent(int montant);
    int calculerPointsVictoire() const;
    void jouerAction(int indiceCarte);
    void acheterCarte(Cartes& carte);
    void finDuTour();
    const std::vector<Cartes>& getDeck() const;
    const std::string& getNom() const;
    void setPointsVictoire(int );
    int getPointsVictoire() const;
    void melangerDeck();
    std::vector<Cartes>& getDefausse();       
};

#endif // JOUEUR_H
