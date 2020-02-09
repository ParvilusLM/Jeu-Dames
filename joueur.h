#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include <iostream>
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "constantes.h"
#include "varGlobales.h"




class JoueurC
{
public:
    JoueurC();
    ~JoueurC();

    void HumainTour(TableJeu &table_jeu);
    void CPU_Tour(TableJeu &table_jeu);
    bool SelectionPionAJouer(TableJeu &table_jeu);
    bool ia_selectionPionAJouer(TableJeu &table_jeu);

    bool JeuPossibleSimplePion(TableJeu &table_jeu);
    bool JeuPossibleDame(TableJeu &table_jeu);

    bool ia_PossibiliteCapture(TableJeu &table_jeu);
    bool ia_PossibiliteCaptureDame(TableJeu &table_jeu);

    bool PossibiliteCaptureDame(TableJeu &table_jeu);
    bool PossibiliteCapture(TableJeu &table_jeu);

    void PromotionPion(TableJeu &table_jeu);
    void CapturePion(TableJeu &table_jeu,int joueur);



    void DeplacementSimplePion(TableJeu &table_jeu);
    void DeplacementDame(TableJeu &table_jeu);

    Joueur getJoueur(int nJ);



private:
    Joueur m_joueur_1;
    Joueur m_joueur_2;








};

#endif // DEF_JOUEUR
