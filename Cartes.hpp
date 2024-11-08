#ifndef CARTES_HPP
#define CARTES_HPP

#include <iostream>
#include <vector>
#include <string>

class Cartes {
public:
    // Attributs de la classe Cartes
    std::string nom;
    std::string type;
    std::string description;
    int cout;
    int stock;
    static std::vector<Cartes*> toutesLesCartes;

    // Constructeur de la classe Cartes
    Cartes(std::string nom);
    
    // Destructeur de la classe Cartes
    ~Cartes();

    bool operator==(const Cartes& autre) const;
    std::string getType() const;
    std::string getNom() const; 
    int getStock() const;     
};

#endif // CARTES_HPP
