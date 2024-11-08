#include "Partie.h"
#include "Joueur.h"
#include "Cartes.hpp"
#include <iostream>

Partie::Partie(const std::vector<std::string>& nomsJoueurs) : joueurActuel(0) {
    for (const auto& nom : nomsJoueurs) {
        joueurs.emplace_back(nom);
    }
    initialiserReserve();
}

void Partie::demarrer() {
    while (!estFinie()) {
        jouerTour();
        joueurActuel = (joueurActuel + 1) % joueurs.size();
    }
    annoncerVainqueur();
}

void Partie::jouerTour() {
    Joueur& joueur = joueurs[joueurActuel];
    std::cout << "\nTour de " << joueur.getNom() << "\n";

    // Calculer les pièces d'or disponibles en main
    joueur.finDuTour();  // Mélanger la défausse et piocher la main
    calculerOrEnMain(joueur);

    bool tourTermine = false;
    while (!tourTermine) {
        afficherEtat();
        std::cout << "\nActions possibles pour " << joueur.getNom() << ":\n";
        std::cout << "1 - Piocher une carte\n";
        std::cout << "2 - Jouer une carte action\n";
        std::cout << "3 - Acheter une carte de la réserve\n";
        std::cout << "4 - Terminer le tour\n";
        std::cout << "Choisissez une option : ";

        int choix;
        std::cin >> choix;

        switch (choix) {
            case 1:
                joueur.piocher();
                calculerOrEnMain(joueur); // Met à jour les pièces d'or
                break;
            case 2:
                jouerCarteAction(joueur);
                break;
            case 3:
                acheterCarte(joueur);
                break;
            case 4:
                tourTermine = true;
                joueur.finDuTour();
                break;
            default:
                std::cout << "Option non valide. Réessayez.\n";
        }
    }
    std::cout << "Fin du tour de " << joueur.getNom() << ".\n";
}

void Partie::calculerOrEnMain(Joueur& joueur) {
    int argentTotal = 0;
    for (const auto& carte : joueur.getDeck()) {
        if (carte.getType() == "Tresor") {
            if (carte.getNom() == "Cuivre") argentTotal += 1;
            else if (carte.getNom() == "Argent") argentTotal += 2;
            else if (carte.getNom() == "Or") argentTotal += 3;
        }
    }
    joueur.ajouterArgent(argentTotal); // Méthode à ajouter dans la classe Joueur pour gérer l'argent
    std::cout << joueur.getNom() << " a " << argentTotal << " pièces d'or en main.\n";
}
void Partie::phaseAction(Joueur& joueur) {
    if (joueur.getNombreActions() > 0) {
        std::cout << "\nPhase d'Action pour " << joueur.getNom() << "\n";
        std::cout << "Cartes en main :\n";
        for (size_t i = 0; i < joueur.getDeck().size(); ++i) {
            std::cout << i + 1 << " - " << joueur.getDeck()[i].getNom() << " (" << joueur.getDeck()[i].getDescription() << ")\n";
        }

        int choix;
        std::cout << "Choisissez une carte Action à jouer (0 pour passer) : ";
        std::cin >> choix;

        if (choix > 0 && choix <= joueur.getDeck().size() && joueur.getDeck()[choix - 1].getType() == "Royaume") {
            joueur.jouerAction(choix - 1);  // Décrémenter les actions dans `jouerAction`
            calculerOrEnMain(joueur);       // Met à jour les pièces si la carte Action affecte l'argent
        } else {
            std::cout << "Action non valide ou pas de carte Action sélectionnée.\n";
        }
    } else {
        std::cout << joueur.getNom() << " n'a plus d'actions disponibles.\n";
    }
}

void Partie::phaseAchat(Joueur& joueur) {
    if (joueur.getArgent() > 0 && joueur.getNombreAchats() > 0) {
        std::cout << "\nPhase d'Achat pour " << joueur.getNom() << "\n";
        std::cout << "Cartes disponibles dans la réserve :\n";
        for (size_t i = 0; i < reserve.size(); ++i) {
            std::cout << i + 1 << " - " << reserve[i].getNom() << " (Coût : " << reserve[i].getCout() 
                      << ", Stock : " << reserve[i].getStock() << ")\n";
        }

        int choix;
        std::cout << "Choisissez une carte à acheter (0 pour passer) : ";
        std::cin >> choix;

        if (choix > 0 && choix <= reserve.size()) {
            Cartes& carte = reserve[choix - 1];
            if (joueur.getArgent() >= carte.getCout() && carte.getStock() > 0) {
                joueur.acheterCarte(carte);  // Méthode `acheterCarte` gère le décompte des achats et des pièces
                std::cout << joueur.getNom() << " a acheté " << carte.getNom() << ".\n";
            } else {
                std::cout << "Pas assez de pièces ou stock épuisé pour " << carte.getNom() << ".\n";
            }
        }
    } else {
        std::cout << joueur.getNom() << " n'a plus d'achats ou pas assez d'argent.\n";
    }
}

void Partie::phaseAjustement(Joueur& joueur) {
    std::cout << "\nPhase d'Ajustement pour " << joueur.getNom() << "\n";
    joueur.finDuTour();  // Place toutes les cartes de la main et de l'aire de jeu dans la défausse, puis pioche 5 nouvelles cartes
    std::cout << joueur.getNom() << " a terminé son tour.\n";
}

void Partie::jouerCarteAction(Joueur& joueur) {
    if (joueur.getNombreActions() <= 0) {
        std::cout << "Vous n'avez plus d'actions disponibles.\n";
        return;
    }

    std::cout << "Cartes en main :\n";
    for (size_t i = 0; i < joueur.getDeck().size(); ++i) {
        std::cout << i + 1 << " - " << joueur.getDeck()[i].getNom() << " (" << joueur.getDeck()[i].getDescription() << ")\n";
    }

    int indiceCarte;
    std::cout << "Choisissez une carte action à jouer (0 pour annuler) : ";
    std::cin >> indiceCarte;

    if (indiceCarte > 0 && indiceCarte <= joueur.getDeck().size()) {
        joueur.jouerAction(indiceCarte - 1);
        calculerOrEnMain(joueur); // Met à jour l'or si la carte affecte les pièces
    }
}

void Partie::acheterCarte(Joueur& joueur) {
    std::cout << "Cartes disponibles dans la réserve :\n";
    for (size_t i = 0; i < reserve.size(); ++i) {
        std::cout << i + 1 << " - " << reserve[i].getNom() << " (Coût : " << reserve[i].getCout() 
                  << ", Stock : " << reserve[i].getStock() << ")\n";
    }

    int choixCarte;
    std::cout << "Choisissez une carte à acheter (0 pour annuler) : ";
    std::cin >> choixCarte;

    if (choixCarte > 0 && choixCarte <= reserve.size()) {
        Cartes& carte = reserve[choixCarte - 1];
        if (joueur.getArgent() >= carte.getCout() && carte.getStock() > 0) {
            joueur.acheterCarte(carte);
            std::cout << joueur.getNom() << " a acheté " << carte.getNom() << ".\n";
        } else {
            std::cout << "Pas assez de pièces ou stock épuisé.\n";
        }
    }
}

bool Partie::estFinie() const {
    // Condition de fin : la pile de cartes "Province" est vide
    for (const auto& carte : reserve) {
        if (carte.getNom() == "Province" && carte.getStock() == 0) {
            return true;
        }
    }

    // Condition de fin : au moins trois piles de la réserve sont vides
    int pilesVides = 0;
    for (const auto& carte : reserve) {
        if (carte.getStock() == 0) {
            pilesVides++;
        }
    }
    return pilesVides >= 3;
}

void Partie::annoncerVainqueur() const {
    std::cout << "La partie est terminée !\n";
    int maxPoints = 0;
    std::string nomVainqueur;

    for (const auto& joueur : joueurs) {
        int points = joueur.calculerPointsVictoire();
        std::cout << joueur.getNom() << " a " << points << " points de victoire.\n";
        if (points > maxPoints) {
            maxPoints = points;
            nomVainqueur = joueur.getNom();
        }
    }
    std::cout << "Le vainqueur est " << nomVainqueur << " avec " << maxPoints << " points de victoire !\n";
}

void Partie::initialiserReserve() {
    reserve.push_back(Cartes("Or"));
    reserve.push_back(Cartes("Argent"));
    reserve.push_back(Cartes("Cuivre"));
    reserve.push_back(Cartes("Domaine"));
    reserve.push_back(Cartes("Duché"));
    reserve.push_back(Cartes("Province"));
    reserve.push_back(Cartes("Atelier"));
    reserve.push_back(Cartes("Chapelle"));
    reserve.push_back(Cartes("Laboratoire"));
    reserve.push_back(Cartes("Village"));
}

void Partie::afficherEtat() const {
    std::cout << "\nÉtat actuel du jeu :\n";
    for (const auto& joueur : joueurs) {
        std::cout << "- " << joueur.getNom() << " a " << joueur.getPointsVictoire() << " points de victoire et " 
                << joueur.getArgent() << " pièces d'or.\n";
    }

    std::cout << "\nCartes dans la réserve :\n";
    for (const auto& carte : reserve) {
        std::cout << "- " << carte.getNom() << " (Stock : " << carte.getStock() << ", Coût : " << carte.getCout() << ")\n";
    }
}
