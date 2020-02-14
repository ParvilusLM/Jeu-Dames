#ifndef DEF_MENU
#define DEF_MENU

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "constantes.h"
#include "varGlobales.h"


class Menu
{
public:
    Menu(sf::RenderWindow &fenetre);
    ~Menu();
    void initMenuP();
    void initMenuNP();
    void initMenuI();
    void initMenuAp();
    void afficheMenuP();
    void afficheMenuNP();
    void afficheMenuI();
    void afficheMenuAp();
    void affficheMenu();
    void elementActif();
    void selectionElActif();
    void retourMenuP();
    bool collisionTS(sf::FloatRect elem);
    TypeJeu getTypeJeu();
    void quitterJeu();

private:
    sf::RenderWindow* m_fenetre;

    TypeMenu m_typeMenu;
    sf::Font m_font;
    sf::Font m_font2;
    sf::Font m_font3;

    int m_elementActif;
    sf::Text m_txtRetour;
    sf::Text m_txtTypeMenu;
    sf::Sprite m_sFondEc;

    //pour menu principale
    sf::Text m_txtNouvlPartie;
    sf::Text m_txtInstructions;
    sf::Text m_txtAPropos;
    sf::Text m_txtQuitter;

    sf::Texture m_tFondEc;
    sf::Texture m_tFondEc2;

    //pour menu nouvellePartie
    sf::Text m_txtHvsH;
    sf::Text m_txtHvsIA;
    TypeJeu m_typeJeu;

    //pour menu Instructions
    sf::Text m_txtTMI;
    sf::Text m_txtMI;
    std::ostringstream m_stream_txtMI;


    //pour menu Apropos
    sf::Text m_txtTMAP;
    std::ostringstream m_stream_txtTMAP;

    sf::Text m_txtMAP;
    std::ostringstream m_stream_txtMAP;




};
#endif // DEF_MENU
