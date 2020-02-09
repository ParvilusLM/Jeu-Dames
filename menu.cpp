#include "menu.h"

Menu::Menu(sf::RenderWindow &fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;
    m_font.loadFromFile("donnees/forte.ttf");
    m_font2.loadFromFile("donnees/ALGER.ttf");
    m_font3.loadFromFile("donnees/rod.ttf");

    m_tFondEc.loadFromFile("donnees/cadre_menu.png");
    m_tFondEc2.loadFromFile("donnees/cadre_menu2.png");

    m_txtTypeMenu.setFont(m_font2);
    m_txtTypeMenu.setCharacterSize(35);
    m_txtTypeMenu.setFillColor(sf::Color::Black);
    m_txtTypeMenu.setPosition(310,200);



    m_txtRetour.setFont(m_font);
    m_txtRetour.setCharacterSize(30);
    m_txtRetour.setFillColor(sf::Color::Black);
    m_txtRetour.setPosition(20,30);
    m_txtRetour.setString("RETOUR");


    m_typeMenu=MenuPrincipale;
    initMenuP();
    initMenuNP();
    initMenuI();
    initMenuAp();


}


void Menu::initMenuP()
{
    m_sFondEc.setTexture(m_tFondEc);
    m_sFondEc.setPosition(0,0);

    m_txtNouvlPartie.setFont(m_font);
    m_txtNouvlPartie.setCharacterSize(40);
    m_txtNouvlPartie.setFillColor(sf::Color::Black);
    m_txtNouvlPartie.setPosition(320,280);
    m_txtNouvlPartie.setString("Nouvelle Partie");

    m_txtInstructions.setFont(m_font);
    m_txtInstructions.setCharacterSize(40);
    m_txtInstructions.setFillColor(sf::Color::Black);
    m_txtInstructions.setPosition(360,360);
    m_txtInstructions.setString("Instructions");

    m_txtAPropos.setFont(m_font);
    m_txtAPropos.setCharacterSize(40);
    m_txtAPropos.setFillColor(sf::Color::Black);
    m_txtAPropos.setPosition(380,440);
    m_txtAPropos.setString("A propos");

    m_txtQuitter.setFont(m_font);
    m_txtQuitter.setCharacterSize(40);
    m_txtQuitter.setFillColor(sf::Color::Black);
    m_txtQuitter.setPosition(400,520);
    m_txtQuitter.setString("Quitter");



}

void Menu::initMenuNP()
{
     m_txtHvsH.setFont(m_font);
     m_txtHvsH.setCharacterSize(40);
     m_txtHvsH.setFillColor(sf::Color::Black);
     m_txtHvsH.setPosition(300,350);
     m_txtHvsH.setString("HUMAIN vs CPU");

     m_txtHvsIA.setFont(m_font);
     m_txtHvsIA.setCharacterSize(40);
     m_txtHvsIA.setFillColor(sf::Color::Black);
     m_txtHvsIA.setPosition(250,450);
     m_txtHvsIA.setString("HUMAIN vs HUMAIN");




}

void Menu::initMenuI()
{
    m_txtTMI.setFont(m_font3);
    m_txtTMI.setCharacterSize(40);
    m_txtTMI.setFillColor(sf::Color::Black);
    m_txtTMI.setPosition(500,310);
    m_txtTMI.setString("DAMES AMERICAINES");


    m_txtMI.setFont(m_font3);
    m_txtMI.setCharacterSize(25);
    m_txtMI.setFillColor(sf::Color::Black);
    m_txtMI.setPosition(10,380);


    m_stream_txtMI.str("");
    m_stream_txtMI<<"DAMES AMERICAINES se joue sur un tableau 8*8 avec 12 pions de chaque cote.\n"
                  <<"Les pions non couronnes peuvent se deplacer et capturer en avant.\n"
                  <<"Quand il y a plus d'une maniere pour un joueur de sauter, on peut choisir laquelle \n "
                  <<"des sequences a faire,necessairement celle avec le plus grand nombre de captures.\n"
                  <<"Toutefois on doit faire toutes les captures dans cette sequence.\n"
                  <<"Les dames peuvent se deplacer seulement d'un carreau.";

    m_txtMI.setString(m_stream_txtMI.str());
}

void Menu::initMenuAp()
{

}


void Menu::affficheMenu()
{
    m_fenetre->draw(m_sFondEc);


    if(m_typeMenu==MenuPrincipale)
    {
        afficheMenuP();
    }
    else if(m_typeMenu==MenuNvlPartie)
    {
        afficheMenuNP();
    }
    else if(m_typeMenu==MenuInstructions)
    {
        afficheMenuI();
    }
    else
    {
        afficheMenuAp();
    }
}

void Menu::afficheMenuP()
{
    m_fenetre->draw(m_txtNouvlPartie);
    m_fenetre->draw(m_txtInstructions);
    m_fenetre->draw(m_txtAPropos);
    m_fenetre->draw(m_txtQuitter);

    m_txtTypeMenu.setString("Menu Principale");
    m_fenetre->draw(m_txtTypeMenu);
}

void Menu::afficheMenuNP()
{
    m_fenetre->draw(m_txtHvsH);
    m_fenetre->draw(m_txtHvsIA);
    m_fenetre->draw(m_txtRetour);

    m_txtTypeMenu.setString("       Type Jeu");
    m_fenetre->draw(m_txtTypeMenu);
}

void Menu::afficheMenuI()
{
    m_fenetre->draw(m_txtRetour);

    m_txtTypeMenu.setString("   Instructions");
    m_fenetre->draw(m_txtTypeMenu);
    m_fenetre->draw(m_txtTMI);
    m_fenetre->draw(m_txtMI);
}

void Menu::afficheMenuAp()
{
    m_fenetre->draw(m_txtRetour);

    m_txtTypeMenu.setString("       A propos");
    m_fenetre->draw(m_txtTypeMenu);
}

void Menu::quitterJeu()
{
    m_fenetre->close();
}

void Menu::elementActif()
{

    if(m_typeMenu==MenuPrincipale)
    {
        if(collisionTS(m_txtNouvlPartie.getGlobalBounds()))
        {
            m_txtNouvlPartie.setColor(sf::Color::Red);
            m_elementActif=NP_ACTIF;
        }
        else if(collisionTS(m_txtInstructions.getGlobalBounds()))
        {
            m_txtInstructions.setColor(sf::Color::Red);
            m_elementActif=I_ACTIF;
        }
        else if(collisionTS(m_txtAPropos.getGlobalBounds()))
        {
            m_txtAPropos.setColor(sf::Color::Red);
            m_elementActif=AP_ACTIF;
        }
        else if(collisionTS(m_txtQuitter.getGlobalBounds()))
        {
            m_txtQuitter.setColor(sf::Color::Red);
            m_elementActif=Q_ACTIF;
        }
        else
        {
            m_txtNouvlPartie.setColor(sf::Color::Black);
            m_txtInstructions.setColor(sf::Color::Black);
            m_txtAPropos.setColor(sf::Color::Black);
            m_txtQuitter.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }

    }
    else if(m_typeMenu==MenuNvlPartie)
    {
        if(collisionTS(m_txtHvsH.getGlobalBounds()))
        {
            m_txtHvsH.setColor(sf::Color::Red);
            m_elementActif=JHvsH_ACTIF;
        }
        else if(collisionTS(m_txtHvsIA.getGlobalBounds()))
        {
            m_txtHvsIA.setColor(sf::Color::Red);
            m_elementActif=JHvsIA_ACTIF;
        }
        else if(collisionTS(m_txtRetour.getGlobalBounds()))
        {
            m_txtRetour.setColor(sf::Color::Red);
            m_elementActif=R_ACTIF;
        }
        else
        {
            m_txtHvsH.setColor(sf::Color::Black);
            m_txtHvsIA.setColor(sf::Color::Black);
            m_txtRetour.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }
    }
    else if(m_typeMenu==MenuInstructions)
    {
        if(collisionTS(m_txtRetour.getGlobalBounds()))
        {
            m_txtRetour.setColor(sf::Color::Red);
            m_elementActif=R_ACTIF;
        }
        else
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }
    }
    else
    {
        if(collisionTS(m_txtRetour.getGlobalBounds()))
        {
            m_txtRetour.setColor(sf::Color::Red);
            m_elementActif=R_ACTIF;
        }
        else
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_elementActif=AUCUN_EL_ACT;
        }
    }

}

void Menu::selectionElActif()
{
    if(m_typeMenu==MenuPrincipale)
    {
        if(m_elementActif==NP_ACTIF)
        {
            m_txtNouvlPartie.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc2);
            m_typeMenu=MenuNvlPartie;
        }
        else if(m_elementActif==I_ACTIF)
        {
            m_txtInstructions.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc2);
            m_typeMenu=MenuInstructions;
        }
        else if(m_elementActif==AP_ACTIF)
        {
            m_txtAPropos.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc2);
            m_typeMenu=MenuApropos;
        }
        else if(m_elementActif==Q_ACTIF)
        {
            m_txtQuitter.setColor(sf::Color::Black);
            quitterJeu();
        }
        else
        {

        }
    }
    else if(m_typeMenu==MenuNvlPartie)
    {
        if(m_elementActif==JHvsH_ACTIF)
        {
            m_txtHvsH.setColor(sf::Color::Black);
            jeu_en_cours=true;
            m_typeJeu=HUMAINvsHUMAIN;
        }
        else if(m_elementActif==JHvsIA_ACTIF)
        {
            m_txtHvsIA.setColor(sf::Color::Black);
            jeu_en_cours=true;
            m_typeJeu=HUMAINvsIA;
        }
        else if(m_elementActif==R_ACTIF)
        {
             m_txtRetour.setColor(sf::Color::Black);
             m_sFondEc.setTexture(m_tFondEc);
             m_typeMenu=MenuPrincipale;
        }
        else
        {

        }

    }
    else if(m_typeMenu==MenuInstructions)
    {
        if(m_elementActif==R_ACTIF)
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc);
            m_typeMenu=MenuPrincipale;
        }
        else
        {

        }

    }
    else
    {
        if(m_elementActif==R_ACTIF)
        {
            m_txtRetour.setColor(sf::Color::Black);
            m_sFondEc.setTexture(m_tFondEc);
            m_typeMenu=MenuPrincipale;
        }
        else
        {

        }
    }
}

bool Menu::collisionTS(sf::FloatRect elem)
{
    bool collision=false;
    if((elem.left<sourisX && elem.left+elem.width>sourisX) && (elem.top<sourisY && elem.top+elem.height>sourisY))
    {
        collision=true;
    }
    return collision;
}

void Menu::retourMenuP()
{
    m_typeMenu=MenuPrincipale;
    m_sFondEc.setTexture(m_tFondEc);
    m_elementActif=AUCUN_EL_ACT;
}

TypeJeu Menu::getTypeJeu()
{
    return m_typeJeu;
}

Menu::~Menu()
{

}
