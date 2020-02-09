#ifndef DEF_CONTROLEUR
#define DEF_CONTROLEUR

#include "decor.h"
#include "enums.h"
#include "constantes.h"
#include "varGlobales.h"

class Controleur
{
public:
    Controleur(sf::RenderWindow &fenetre);
    ~Controleur();
    void debutJeu();
    void retourMenu();
    void afficheMenu();
    void afficheJeu();
    void demarrerHorl();
    void compteurTemps();
    void gestionTour(int ind_J);
    void Fin_Jeu();
    void gestionDplSouris();
    void gestionSelectionSouris();
    Decor* getDecor();
    void gestMajD();



private:
    sf::RenderWindow* m_fenetre;
    Decor* m_decor;


};

#endif // DEF_CONTROLEUR
