#include "Royaume.hpp"
#include "Joueur.h"
#include "Partie.h"
#include <iostream>

// Constructeur
Royaume::Royaume(const Cartes& carte) {
    if (carte.getType() != "Royaume") {
        std::cout << "Erreur : type de carte incorrect, attendue 'Royaume'.\n";
    } else {
        this->carteDeBase = carte;
        this->nom = carte.getNom();
    }
}

// Destructeur
Royaume::~Royaume() {
    std::cout << "Destruction de la carte Royaume " << this->nom << "\n";
}

// Atelier
void Royaume::Atelier(Joueur& joueur) {
    if (carteDeBase.getNom() == "Atelier") {
        std::cout << "Quelle carte souhaitez-vous ajouter à votre deck (coût <= 4) ? ";
        std::string aPiocher;
        std::cin >> aPiocher;

        for (auto& carte : toutesLesCartes) {
            if (carte.getNom() == aPiocher) {
                if (carte.getStock() > 0 && carte.getCout() <= 4) {
                    joueur.getDefausse().push_back(carte);
                    carte.setStock(carte.getStock() - 1);
                    std::cout << "La carte " << carte.getNom() << " a été ajoutée à votre deck.\n";
                } else if (carte.getStock() == 0) {
                    std::cout << "Cette carte n'est plus disponible.\n";
                } else {
                    std::cout << "Cette carte est trop chère.\n";
                }
                return;
            }
        }
        std::cout << "Carte introuvable dans la réserve.\n";
    }
}

// Bucheron
void Royaume::Bucheron(Joueur& joueur) {
    if (carteDeBase.getNom() == "Bucheron") {
        joueur.setArgent(joueur.getArgent() + 2);
        joueur.setNombreAchats(joueur.getNombreAchats() + 1);
        std::cout << joueur.getNom() << " gagne 2 pièces d'or et un achat supplémentaire.\n";
    }
}

// Chapelle
void Royaume::Chapelle(Joueur& joueur) {
    if (carteDeBase.getNom() == "Chapelle") {
        int cartesADefauser = 0;
        while (cartesADefauser < 4 && !joueur.getMain().empty()) {
            std::cout << "Défaussez une carte (0 pour terminer) : ";
            int choix;
            std::cin >> choix;
            if (choix > 0 && choix <= joueur.getMain().size()) {
                joueur.getDefausse().push_back(joueur.getMain()[choix - 1]);
                joueur.getMain().erase(joueur.getMain().begin() + choix - 1);
                cartesADefauser++;
            } else {
                break;
            }
        }
    }
}

// Douve
void Royaume::Douve(Joueur& joueur) {
    if (this->nom == "Douve") {
        joueur.piocher(2);
        std::cout << joueur.getNom() << " pioche 2 cartes supplémentaires.\n";
    }
}

// Festin
void Royaume::Festin(Joueur& joueur) {
    if (this->nom == "Festin") {
        std::cout << "Quelle carte souhaitez-vous acheter (coût <= 5) ? ";
        std::string aAcheter;
        std::cin >> aAcheter;

        for (auto& carte : toutesLesCartes) {
            if (carte.getNom() == aAcheter) {
                if (carte.getStock() > 0 && carte.getCout() <= 5) {
                    joueur.getDeck().push_back(carte);
                    carte.setStock(carte.getStock() - 1);
                    std::cout << "La carte " << carte.getNom() << " a été ajoutée à votre deck.\n";
                } else if (carte.getStock() == 0) {
                    std::cout << "Cette carte n'est plus disponible.\n";
                } else {
                    std::cout << "Cette carte est trop chère.\n";
                }
                return;
            }
        }
        std::cout << "Carte introuvable dans la réserve.\n";
    }
}

// Jardins
void Royaume::Jardins(Joueur& joueur, Partie& partie) {
    if (this->nom == "Jardins" && partie.estFinie()) {
        joueur.setPointsVictoire(joueur.getPointsVictoire() + joueur.getDeck().size() / 10);
    }
}

// Laboratoire
void Royaume::Laboratoire(Joueur& joueur) {
    if (this->nom == "Laboratoire") {
        joueur.piocher(2);
        joueur.setNombreActions(joueur.getNombreActions() + 1);
        std::cout << joueur.getNom() << " pioche 2 cartes et gagne une action supplémentaire.\n";
    }
}

// Village
void Royaume::Village(Joueur& joueur) {
    if (this->nom == "Village") {
        joueur.piocher(1);
        joueur.setNombreActions(joueur.getNombreActions() + 2);
        std::cout << joueur.getNom() << " pioche 1 carte et gagne 2 actions supplémentaires.\n";
    }
}

// Sorcière
void Royaume::Sorciere(Joueur& joueur, Partie& partie) {
    if (this->nom == "Sorcière") {
        joueur.piocher(2);
        for (auto& autreJoueur : partie.getJoueurs()) {
            if (&autreJoueur != &joueur && !autreJoueur.possedeCarte("Douve")) {
                autreJoueur.piocherMalediction();
            }
        }
    }
}

// Voleur
void Royaume::Voleur(Joueur& joueur, Partie& partie) {
    if (this->nom == "Voleur") {
        for (auto& autreJoueur : partie.getJoueurs()) {
            if (&autreJoueur != &joueur && !autreJoueur.possedeCarte("Douve")) {
                for (int i = 0; i < 2; ++i) {
                    Cartes carte = autreJoueur.piocherCarte();
                    if (carte.getType() == "Tresor") {
                        std::cout << "Souhaitez-vous voler " << carte.getNom() << " ? (oui/non): ";
                        std::string reponse;
                        std::cin >> reponse;
                        if (reponse == "oui") {
                            joueur.getDefausse().push_back(carte);
                            break;
                        }
                    }
                }
            }
        }
    }
}
