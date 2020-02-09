#ifndef DEF_INFO
#define DEF_INFO

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "constantes.h"
#include "varGlobales.h"


class Info
{
public:
    Info(sf::RenderWindow &fenetre);
    ~Info();
    void initInfo();
    void reinitInfo();
    void reinitialiserH();
    void demarrerH();
    void pauseH();
    float getTemps();
    int getNbDplP();
    template <class T> std::string nbEnString(T nb);
    void indiquerNiveau();
    void compteurDeplacementP();
    void gestionTemps();
    void afficheInfo();
    void maj_Info(TableJeu &table_jeu);

private:
    sf::Text m_txtTemps;
    sf::Font m_fntTemps;
    sf::Font m_fntAutre;
    sf::Font font_1,font_2;
    sf::Texture m_tCadre;
    sf::Sprite m_sCadre;
    EtatH m_etatH;
    sf::Clock m_horloge;
    float m_tempsEcoule;
    std::ostringstream stream_text,etat_jR,etat_jB;
    sf::Text infoJeu;
    sf::RenderWindow* m_fenetre;


};
#endif // DEF_INFO
