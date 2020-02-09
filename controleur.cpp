#include "controleur.h"


Controleur::Controleur(sf::RenderWindow &fenetre):m_fenetre(0),m_decor(0)
{
    m_fenetre=&fenetre;
    m_decor= new Decor(*m_fenetre);

}

void Controleur::debutJeu()
{
    fin_partie=false;
    std::cout<<"Entree dans la fonction Debut Jeu"<<std::endl;
    m_decor->CreationTableDeJeu();
    m_decor->InitInfo();
    m_decor->demarrerHorl();
    std::cout<<"Sortie dans la fonction Debut Jeu"<<std::endl;


}

void Controleur::retourMenu()
{
   m_decor->retourMenu();
   jeu_en_cours=false;
   ensembleCaseValide.clear();
   ensembleImCaseValide.clear();
   ensemblePionValide.clear();
   ensembleImPionValide.clear();
   m_decor->effacementTJ();

}

void Controleur::afficheMenu()
{
    m_decor->AfficherMenu();
}

void Controleur::afficheJeu()
{
    m_decor->Afficher();
}

void Controleur::demarrerHorl()
{
    m_decor->demarrerHorl();
}

void Controleur::compteurTemps()
{
    m_decor->compteurTemps();
}

void Controleur::gestionTour(int ind_J)
{
    int indic=ind_J;

    m_decor->gestionTour(indic);
    //Fin_Jeu();
}

void Controleur::gestionDplSouris()
{
    m_decor->gestionDplSouris();
}

void Controleur::gestionSelectionSouris()
{
    m_decor->gestionSelectionSouris();
}

void Controleur::Fin_Jeu()
{
    m_decor->Fin_Jeu();

    if(fin_partie)
    {
        ensembleCaseValide.clear();
        ensembleImCaseValide.clear();
        ensemblePionValide.clear();
        ensembleImPionValide.clear();
        m_decor->effacementTJ();
        m_decor->retourMenu();
        jeu_en_cours=false;

    }

}

Decor* Controleur::getDecor()
{
    return m_decor;
}

void Controleur::gestMajD()
{
    m_decor->gestMajD();

}

Controleur::~Controleur()
{
    delete m_decor;
}
