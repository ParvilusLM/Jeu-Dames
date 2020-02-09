#ifndef DEF_VARGLOBALES
#define DEF_VARGLOBALES

#include <SFML/Graphics.hpp>
#include <iostream>

extern std::vector<sf::Vector2f> ensembleCaseValide;
extern std::vector<sf::Vector2f>ensemblePionValide;
extern std::vector<sf::Vector2f>ensemblePCapDeDepl;
extern bool HumvsHum;
extern bool jeu_en_cours;
extern sf::Texture t_tableDames,t_pion_r,t_pion_b,t_pion_r_d,t_pion_b_d,t_indic_selection,t_masquePionCDC;
extern sf::Sprite s_indic_selection;
extern std::vector<sf::Sprite> ensembleImPionValide;
extern std::vector<sf::Sprite> ensembleImCaseValide;
extern int sourisX,sourisY;
extern bool LA_MAIN;
extern bool ia_simp_depl;
extern bool ia_captur_p;
extern bool selec_valide;
extern bool fin_partie;
extern bool partie_gagne;

extern bool h_capture;
extern bool h_deplacem;


struct Pion
{
    int type_pion;
    bool selectionne;
    bool capture;
    sf::Sprite s_pion;

};

struct Joueur
{
    int nb_pions;
    int nb_pions_cap;
    std::vector<Pion> pions;
};

struct TableJeu
{
    sf::Sprite s_tableDeJeu;

  std::vector<Joueur> joueurs;
};

struct CaseValabe
{
    int positionX;
    int positionY;
    int valeur_chemin;
    int lien_ch_precd;
    int num_chem;
    bool a_droite;
    bool b_a_droite;

    bool i_d_h_g;
    bool i_d_h_d;
    bool i_d_b_g;
    bool i_d_b_d;

    bool mouv_h_g;
    bool mouv_h_d;
    bool mouv_b_g;
    bool mouv_b_d;
};


#endif // DEF_VARGLOBALES
