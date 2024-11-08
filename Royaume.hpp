#ifndef ROYAUME_HPP
#define ROYAUME_HPP

#include "Cartes.hpp"
#include "Joueur.h"
#include "Partie.h"
#include <string>

class Royaume : public Cartes {
public:
    // Constructeur et destructeur
    Royaume(const Cartes& carte);
    ~Royaume();

    // Effets des cartes Royaume
    void Atelier(Joueur& joueur);
    void Bucheron(Joueur& joueur);
    void Chapelle(Joueur& joueur);
    void Laboratoire(Joueur& joueur);
    void Village(Joueur& joueur);
    void Douve(Joueur& joueur);
    void Festin(Joueur& joueur);
    void Jardins(Joueur& joueur, Partie& partie);
    void Sorciere(Joueur& joueur, Partie& partie);
    void Voleur(Joueur& joueur, Partie& partie);
};

#endif // ROYAUME_HPP
