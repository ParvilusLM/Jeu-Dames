#include "info.h"



Info::Info(sf::RenderWindow &fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;
    m_tempsEcoule=0;
    reinitialiserH();
    demarrerH();

}

void Info::initInfo()
{
   m_etatH=EnPause;
   m_tCadre.loadFromFile("donnees/cadre.png");
   m_sCadre.setTexture(m_tCadre);
   m_sCadre.setPosition(600,0);

   m_fntTemps.loadFromFile("donnees/charlbold.ttf");
   m_fntAutre.loadFromFile("donnees/keypunc.ttf");

   m_txtTemps.setFont(m_fntTemps);
   m_txtTemps.setCharacterSize(40);
   m_txtTemps.setPosition(700,300);
   m_txtTemps.setFillColor(sf::Color::Black);
   gestionTemps();

   font_1.loadFromFile("donnees/MH.ttf");
    font_2.loadFromFile("donnees/MH_2.ttf");
    infoJeu.setFont(font_1);
    infoJeu.setCharacterSize(32);
    infoJeu.setPosition(620.f,20.f);
    infoJeu.setFillColor(sf::Color::White);

}

void Info::reinitInfo()
{
    reinitialiserH();
    demarrerH();
}

void Info::reinitialiserH()
{
    m_horloge.restart();
    pauseH();
    m_tempsEcoule=0.f;
}

void Info::demarrerH()
{
    if(m_etatH !=Demarre)
    {
        m_horloge.restart();
        m_etatH=Demarre;
    }
}

void Info::pauseH()
{
    if(m_etatH !=EnPause)
    {
        m_etatH=EnPause;
        m_tempsEcoule += m_horloge.getElapsedTime().asSeconds();
    }
}

float Info::getTemps()
{
    float temps;
    if(m_etatH == EnPause)
    {
        temps=m_tempsEcoule;
    }
    else
    {
        temps= m_horloge.getElapsedTime().asSeconds() + m_tempsEcoule;
    }

    return temps;
}



template <class T> std::string Info::nbEnString(T nb)
{
    std::ostringstream chaineCar;
    chaineCar << nb;
    return chaineCar.str();
}


void Info::gestionTemps()
{
    int temps=int(getTemps());
    std::ostringstream m_streamTxtTemps;
    m_streamTxtTemps.str("");
    m_streamTxtTemps<< nbEnString(temps/60) << " : "<< nbEnString(temps%60);

    m_txtTemps.setString(m_streamTxtTemps.str());
}


void Info::afficheInfo()
{
    m_fenetre->draw(m_sCadre);
    m_fenetre->draw(m_txtTemps);
    m_fenetre->draw(infoJeu);

}

void Info::maj_Info(TableJeu &table_jeu)
{
                  if(LA_MAIN)
                  {
                      etat_jB.str("");
                      etat_jB<<"actif";

                      etat_jR.str("");
                      etat_jR<<"passif";
                  }
                  else
                  {
                      etat_jB.str("");
                      etat_jB<<"passif";

                      etat_jR.str("");
                      etat_jR<<"actif";
                  }

                  //gestion de l'affichage des informations sur le jeu
                  stream_text.str("");
                  stream_text<<"       CPU"<<"\n\n"
                             <<"Nb Pions: "<<table_jeu.joueurs.at(0).pions.size()<<"\n"
                             <<"Nb Pions Captures: "<<12-table_jeu.joueurs.at(1).pions.size()<<"\n"
                             <<"Etat: "<< etat_jR.str()<<"\n\n\n\n\n\n\n\n"
                             <<"       Humain"<<"\n\n"
                             <<"Nb Pions: "<<table_jeu.joueurs.at(1).pions.size()<<"\n"
                             <<"Nb Pions Captures: "<<12-table_jeu.joueurs.at(0).pions.size()<<"\n"
                             <<"Etat: "<< etat_jB.str() ;

                 infoJeu.setString(stream_text.str());

}

Info::~Info()
{

}
