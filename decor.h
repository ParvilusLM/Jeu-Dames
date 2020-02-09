#ifndef DEF_DECOR
#define DEF_DECOR

#include <iostream>
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "constantes.h"
#include "varGlobales.h"
#include "menu.h"
#include "joueur.h"
#include "info.h"


class Decor
{
public:
    Decor(sf::RenderWindow &fenetre);
    ~Decor();
    void CreationTableDeJeu();
    void PositionInitialPions();
    void SelectionTextures();
    void effacementTJ();
    void gestIndicateurP();
    bool MarquagePionCapDeCap();
    void MarquagePionCapDeDepl();
    bool MarquageCaseValide();
    void gestMajD();
    void InitInfo();
    void gestionTour(int ind_J);

    void retourMenu();
    void demarrerHorl();
    void compteurTemps();

    void Fin_Jeu();
    void gestionDplSouris();
    void gestionSelectionSouris();

    void Afficher();
    void AfficherMenu();



private:
    sf::RenderWindow *m_fenetre;
    TableJeu m_tableJeu;
    JoueurC* m_joueurC;
    Menu* m_menu;
    Info* m_info;

    sf::Texture t_im_gagne,t_im_perdu;
    sf::Sprite s_masquePionCDC;



};

#endif // DEF_DECOR
