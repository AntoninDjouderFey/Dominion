#include "Cartes.hpp"
#include <iostream>

//constructeur
Cartes::Cartes(std::string nom) {
    this->nom = nom;
    if (nom =="Or" || nom=="Argent" || nom=="Cuivre") {
        this->type = "Tresor";
        if (nom == "Or") {
            this->cout=6;
            this->stock=30;
            this->description = "permet de gagner 3 pièces";
        } else if (nom == "Argent") {
            this->cout=3;
            this->stock=40;
            this->description = "permet de gagner 2 pièces";
        } else if (nom == "Cuivre") {
            this->cout=0;
            this->stock=60;
            this->description = "permet de gagner 1 pièce";
        } toutesLesCartes.push_back(this);
    } else if (nom == "Domaine" || nom == "Duché" || nom == "Province" || nom == "Malédiction" ) {
        this->type = "Victoire";
        if (nom == "Domaine") {
            this->cout=2;
            this->stock=24;
            this->description = "vous rapporte 1 point de victoire";
        } else if (nom == "Duché") {
            this->cout=5;
            this->stock=12;
            this->description = "vous rapporte 3 points de victoire";
        } else if (nom == "Province") {
            this->cout=8;
            this->stock=8; //le mettre à 12 si on a plus de 2 joueurs
            this->description = "vous rapporte 6 points de victoire";
        } else if (nom == "Malédiction") {
            this->cout=0;
            this->stock=30;
            this->description = "vous retire un point de victoire";
        } toutesLesCartes.push_back(this);
    } else if (nom == "Atelier" || nom == "Chapelle" || nom == "Laboratoire" || nom == "Village" || nom == "Douve" || nom == "Bûcheron" || nom == "Festin" || nom == "Jardins" || nom == "Sorcière" || nom == "Voleur") {
        this->type = "Royaume";
        if (nom == "Atelier") {
            this->cout=3;
            this->stock=10;
            this->description = "permet de gagner une carte coutant jusqu'à 4";
        } else if (nom == "Chapelle") {
            this->cout=2;
            this->stock=10;
            this->description = "permet de défausser jusqu'à 4 cartes de sa main";
        } else if (nom == "Laboratoire") {
            this->cout=5;
            this->stock=10;
            this->description = "permet de piocher 2 cartes et d'obtenir une action supplémentaire";
        } else if (nom == "Village") {
            this->cout=3;
            this->stock=10;
            this->description = "permet de piocher une carte et d'obtenir 2 actions supplémentaires";
        }
        else if (nom == "Voleur") {
            this->cout=4;
            this->stock=10;
            this->description = "les adversaire révèlent les 2 premières cartes de leur deck et vous en piquez une si elle est de type trésor";
        }
        else if (nom == "Douve") {
            this->cout=2;
            this->stock=10;
            this->description = "permet de se protéger des attaques adverses";
        }
        else if (nom == "Bûcheron") {
            this->cout=2;
            this->stock=10;
            this->description = "permet de gagner 2 pièces virtuelles et un achat supplémentaire";
        }
        else if (nom == "Festin") {
            this->cout=4;
            this->stock=10;
            this->description = "permet de gagner une carte coutant jusqu'à 5, jetée après utilisation";
        }
        else if (nom == "Jardins") {
            this->cout=4;
            this->stock=10;
            this->description = "vous rapporte 1 point de victoire pour chaque multiple de 10 cartes dans votre deck (cumulable)";
        }
        else if (nom == "Sorcière") {
            this->cout=5;
            this->stock=10;
            this->description = "permet de donner une malédiction à ses adversaires";
        }
        toutesLesCartes.push_back(this);
    } else {
        std::cout << "Erreur : nom de carte inconnu" << std::endl;
    }
}
std::string Cartes::getType() const {
    return type;
}
std::string Cartes::getNom() const {
    return nom;
}
int Cartes::getStock() const {
    return stock;
}
//destructeur
Cartes::~Cartes() {
    std::cout << "Destruction de la carte " << this->nom << std::endl;
}

bool Cartes::operator==(const Cartes& autre) const {
    return this->nom == autre.nom;
}