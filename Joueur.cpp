#include "Joueur.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>

Joueur::Joueur(const std::string& nom)
    : nom(nom), pointsVictoire(0), nombreActions(1), nombreAchats(1), argent(0) {
    for (int i = 0; i < 7; ++i) deck.push_back(Cartes("Cuivre"));
    for (int i = 0; i < 3; ++i) deck.push_back(Cartes("Domaine"));
    melangerDeck();
}

const std::vector<Cartes>& Joueur::getMain() const {
    return main;
}

void Joueur::setMain(const std::vector<Cartes>& mano) {
    main = mano;
}

int Joueur::getArgent() const {
    return argent;
}

void Joueur::setArgent(int n_argent) {
    argent = n_argent;
}

void Joueur::setDeck(const std::vector<Cartes>& nouveauDeck) {
    deck = nouveauDeck;
}

void Joueur::setNombreActions(int nbactions) {
    nombreActions = nbactions;
}

void Joueur::piocher(int nombre) {
    for (int i = 0; i < nombre; ++i) {
        if (deck.empty()) {
            deck = defausse;
            defausse.clear();
            melangerDeck();
        }
        main.push_back(deck.back());
        deck.pop_back();
    }
}
void Joueur::piocherMalediction() {
    // Crée une carte "Malédiction" si elle est disponible
    Cartes malediction("Malediction");
    if (malediction.getType() == "Victoire" && malediction.getNom() == "Malediction") {
        defausse.push_back(malediction);  // Ajoute la carte à la défausse du joueur
        std::cout << getNom() << " reçoit une carte Malédiction, ce qui réduit ses points de victoire.\n";
    } else {
        std::cout << "Erreur : Impossible de trouver une carte Malédiction.\n";
    }
}

int Joueur::getNombreAchats() const {
    return nombreAchats;
}

int Joueur::getNombreActions() const {
    return nombreActions;
}

void Joueur::ajouterArgent(int montant) {
    argent += montant;
}

int Joueur::calculerPointsVictoire() const {
    int points = 0;
    for (const auto& carte : deck) {
        if (carte.getType() == "Victoire") {
            if (carte.getNom() == "Domaine") points += 1;
            else if (carte.getNom() == "Duché") points += 3;
            else if (carte.getNom() == "Province") points += 6;
            else if (carte.getNom() == "Malédiction") points -= 1;
        }
    }
    return points;
}

void Joueur::jouerAction(int indiceCarte) {
    if (indiceCarte < main.size() && main[indiceCarte].getType() == "Royaume" && nombreActions > 0) {
        nombreActions--;
        defausse.push_back(main[indiceCarte]);
        main.erase(main.begin() + indiceCarte);
    }
}

void Joueur::acheterCarte(Cartes& carte) {
    if (argent >= carte.getCout() && nombreAchats > 0) {
        nombreAchats--;
        argent -= carte.getCout();
        defausse.push_back(carte);
        carte.setStock(carte.getStock() - 1);
    }
}

void Joueur::finDuTour() {
    defausse.insert(defausse.end(), main.begin(), main.end());
    main.clear();
    piocher(5);
    nombreActions = 1;
    nombreAchats = 1;
    argent = 0;
}

const std::vector<Cartes>& Joueur::getDeck() const { return deck; }
const std::string& Joueur::getNom() const { return nom; }
int Joueur::getPointsVictoire() const { return pointsVictoire; }
std::vector<Cartes>& Joueur::getDefausse() {
    return defausse;
}
void Joueur::melangerDeck() {
    std::mt19937 g(static_cast<unsigned int>(std::time(0)));
    std::shuffle(deck.begin(), deck.end(), g);
}
