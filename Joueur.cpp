
#include "Joueur.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>

Joueur::Joueur(const std::string& nom)
    : nom(nom), pointsVictoire(0), nombreActions(1), nombreAchats(1), argent(0) {
    // Ajouter 7 cartes Cuivre au deck
    for (int i = 0; i < 7; ++i) {
        auto carte = std::make_shared<Cartes>("Cuivre");
        deck.push_back(carte);
        
    }

    // Ajouter 3 cartes Domaine au deck
    for (int i = 0; i < 3; ++i) {
        auto carte = std::make_shared<Cartes>("Domaine");
        deck.push_back(carte);
        
    }

    // Mélanger le deck
    melangerDeck();

    // Piocher les 5 premières cartes dans la main
    for (int i = 0; i < 5 && !deck.empty(); ++i) {
        main.push_back(deck.back());
        deck.pop_back();
    }

    // Vérifier les cartes restantes dans le deck après la pioche
    std::cout << "Deck apres pioche initiale de 5 cartes :\n";
    for (const auto& carte : deck) {
        std::cout << "- " << carte->getNom() << " (" << carte->getType() << ")\n";
    }

    // Afficher les cartes de la main pour vérification
    std::cout << "Main initiale de " << nom << " :\n";
    for (const auto& carte : main) {
        std::cout << "- " << carte->getNom() << " (" << carte->getType() << ")\n";
    }

    // Calculer les points de victoire initiaux et l'argent
    int totalPointsVictoire = 0;
    int totalArgent = 0;

    for (const auto& carte : deck) {
        if (carte->getType() == "Victoire") {
            totalPointsVictoire += (carte->getNom() == "Domaine" ? 1 : 0);
        } else if (carte->getType() == "Tresor") {
            totalArgent += (carte->getNom() == "Cuivre" ? 1 : 0);
        }
    }

    for (const auto& carte : main) {
        if (carte->getType() == "Victoire") {
            totalPointsVictoire += (carte->getNom() == "Domaine" ? 1 : 0);
        } else if (carte->getType() == "Tresor") {
            totalArgent += (carte->getNom() == "Cuivre" ? 1 : 0);
        }
    }

    setPointsVictoire(totalPointsVictoire);
    setArgent(totalArgent);

    // Afficher les points de victoire et l'argent
    std::cout << nom << " commence avec :\n";
    std::cout << "- " << pointsVictoire << " points de victoire\n";
    std::cout << "- " << argent << " pieces d'or\n";
}


std::vector<std::shared_ptr<Cartes>>& Joueur::getMain() {
    return main;
}


void Joueur::setMain(const std::vector<std::shared_ptr<Cartes>>& mano) {
    main = mano;
}


int Joueur::getArgent() const {
    return argent;
}

void Joueur::setArgent(int n_argent) {
    argent = n_argent;
}
void Joueur::setPointsVictoire(int points) {
    pointsVictoire = points;
}


void Joueur::setDeck(const std::vector<std::shared_ptr<Cartes>>& nouveauDeck) {
    deck = nouveauDeck;
}


void Joueur::setNombreActions(int nbactions) {
    nombreActions = nbactions;
}
void Joueur::setNombreAchats(int nbAchats) {
    nombreAchats = nbAchats;
}
std::shared_ptr<Cartes> Joueur::piocher(int nombre) {
    std::shared_ptr<Cartes> derniereCartePiocher;

    for (int i = 0; i < nombre; ++i) {
        if (deck.empty()) {
            // Reconstituer le deck si vide
            if (!defausse.empty()) {
                deck = defausse;
                defausse.clear();
                melangerDeck();
                std::cout << "Le deck a été reconstitué à partir de la défausse.\n";
            } else {
                std::cout << "Erreur : Plus de cartes disponibles pour le joueur " << nom << ".\n";
                break;
            }
        }

        // Piocher une carte depuis le deck
        if (!deck.empty()) {
            derniereCartePiocher = deck.back();
            main.push_back(derniereCartePiocher);
            deck.pop_back();

            // DEBUG : Vérifier les cartes ajoutées à la main
            std::cout << "Carte piochée : " << derniereCartePiocher->getNom() << " (" << derniereCartePiocher->getType() << ")\n";
        }
    }

    // DEBUG : Vérifier l'état de la main après la pioche
    std::cout << "Main après pioche :\n";
    for (const auto& carte : main) {
        std::cout << "- " << carte->getNom() << " (" << carte->getType() << ")\n";
    }

    return derniereCartePiocher;
}


void Joueur::piocherMalediction() {
    // Trouver la carte Malédiction dans la réserve
    auto it = std::find_if(Cartes::toutesLesCartes.begin(), Cartes::toutesLesCartes.end(),
        [](const std::shared_ptr<Cartes>& carte) { return carte->getNom() == "Malediction" && carte->getStock() > 0; });

    if (it != Cartes::toutesLesCartes.end()) {
        // Ajouter la carte Malédiction à la défausse du joueur
        defausse.push_back(*it);

        // Réduire le stock de Malédiction
        (*it)->setStock((*it)->getStock() - 1);

        std::cout << getNom() << " reçoit une carte Malédiction, ce qui réduit ses points de victoire.\n";
    } else {
        std::cout << "Plus de cartes Malédiction disponibles dans la réserve.\n";
    }
}


bool Joueur::possedeCarte(const std::string& nomCarte) const {
    for (const auto& carte : main) { // Ici, 'main' est supposé être la liste des cartes en main
        if (carte->getNom() == nomCarte) {
            return true;
        }
    }
    return false;
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
int Joueur::calculerOrEnMain() const {
    int totalOr = 0;
    for (const auto& carte : main) {
        if (carte->getType() == "Tresor") {
            if (carte->getNom() == "Cuivre") totalOr += 1;
            else if (carte->getNom() == "Argent") totalOr += 2;
            else if (carte->getNom() == "Or") totalOr += 3;
        }
    }
    return totalOr;
}

int Joueur::calculerPointsVictoire() const {
    int points = 0;
    for (const auto& carte : deck) {
        if (carte->getType() == "Victoire") {
            if (carte->getNom() == "Domaine") points += 1;
            else if (carte->getNom() == "Duche") points += 3;
            else if (carte->getNom() == "Province") points += 6;
            else if (carte->getNom() == "Malediction") points -= 1;
        }
    }
    return points;
}

void Joueur::jouerAction(int indiceCarte) {
    if (static_cast<size_t>(indiceCarte) < main.size() && main[indiceCarte]->getType() == "Royaume" && nombreActions > 0) {
        nombreActions--;
        defausse.push_back(main[indiceCarte]); // Ajoute la carte dans la défausse
        main.erase(main.begin() + indiceCarte); // Retire la carte de la main
    } else {
        std::cout << "Action non valide ou pas assez d actions disponibles.\n";
    }
}

void Joueur::acheterCarte(Cartes& carte) {
    if (nombreAchats > 0) {
        if (argent >= carte.getCout() && carte.getStock() > 0) {
            nombreAchats--;

            // Réduire l'argent du joueur en fonction du coût de la carte
            int coutRestant = carte.getCout();
            for (auto it = main.begin(); it != main.end() && coutRestant > 0; ) {
                if ((*it)->getType() == "Tresor") {
                    if ((*it)->getNom() == "Cuivre") coutRestant -= 1;
                    else if ((*it)->getNom() == "Argent") coutRestant -= 2;
                    else if ((*it)->getNom() == "Or") coutRestant -= 3;

                    defausse.push_back(*it); // Déplace la carte trésor dans la défausse
                    it = main.erase(it);     // Retire la carte de la main
                } else {
                    ++it;
                }
            }

            if (coutRestant <= 0) {
                // Ajouter la carte achetée dans la défausse
                defausse.push_back(std::make_shared<Cartes>(carte));
                carte.setStock(carte.getStock() - 1); // Réduire le stock de la carte
                std::cout << nom << " a acheté " << carte.getNom() << " et l a placée dans sa défausse.\n";
            } else {
                std::cout << "Erreur : Pas assez de tresors pour acheter " << carte.getNom() << ".\n";
            }
        } else {
            std::cout << "Erreur : Pas assez d'or ou carte en rupture de stock.\n";
        }
    } else {
        std::cout << "Erreur : Pas d achats disponibles pour ce tour.\n";
    }
}
void Joueur::afficherEtat() const {
    std::cout << "\n--- Etat du joueur " << nom << " ---\n";

    // Afficher le contenu de la main
    std::cout << "Main : ";
    if (!main.empty()) {
        for (const auto& carte : main) {
            std::cout << carte->getNom() << " ";
        }
    } else {
        std::cout << "(vide)";
    }
    std::cout << "\n";

    // Afficher le contenu de la défausse
    std::cout << "Défausse : ";
    if (!defausse.empty()) {
        for (const auto& carte : defausse) {
            std::cout << carte->getNom() << " ";
        }
    } else {
        std::cout << "(vide)";
    }
    std::cout << "\n";

    // Afficher le contenu du deck
    std::cout << "Deck : ";
    if (!deck.empty()) {
        for (const auto& carte : deck) {
            std::cout << carte->getNom() << " ";
        }
    } else {
        std::cout << "(vide)";
    }
    std::cout << "\n--------------------------------\n";
}


void Joueur::finDuTour() {
    // Déplacer toutes les cartes de la main dans la défausse
    defausse.insert(defausse.end(), main.begin(), main.end());
    main.clear();  // Vider la main

    // Reconstituer le deck si nécessaire
    if (deck.empty()) {
        if (!defausse.empty()) {
            deck = defausse;  // Transférer la défausse dans le deck
            defausse.clear(); // Vider la défausse
            melangerDeck();   // Mélanger le nouveau deck
            std::cout << "Le deck a été reconstitué à partir de la défausse.\n";
        } else {
            std::cout << "Le joueur " << nom << " n'a plus de cartes disponibles.\n";
            return; // Sortir si aucune carte n'est disponible
        }
    }

    // Piocher 5 cartes dans le deck
    for (int i = 0; i < 5 && !deck.empty(); ++i) {
        main.push_back(deck.back());
        deck.pop_back();
    }

    // Réinitialiser les variables pour le prochain tour
    nombreActions = 1;
    nombreAchats = 1;
    argent = calculerOrEnMain();  // Calculer l'or disponible avec les nouvelles cartes en main

    // Afficher l'état du joueur après le tour
    std::cout << "Fin du tour pour " << nom << ".\n";
    afficherEtat();
}
void Joueur::verifierMain() {
    // Si la main contient plus de 5 cartes, déplacer les cartes excédentaires dans la défausse
    while (main.size() > 5) {
        std::cout << "La main de " << nom << " a plus de 5 cartes. Correction en cours...\n";
        defausse.push_back(main.back());
        main.pop_back();
    }

    // Si la main contient moins de 5 cartes, piocher jusqu'à atteindre 5 cartes
    while (main.size() < 5) {
        if (!deck.empty()) {
            std::cout << "Le joueur " << nom << " pioche une carte depuis le deck.\n";
            piocher(1);
        } else if (!defausse.empty()) {
            std::cout << "Le deck est vide. Le joueur " << nom << " reconstitue le deck depuis la défausse.\n";
            deck = defausse;
            defausse.clear();
            melangerDeck();
        } else {
            std::cout << "Aucune carte disponible pour le joueur " << nom << ".\n";
            break;
        }
    }
}



std::vector<std::shared_ptr<Cartes>>& Joueur::getDeck() {
    return deck;
}

const std::string& Joueur::getNom() const { return nom; }
int Joueur::getPointsVictoire() const { return pointsVictoire; }
std::vector<std::shared_ptr<Cartes>>& Joueur::getDefausse() {
    return defausse;
}

void Joueur::melangerDeck() {

    std::mt19937 g(static_cast<unsigned int>(std::time(0)));
    std::shuffle(deck.begin(), deck.end(), g);

    std::cout << "Deck après mélange :\n";
    for (const auto& carte : deck) {
        std::cout << "- " << carte->getNom() << " (" << carte->getType() << ")\n";
    }
} 
void Joueur::supprimerCarte(const std::shared_ptr<Cartes>& carte) {
    // Supprimer de la main
    auto it = std::find(main.begin(), main.end(), carte);
    if (it != main.end()) {
        main.erase(it);
        std::cout << "Carte " << carte->getNom() << " supprimée de la main.\n";
        return;
    }

    // Supprimer du deck
    it = std::find(deck.begin(), deck.end(), carte);
    if (it != deck.end()) {
        deck.erase(it);
        std::cout << "Carte " << carte->getNom() << " supprimée du deck.\n";
        return;
    }

    // Supprimer de la défausse
    it = std::find(defausse.begin(), defausse.end(), carte);
    if (it != defausse.end()) {
        defausse.erase(it);
        std::cout << "Carte " << carte->getNom() << " supprimée de la défausse.\n";
    }
}