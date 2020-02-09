#include "decor.h"

Decor::Decor(sf::RenderWindow &fenetre):m_joueurC(0), m_menu(0),m_info(0)
{
    m_fenetre=&fenetre;
    m_joueurC=new JoueurC();
    m_menu=new Menu(*m_fenetre);
    m_info= new Info(*m_fenetre);


    t_im_gagne.loadFromFile("donnees/im_gagne.png");
    t_im_perdu.loadFromFile("donnees/im_perdu.png");


    t_tableDames.loadFromFile("donnees/table.png");

    t_pion_b.loadFromFile("donnees/pion_blanc.png");
    t_pion_b_d.loadFromFile("donnees/pion_b_dame.png");

    t_pion_r.loadFromFile("donnees/pion_rouge.png");
    t_pion_r_d.loadFromFile("donnees/pion_r_dame.png");

    t_indic_selection.loadFromFile("donnees/masque_vert.png");
    t_masquePionCDC.loadFromFile("donnees/masque_jaune.png");

    s_indic_selection.setTexture(t_indic_selection);
    s_indic_selection.setOrigin(37.5,37.5);


    s_masquePionCDC.setTexture(t_masquePionCDC);
    s_masquePionCDC.setOrigin(37.5,37.5);
}


void Decor::CreationTableDeJeu()
{
    Joueur m_joueur1=m_joueurC->getJoueur(1);
    Joueur m_joueur2=m_joueurC->getJoueur(2);

    m_tableJeu.joueurs.insert(m_tableJeu.joueurs.end(),m_joueur1);
    m_tableJeu.joueurs.insert(m_tableJeu.joueurs.end(),m_joueur2);


    PositionInitialPions();
    SelectionTextures();
}

void Decor::PositionInitialPions()
{
    //position des pions du m_joueurC->m_joueur_1 sur la table
    m_tableJeu.joueurs.at(0).pions.at(0).s_pion.setPosition(75*col_B+37.5,75*rang_1+37.5);
    m_tableJeu.joueurs.at(0).pions.at(1).s_pion.setPosition(75*col_D+37.5,75*rang_1+37.5);
    m_tableJeu.joueurs.at(0).pions.at(2).s_pion.setPosition(75*col_F+37.5,75*rang_1+37.5);
    m_tableJeu.joueurs.at(0).pions.at(3).s_pion.setPosition(75*col_H+37.5,75*rang_1+37.5);
    m_tableJeu.joueurs.at(0).pions.at(4).s_pion.setPosition(75*col_A+37.5,75*rang_2+37.5);
    m_tableJeu.joueurs.at(0).pions.at(5).s_pion.setPosition(75*col_C+37.5,75*rang_2+37.5);//rang2
    m_tableJeu.joueurs.at(0).pions.at(6).s_pion.setPosition(75*col_E+37.5,75*rang_2+37.5);
    m_tableJeu.joueurs.at(0).pions.at(7).s_pion.setPosition(75*col_G+37.5,75*rang_2+37.5);//col H rang2
    m_tableJeu.joueurs.at(0).pions.at(8).s_pion.setPosition(75*col_B+37.5,75*rang_3+37.5);
    m_tableJeu.joueurs.at(0).pions.at(9).s_pion.setPosition(75*col_D+37.5,75*rang_3+37.5);
    m_tableJeu.joueurs.at(0).pions.at(10).s_pion.setPosition(75*col_F+37.5,75*rang_3+37.5);
    m_tableJeu.joueurs.at(0).pions.at(11).s_pion.setPosition(75*col_H+37.5,75*rang_3+37.5);//rang_3

    //position des pions du m_joueurC->m_joueur_2 sur la table
    m_tableJeu.joueurs.at(1).pions.at(0).s_pion.setPosition(75*col_A+37.5,75*rang_8+37.5);
    m_tableJeu.joueurs.at(1).pions.at(1).s_pion.setPosition(75*col_C+37.5,75*rang_8+37.5);
    m_tableJeu.joueurs.at(1).pions.at(2).s_pion.setPosition(75*col_E+37.5,75*rang_8+37.5);
    m_tableJeu.joueurs.at(1).pions.at(3).s_pion.setPosition(75*col_G+37.5,75*rang_8+37.5);
    m_tableJeu.joueurs.at(1).pions.at(4).s_pion.setPosition(75*col_B+37.5,75*rang_7+37.5);
    m_tableJeu.joueurs.at(1).pions.at(5).s_pion.setPosition(75*col_D+37.5,75*rang_7+37.5);
    m_tableJeu.joueurs.at(1).pions.at(6).s_pion.setPosition(75*col_F+37.5,75*rang_7+37.5);
    m_tableJeu.joueurs.at(1).pions.at(7).s_pion.setPosition(75*col_H+37.5,75*rang_7+37.5);
    m_tableJeu.joueurs.at(1).pions.at(8).s_pion.setPosition(75*col_A+37.5,75*rang_6+37.5);
    m_tableJeu.joueurs.at(1).pions.at(9).s_pion.setPosition(75*col_C+37.5,75*rang_6+37.5);
    m_tableJeu.joueurs.at(1).pions.at(10).s_pion.setPosition(75*col_E+37.5,75*rang_6+37.5);
    m_tableJeu.joueurs.at(1).pions.at(11).s_pion.setPosition(75*col_G+37.5,75*rang_6+37.5);
}

void Decor::SelectionTextures()
 {
   //table jeu
   m_tableJeu.s_tableDeJeu.setTexture(t_tableDames);

   int cmpt=0;
     while(cmpt<m_tableJeu.joueurs.size())
     {
         int cmpt2=0;
        while(cmpt2<m_tableJeu.joueurs.at(cmpt).pions.size())
        {
            if(m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).type_pion==pion_R)
           {
             m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).s_pion.setTexture(t_pion_r);
           }

           if(m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).type_pion==pion_R_D)
           {
              m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).s_pion.setTexture(t_pion_r_d);
           }

           if(m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).type_pion==pion_B)
           {
             m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).s_pion.setTexture(t_pion_b);
           }

           if(m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).type_pion==pion_B_D)
           {
              m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).s_pion.setTexture(t_pion_b_d);
           }


            cmpt2++;
        }
        cmpt++;
     }
 }


bool Decor::MarquagePionCapDeCap()
{
    bool possible=false;
    ensemblePionValide.clear();

    //
    int compt=0;
    while(compt<m_tableJeu.joueurs.at(1).pions.size())
    {
        if(m_tableJeu.joueurs.at(1).pions.at(compt).type_pion==pion_B)
        {
            bool m_droite=false;
            bool m_gauche=false;



                     sf::Vector2f posInitialPion;
                     posInitialPion.x=m_tableJeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().x;
                     posInitialPion.y=m_tableJeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().y;

                     int posEnCaseX=posInitialPion.x/75;
                     int posEnCaseY=posInitialPion.y/75;

                     if(!m_gauche && posEnCaseX>1 && posEnCaseY>1)
                     {

                             bool prem_case=false;
                             bool deux_case=false;

                             int compt_1=0;
                             while(compt_1<m_tableJeu.joueurs.at(0).pions.size())
                             {

                                 int posX=posEnCaseX-1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                                 {

                                     prem_case=true;
                                 }

                                 compt_1++;
                             }

                            int compt_2=0;
                             while(compt_2<m_tableJeu.joueurs.at(1).pions.size())
                             {
                                 int posX=posEnCaseX-1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=false;
                                 }

                                 compt_2++;
                             }


                             int compt3=0;
                             while(compt3<m_tableJeu.joueurs.size())
                             {
                                 int compt4=0;
                                 while(compt4<m_tableJeu.joueurs.at(compt3).pions.size())
                                 {
                                     int posX=posEnCaseX-2;
                                     int posY=posEnCaseY-2;

                                 if(m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     deux_case=true;
                                 }

                                     compt4++;
                                 }

                                 compt3++;
                             }

                             if(prem_case && !deux_case)
                             {
                                 m_gauche=true;
                             }





                     }


                     if(!m_droite && posEnCaseX<6 && posEnCaseY>1)
                     {
                             bool prem_case=false;
                             bool deux_case=false;

                             int compt_1=0;
                             while(compt_1<m_tableJeu.joueurs.at(0).pions.size())
                             {
                                 int posX=posEnCaseX+1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=true;
                                 }

                                 compt_1++;
                             }

                            int compt_2=0;
                             while(compt_2<m_tableJeu.joueurs.at(1).pions.size())
                             {
                                 int posX=posEnCaseX+1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=false;
                                 }

                                 compt_2++;
                             }

                             int compt3=0;
                             while(compt3<m_tableJeu.joueurs.size())
                             {
                                 int compt4=0;
                                 while(compt4<m_tableJeu.joueurs.at(compt3).pions.size())
                                 {
                                     int posX=posEnCaseX+2;
                                     int posY=posEnCaseY-2;

                                 if(m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     deux_case=true;
                                 }

                                     compt4++;
                                 }

                                 compt3++;
                             }

                             if(prem_case && !deux_case)
                             {
                                 m_droite=true;
                             }




                     }


                if(m_droite || m_gauche)
                {
                    sf::Vector2f nouvelCoordPion;
                    nouvelCoordPion.x=posEnCaseX;
                    nouvelCoordPion.y=posEnCaseY;
                    h_capture=true;

                    ensemblePionValide.insert(ensemblePionValide.end(),nouvelCoordPion);
                }
        }

        if(m_tableJeu.joueurs.at(1).pions.at(compt).type_pion==pion_B_D)
        {
            bool m_droite=false;
            bool m_gauche=false;
            bool m_bas_gauche=false;
            bool m_bas_droite=false;



                     sf::Vector2f posInitialPion;
                     posInitialPion.x=m_tableJeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().x;
                     posInitialPion.y=m_tableJeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().y;

                     int posEnCaseX=posInitialPion.x/75;
                     int posEnCaseY=posInitialPion.y/75;


                     if(!m_gauche && posEnCaseX>1 && posEnCaseY>1)
                     {
                             bool prem_case=false;
                             bool deux_case=false;

                             int compt_1=0;
                             while(compt_1<m_tableJeu.joueurs.at(0).pions.size())
                             {

                                 int posX=posEnCaseX-1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=true;
                                 }

                                 compt_1++;
                             }

                            int compt_2=0;
                             while(compt_2<m_tableJeu.joueurs.at(1).pions.size())
                             {
                                 int posX=posEnCaseX-1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=false;
                                 }

                                 compt_2++;
                             }


                             int compt3=0;
                             while(compt3<m_tableJeu.joueurs.size())
                             {
                                 int compt4=0;
                                 while(compt4<m_tableJeu.joueurs.at(compt3).pions.size())
                                 {
                                     int posX=posEnCaseX-2;
                                     int posY=posEnCaseY-2;

                                 if(m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     deux_case=true;
                                 }

                                     compt4++;
                                 }

                                 compt3++;
                             }

                             if(prem_case && !deux_case)
                             {
                                 m_gauche=true;
                             }




                     }


                     if(!m_droite && posEnCaseX<6 && posEnCaseY>1)
                     {

                             bool prem_case=false;
                             bool deux_case=false;

                             int compt_1=0;
                             while(compt_1<m_tableJeu.joueurs.at(0).pions.size())
                             {
                                 int posX=posEnCaseX+1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=true;
                                 }

                                 compt_1++;
                             }

                            int compt_2=0;
                             while(compt_2<m_tableJeu.joueurs.at(1).pions.size())
                             {
                                 int posX=posEnCaseX+1;
                                 int posY=posEnCaseY-1;

                                 if(m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=false;
                                 }

                                 compt_2++;
                             }

                             int compt3=0;
                             while(compt3<m_tableJeu.joueurs.size())
                             {
                                 int compt4=0;
                                 while(compt4<m_tableJeu.joueurs.at(compt3).pions.size())
                                 {
                                     int posX=posEnCaseX+2;
                                     int posY=posEnCaseY-2;

                                 if(m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     deux_case=true;
                                 }

                                     compt4++;
                                 }

                                 compt3++;
                             }

                             if(prem_case && !deux_case)
                             {
                                 m_droite=true;
                             }




                     }


                     if(!m_bas_gauche && posEnCaseX>1 && posEnCaseY<6)
                     {

                             bool prem_case=false;
                             bool deux_case=false;

                             int compt_1=0;
                             while(compt_1<m_tableJeu.joueurs.at(0).pions.size())
                             {

                                 int posX=posEnCaseX-1;
                                 int posY=posEnCaseY+1;

                                 if(m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=true;
                                 }

                                 compt_1++;
                             }

                            int compt_2=0;
                             while(compt_2<m_tableJeu.joueurs.at(1).pions.size())
                             {
                                 int posX=posEnCaseX-1;
                                 int posY=posEnCaseY+1;

                                 if(m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=false;
                                 }

                                 compt_2++;
                             }


                             int compt3=0;
                             while(compt3<m_tableJeu.joueurs.size())
                             {
                                 int compt4=0;
                                 while(compt4<m_tableJeu.joueurs.at(compt3).pions.size())
                                 {
                                     int posX=posEnCaseX-2;
                                     int posY=posEnCaseY+2;

                                 if(m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     deux_case=true;
                                 }

                                     compt4++;
                                 }

                                 compt3++;
                             }

                             if(prem_case && !deux_case)
                             {
                                 m_bas_gauche=true;
                             }




                     }


                     if(!m_bas_droite && posEnCaseX<6 && posEnCaseY<6)
                     {

                             bool prem_case=false;
                             bool deux_case=false;

                             int compt_1=0;
                             while(compt_1<m_tableJeu.joueurs.at(0).pions.size())
                             {
                                 int posX=posEnCaseX+1;
                                 int posY=posEnCaseY+1;

                                 if(m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=true;
                                 }

                                 compt_1++;
                             }

                            int compt_2=0;
                             while(compt_2<m_tableJeu.joueurs.at(1).pions.size())
                             {
                                 int posX=posEnCaseX+1;
                                 int posY=posEnCaseY+1;

                                 if(m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     prem_case=false;
                                 }

                                 compt_2++;
                             }

                             int compt3=0;
                             while(compt3<m_tableJeu.joueurs.size())
                             {
                                 int compt4=0;
                                 while(compt4<m_tableJeu.joueurs.at(compt3).pions.size())
                                 {
                                     int posX=posEnCaseX+2;
                                     int posY=posEnCaseY+2;

                                 if(m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                 {
                                     deux_case=true;
                                 }

                                     compt4++;
                                 }

                                 compt3++;
                             }

                             if(prem_case && !deux_case)
                             {
                                 m_bas_droite=true;
                             }




                     }


                if(m_droite || m_gauche || m_bas_gauche || m_bas_droite)
                {
                    sf::Vector2f nouvelCoordPion;
                    nouvelCoordPion.x=posEnCaseX;
                    nouvelCoordPion.y=posEnCaseY;
                    h_capture=true;

                    ensemblePionValide.insert(ensemblePionValide.end(),nouvelCoordPion);
                }
        }

        compt++;
    }
}

void Decor::MarquagePionCapDeDepl()
{
    int compt=0;
    while(compt<m_tableJeu.joueurs.at(1).pions.size())
    {
        int posInitP_X=m_tableJeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().x/75;
        int posInitP_Y=m_tableJeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().y/75;

        if(m_tableJeu.joueurs.at(1).pions.at(compt).type_pion==pion_B)
        {
            bool m_h_g=false;
            bool m_h_d=false;

            if(!m_h_g && posInitP_X>0 && posInitP_Y>0)
            {
                m_h_g=true;
                int posX=posInitP_X-1;
                int posY=posInitP_Y-1;

                int comp=0;
                while(comp<m_tableJeu.joueurs.size())
                {
                    int comp2=0;
                    while(comp2<m_tableJeu.joueurs.at(comp).pions.size())
                    {
                        if(m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().y==posY*75+37.5)
                        {
                            m_h_g=false;
                        }
                        comp2++;
                    }
                    comp++;
                }

            }

            if(!m_h_d && posInitP_X<7 && posInitP_Y>0)
            {
                m_h_d=true;
                int posX=posInitP_X+1;
                int posY=posInitP_Y-1;

                int comp=0;
                while(comp<m_tableJeu.joueurs.size())
                {
                    int comp2=0;
                    while(comp2<m_tableJeu.joueurs.at(comp).pions.size())
                    {
                        if(m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().y==posY*75+37.5)
                        {
                            m_h_d=false;
                        }
                        comp2++;
                    }
                    comp++;
                }
            }

            if(m_h_g || m_h_d)
            {
                sf::Vector2f nouvel_pos;
                nouvel_pos.x=posInitP_X;
                nouvel_pos.y=posInitP_Y;

                ensemblePCapDeDepl.insert(ensemblePCapDeDepl.end(),nouvel_pos);
                h_deplacem=true;
            }


        }

        if(m_tableJeu.joueurs.at(1).pions.at(compt).type_pion==pion_B_D)
        {
            bool m_h_g=false;
            bool m_h_d=false;
            bool m_b_g=false;
            bool m_b_d=false;

            if(!m_h_g && posInitP_X>0 && posInitP_Y>0)
            {
                m_h_g=true;
                int posX=posInitP_X-1;
                int posY=posInitP_Y-1;

                int comp=0;
                while(comp<m_tableJeu.joueurs.size())
                {
                    int comp2=0;
                    while(comp2<m_tableJeu.joueurs.at(comp).pions.size())
                    {
                        if(m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().y==posY*75+37.5)
                        {
                            m_h_g=false;
                        }
                        comp2++;
                    }
                    comp++;
                }

            }

            if(!m_h_d && posInitP_X<7 && posInitP_Y>0)
            {
                m_h_d=true;
                int posX=posInitP_X+1;
                int posY=posInitP_Y-1;

                int comp=0;
                while(comp<m_tableJeu.joueurs.size())
                {
                    int comp2=0;
                    while(comp2<m_tableJeu.joueurs.at(comp).pions.size())
                    {
                        if(m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().y==posY*75+37.5)
                        {
                            m_h_d=false;
                        }
                        comp2++;
                    }
                    comp++;
                }
            }

            if(!m_b_g && posInitP_X>0 && posInitP_Y<7)
            {
                m_b_g=true;
                int posX=posInitP_X-1;
                int posY=posInitP_Y+1;

                int comp=0;
                while(comp<m_tableJeu.joueurs.size())
                {
                    int comp2=0;
                    while(comp2<m_tableJeu.joueurs.at(comp).pions.size())
                    {
                        if(m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().y==posY*75+37.5)
                        {
                            m_b_g=false;
                        }
                        comp2++;
                    }
                    comp++;
                }

            }

            if(!m_b_d && posInitP_X<7 && posInitP_Y<7)
            {
                m_b_d=true;
                int posX=posInitP_X+1;
                int posY=posInitP_Y+1;

                int comp=0;
                while(comp<m_tableJeu.joueurs.size())
                {
                    int comp2=0;
                    while(comp2<m_tableJeu.joueurs.at(comp).pions.size())
                    {
                        if(m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().x==posX*75+37.5 && m_tableJeu.joueurs.at(comp).pions.at(comp2).s_pion.getPosition().y==posY*75+37.5)
                        {
                            m_b_d=false;
                        }
                        comp2++;
                    }
                    comp++;
                }
            }


            if(m_h_g || m_h_d || m_b_g || m_b_d)
            {
                sf::Vector2f nouvel_pos;
                nouvel_pos.x=posInitP_X;
                nouvel_pos.y=posInitP_Y;

                ensemblePCapDeDepl.insert(ensemblePCapDeDepl.end(),nouvel_pos);
                h_deplacem=true;
            }


        }



        compt++;
    }
}

bool Decor::MarquageCaseValide()
{
    bool possible=false;

    std::vector<sf::Vector2f> posEnsembleCaseVal;

    int comptt=0;
    while(comptt<m_tableJeu.joueurs.at(1).pions.size())
    {
        if(m_tableJeu.joueurs.at(1).pions.at(comptt).selectionne)
        {
            //initialisation du tableau virtuel
            int tableau_virtuel[8][8]={0};

            int compt=0;
            while(compt<m_tableJeu.joueurs.size())
            {
                int compt2=0;
                while(compt2<m_tableJeu.joueurs.at(compt).pions.size())
                {
                    //Position du pion dans le tableau virtuel
                    int posx=m_tableJeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x/75;
                    int posy=m_tableJeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y/75;

                    if(m_tableJeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B)
                    {
                        if(m_tableJeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                        {
                            tableau_virtuel[posx][posy]=1;
                        }
                        else
                        {
                            tableau_virtuel[posx][posy]=-1;
                        }
                    }

                    if(m_tableJeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B_D)
                    {
                        if(m_tableJeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                        {
                            tableau_virtuel[posx][posy]=1;
                        }
                        else
                        {
                            tableau_virtuel[posx][posy]=-1;
                        }
                    }

                    if(m_tableJeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R)
                    {
                            tableau_virtuel[posx][posy]=-2;
                    }

                    if(m_tableJeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R_D)
                    {
                            tableau_virtuel[posx][posy]=-2;
                    }


                    compt2++;
                }

                compt++;
            }

            int val_a_verif=1;

            int n_chemins=1;
            int n_chemins_term=0;

            if(m_tableJeu.joueurs.at(1).pions.at(comptt).type_pion==pion_B)
            {
                   int compteur2=0;
                   while(compteur2<1)
                   {
                       //boucle dans le tableau virtuel pour trouver la valeur a tester
                       int compteur3=0;
                       while(compteur3<8)
                       {
                           int compteur4=0;
                           while(compteur4<8)
                           {

                               if(tableau_virtuel[compteur3][compteur4]==val_a_verif)
                               {
                                   bool dir_gauche=false;
                                   bool dir_droite=false;


                                   //conditions pour savoir la direction que peut prendre le pion
                                   if(compteur3>1 && compteur4>1)
                                   {
                                         if(tableau_virtuel[compteur3-1][compteur4-1]==-2 && tableau_virtuel[compteur3-2][compteur4-2]>-1 && tableau_virtuel[compteur3-2][compteur4-2]<val_a_verif+1)
                                         {
                                             dir_gauche=true;
                                         }
                                   }


                                   if(compteur3<6 && compteur4>1)
                                   {
                                       if(tableau_virtuel[compteur3+1][compteur4-1]==-2 && tableau_virtuel[compteur3+2][compteur4-2]>-1 && tableau_virtuel[compteur3+2][compteur4-2]<val_a_verif+1)
                                       {
                                           dir_droite=true;
                                       }
                                   }

                                   //.......

                                   if(dir_gauche && !dir_droite)
                                   {
                                       if(tableau_virtuel[compteur3-2][compteur4-2]<val_a_verif+1)
                                       {
                                           tableau_virtuel[compteur3-2][compteur4-2]=val_a_verif+1;

                                       }

                                   }

                                   if(!dir_gauche && dir_droite)
                                   {
                                       if(tableau_virtuel[compteur3+2][compteur4-2]<val_a_verif+1)
                                       {
                                           tableau_virtuel[compteur3+2][compteur4-2]=val_a_verif+1;

                                       }

                                   }

                                   if(dir_gauche && dir_droite)
                                   {
                                       if(tableau_virtuel[compteur3-2][compteur4-2]<val_a_verif+1)
                                       {
                                           tableau_virtuel[compteur3-2][compteur4-2]=val_a_verif+1;
                                       }


                                       if(tableau_virtuel[compteur3+2][compteur4-2]<val_a_verif+1)
                                       {
                                           tableau_virtuel[compteur3+2][compteur4-2]=val_a_verif+1;
                                       }


                                      n_chemins++;
                                   }

                                   if(!dir_gauche && !dir_droite)
                                   {
                                       n_chemins_term++;
                                   }


                               }


                               compteur4++;
                           }

                            compteur3++;
                       }


                       if(n_chemins==n_chemins_term)
                       {
                           compteur2++;
                       }
                       else
                        val_a_verif++;

                   }

            }

            if(m_tableJeu.joueurs.at(1).pions.at(comptt).type_pion==pion_B_D)
            {
                // vecteur representant l'ensemble des cases des differents chemins
                std::vector<CaseValabe> eChemin;

                //vecteur pour stocker les cases a tester
                std::vector<CaseValabe> eCasesATester;

                //boucle semi-infinie
                int compt2=0;
                while(compt2<1)
                {
                    if(val_a_verif==1)
                    {
                        CaseValabe eCase;
                        eCase.valeur_chemin=1;

                        int compt3=0;
                        while(compt3<8)
                        {
                            int compt4=0;
                            while(compt4<8)
                            {
                                if(tableau_virtuel[compt3][compt4]==1)
                                {
                                    eCase.positionX=compt3;
                                    eCase.positionY=compt4;
                                }

                                compt4++;
                            }
                            compt3++;
                        }

                        eCase.lien_ch_precd=0;
                        eCase.num_chem=1;

                        eCase.i_d_h_g=false;
                        eCase.i_d_h_d=false;
                        eCase.i_d_b_g=false;
                        eCase.i_d_b_d=false;

                        eChemin.insert(eChemin.end(),eCase);
                    }

                    //variable pour savoir le nombre de cases qu'on va tester
                    int no_chemin=0;

                    //initialisation de la variable no_chemin
                    int compt3=0;
                    while(compt3<8)
                    {
                        int compt4=0;
                        while(compt4<8)
                        {
                            if(tableau_virtuel[compt3][compt4]==val_a_verif)
                            {
                                no_chemin++;
                            }
                            compt4++;
                        }
                        compt3++;
                    }

                    //stockage des cases a tester dans le vecteur eCaseATester
                    eCasesATester.clear();
                    int pseudo_no_ch=0;
                    int comp=0;
                    while(comp<no_chemin)
                    {
                        int dern_ind=eChemin.size()-1;

                        eCasesATester.insert(eCasesATester.end(),eChemin.at(dern_ind-pseudo_no_ch));
                        pseudo_no_ch++;
                        comp++;
                    }


                    //boucle dans le tableau virtuel pour tester les cases correspondant a val_a_verif
                    int compt4=0;
                    while(compt4<8)
                    {
                        int compt5=0;
                        while(compt5<8)
                        {
                            if(tableau_virtuel[compt4][compt5]==val_a_verif)
                            {
                                bool dir_haut_g=false;
                                bool dir_haut_d=false;
                                bool dir_bas_g=false;
                                bool dir_bas_d=false;

                                //choix de la case active dans eCaseATester
                                int no_case_eCaseATester=0;
                                int commp=0;
                                while(commp<eCasesATester.size())
                                {
                                    if(eCasesATester.at(commp).positionX==compt4 && eCasesATester.at(commp).positionY==compt5)
                                    {
                                        no_case_eCaseATester=commp;
                                    }
                                    commp++;
                                }



                                //condition pour savoir quelle direction que peut prendre la dame en haut
                                if(compt4>1 && compt5>1)
                                {
                                    if(tableau_virtuel[compt4-1][compt5-1]==-2 && tableau_virtuel[compt4-2][compt5-2]>-1 && tableau_virtuel[compt4-2][compt5-2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_h_g)
                                    {
                                        dir_haut_g=true;
                                    }
                                }

                                if(compt4<6 && compt5>1)
                                {
                                    if(tableau_virtuel[compt4+1][compt5-1]==-2 && tableau_virtuel[compt4+2][compt5-2]>-1 && tableau_virtuel[compt4+2][compt5-2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_h_d)
                                    {
                                        dir_haut_d=true;
                                    }
                                }

                                //condition pour savoir quelle direction que peut prendre la dame en bas
                                if(compt4>1 && compt5<6)
                                {
                                    if(tableau_virtuel[compt4-1][compt5+1]==-2 && tableau_virtuel[compt4-2][compt5+2]>-1 && tableau_virtuel[compt4-2][compt5+2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_b_g)
                                    {
                                        dir_bas_g=true;
                                    }
                                }

                                if(compt4<6 && compt5<6)
                                {
                                    if(tableau_virtuel[compt4+1][compt5+1]==-2 && tableau_virtuel[compt4+2][compt5+2]>-1 && tableau_virtuel[compt4+2][compt5+2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_b_d)
                                    {
                                        dir_bas_d=true;
                                    }
                                }

                                //
                                //1
                                if(dir_haut_g && !dir_haut_d && !dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);
                                }

                                //2
                                if(!dir_haut_g && dir_haut_d && !dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4+2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=true;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=true;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);
                                }

                                //3
                                if(!dir_haut_g && !dir_haut_d && dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5+2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=true;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=true;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);
                                }

                                //4
                                if(!dir_haut_g && !dir_haut_d && !dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4+2;
                                    eCase.positionY=compt5+2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=true;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase);
                                }

                                //5
                                if(dir_haut_g && dir_haut_d && !dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4+2;
                                    eCase2.positionY=compt5-2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=false;
                                    eCase2.i_d_b_g=true;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=true;
                                    eCase2.mouv_b_g=false;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    n_chemins++;
                                }

                                //6
                                if(dir_haut_g && !dir_haut_d && dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4-2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=true;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=true;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    n_chemins++;
                                }

                                //7
                                if(dir_haut_g && !dir_haut_d && !dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4+2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=true;
                                    eCase2.i_d_h_d=false;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=false;
                                    eCase2.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    n_chemins++;
                                }

                                //8
                                if(!dir_haut_g && dir_haut_d && dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4+2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=true;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=true;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4-2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=true;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=true;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    n_chemins++;
                                }

                                //9
                                if(!dir_haut_g && dir_haut_d && !dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4+2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=true;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=true;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4+2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=true;
                                    eCase2.i_d_h_d=false;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=false;
                                    eCase2.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    n_chemins++;
                                }

                                //10
                                if(!dir_haut_g && !dir_haut_d && dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5+2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=true;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=true;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4+2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=true;
                                    eCase2.i_d_h_d=false;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=false;
                                    eCase2.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    n_chemins++;
                                }

                                //11
                                if(dir_haut_g && dir_haut_d && dir_bas_g && !dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4+2;
                                    eCase2.positionY=compt5-2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=false;
                                    eCase2.i_d_b_g=true;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=true;
                                    eCase2.mouv_b_g=false;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase3;
                                    eCase3.positionX=compt4-2;
                                    eCase3.positionY=compt5+2;
                                    eCase3.valeur_chemin=val_a_verif+1;
                                    eCase3.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase3.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+2;

                                    eCase3.i_d_h_g=false;
                                    eCase3.i_d_h_d=true;
                                    eCase3.i_d_b_g=false;
                                    eCase3.i_d_b_d=false;

                                    eCase3.mouv_h_g=false;
                                    eCase3.mouv_h_d=false;
                                    eCase3.mouv_b_g=true;
                                    eCase3.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase3);

                                    n_chemins+=2;
                                }

                                //12
                                if(dir_haut_g && dir_haut_d && !dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4+2;
                                    eCase2.positionY=compt5-2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=false;
                                    eCase2.i_d_b_g=true;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=true;
                                    eCase2.mouv_b_g=false;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase3;
                                    eCase3.positionX=compt4+2;
                                    eCase3.positionY=compt5+2;
                                    eCase3.valeur_chemin=val_a_verif+1;
                                    eCase3.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase3.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+2;

                                    eCase3.i_d_h_g=true;
                                    eCase3.i_d_h_d=false;
                                    eCase3.i_d_b_g=false;
                                    eCase3.i_d_b_d=false;

                                    eCase3.mouv_h_g=false;
                                    eCase3.mouv_h_d=false;
                                    eCase3.mouv_b_g=false;
                                    eCase3.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase3);

                                    n_chemins+=2;
                                }

                                //13
                                if(dir_haut_g && !dir_haut_d && dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4-2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4-2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=false;
                                    eCase.i_d_b_d=true;

                                    eCase.mouv_h_g=true;
                                    eCase.mouv_h_d=false;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4-2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=true;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=true;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase3;
                                    eCase3.positionX=compt4+2;
                                    eCase3.positionY=compt5+2;
                                    eCase3.valeur_chemin=val_a_verif+1;
                                    eCase3.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase3.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+2;

                                    eCase3.i_d_h_g=true;
                                    eCase3.i_d_h_d=false;
                                    eCase3.i_d_b_g=false;
                                    eCase3.i_d_b_d=false;

                                    eCase3.mouv_h_g=false;
                                    eCase3.mouv_h_d=false;
                                    eCase3.mouv_b_g=false;
                                    eCase3.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase3);

                                    n_chemins+=2;
                                }

                                //14
                                if(!dir_haut_g && dir_haut_d && dir_bas_g && dir_bas_d)
                                {
                                    tableau_virtuel[compt4+2][compt5-2]=val_a_verif+1;

                                    CaseValabe eCase;
                                    eCase.positionX=compt4+2;
                                    eCase.positionY=compt5-2;
                                    eCase.valeur_chemin=val_a_verif+1;
                                    eCase.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem;

                                    eCase.i_d_h_g=false;
                                    eCase.i_d_h_d=false;
                                    eCase.i_d_b_g=true;
                                    eCase.i_d_b_d=false;

                                    eCase.mouv_h_g=false;
                                    eCase.mouv_h_d=true;
                                    eCase.mouv_b_g=false;
                                    eCase.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase);

                                    tableau_virtuel[compt4-2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase2;
                                    eCase2.positionX=compt4-2;
                                    eCase2.positionY=compt5+2;
                                    eCase2.valeur_chemin=val_a_verif+1;
                                    eCase2.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase2.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+1;

                                    eCase2.i_d_h_g=false;
                                    eCase2.i_d_h_d=true;
                                    eCase2.i_d_b_g=false;
                                    eCase2.i_d_b_d=false;

                                    eCase2.mouv_h_g=false;
                                    eCase2.mouv_h_d=false;
                                    eCase2.mouv_b_g=true;
                                    eCase2.mouv_b_d=false;

                                    eChemin.insert(eChemin.end(),eCase2);

                                    tableau_virtuel[compt4+2][compt5+2]=val_a_verif+1;

                                    CaseValabe eCase3;
                                    eCase3.positionX=compt4+2;
                                    eCase3.positionY=compt5+2;
                                    eCase3.valeur_chemin=val_a_verif+1;
                                    eCase3.lien_ch_precd=eCasesATester.at(no_case_eCaseATester).num_chem;
                                    eCase3.num_chem=eCasesATester.at(no_case_eCaseATester).num_chem+2;

                                    eCase3.i_d_h_g=true;
                                    eCase3.i_d_h_d=false;
                                    eCase3.i_d_b_g=false;
                                    eCase3.i_d_b_d=false;

                                    eCase3.mouv_h_g=false;
                                    eCase3.mouv_h_d=false;
                                    eCase3.mouv_b_g=false;
                                    eCase3.mouv_b_d=true;

                                    eChemin.insert(eChemin.end(),eCase3);

                                    n_chemins+=2;
                                }

                                //15
                                if(!dir_haut_g && !dir_haut_d && !dir_bas_g && !dir_bas_d)
                                {
                                    n_chemins_term++;
                                }

                                //pseudo_comp++;
                            }
                            compt5++;
                        }
                        compt4++;
                    }

                    if(n_chemins==n_chemins_term)
                    {
                       compt2++;
                    }
                    else
                    {
                        val_a_verif++;
                    }

                }

            }

            // insertion des coordonnees des cases valide dans posEnsemCasesValid

                   int compt2=0;
                   while(compt2<8)
                   {
                       int compt3=0;
                       while(compt3<8)
                       {
                           if(tableau_virtuel[compt2][compt3]==val_a_verif && val_a_verif!=1)
                           {
                              sf::Vector2f nouvelCoord;
                              nouvelCoord.x=compt2;
                              nouvelCoord.y=compt3;

                              posEnsembleCaseVal.insert(posEnsembleCaseVal.end(),nouvelCoord);
                           }

                           compt3++;
                       }

                       compt2++;
                   }

                   ensembleCaseValide.clear();
                   if(posEnsembleCaseVal.size()!=0)
                   {
                       ensembleCaseValide.insert(ensembleCaseValide.end(),posEnsembleCaseVal.begin(),posEnsembleCaseVal.end());
                   }

        }

        comptt++;

    }
}

void Decor::AfficherMenu()
{
     m_menu->affficheMenu();
}

void Decor::Afficher()
 {

         SelectionTextures();

         m_fenetre->draw(m_tableJeu.s_tableDeJeu);

         int cmpt=0;
         while(cmpt<m_tableJeu.joueurs.size())
         {
             int cmpt2=0;
            while(cmpt2<m_tableJeu.joueurs.at(cmpt).pions.size())
            {
                m_fenetre->draw(m_tableJeu.joueurs.at(cmpt).pions.at(cmpt2).s_pion);
                cmpt2++;
            }
            cmpt++;
         }

         if(selec_valide)
         {
             m_fenetre->draw(s_indic_selection);

             int compt=0;
             while(compt<ensembleImCaseValide.size())
             {
                 m_fenetre->draw(ensembleImCaseValide.at(compt));
                 compt++;
             }
         }

         if(!selec_valide && LA_MAIN)
         {
             int compt=0;
             while(compt<ensembleImPionValide.size())
             {
                 m_fenetre->draw(ensembleImPionValide.at(compt));
                 compt++;
             }
         }


         m_info->afficheInfo();






 }

 void Decor::effacementTJ()
 {
     m_tableJeu.joueurs.clear();
 }

void Decor::gestIndicateurP()
{
      if(!selec_valide && LA_MAIN)
      {
          ensembleImPionValide.clear();
          MarquagePionCapDeCap();

          //on met les coordonnees de ensemblePionValide dans un vecteur de sprite
          if(ensemblePionValide.size()!=0)
          {
              int compt=0;
              while(compt<ensemblePionValide.size())
              {

                  s_masquePionCDC.setPosition(ensemblePionValide.at(compt).x*75+37.5,ensemblePionValide.at(compt).y*75+37.5);

                  ensembleImPionValide.insert(ensembleImPionValide.end(),s_masquePionCDC);

                  compt++;
              }

          }

      }
      else
        ensembleImPionValide.clear();


      if(!selec_valide && LA_MAIN && !h_capture)
      {
          ensemblePCapDeDepl.clear();
          MarquagePionCapDeDepl();
      }

      if(selec_valide && LA_MAIN)
      {
          ensembleImCaseValide.clear();
          MarquageCaseValide();

          //on met les coord de ensembleCaseValide dans ensembleImCaseValid
          if(ensembleCaseValide.size()!=0)
          {
              int compt=0;
              while(compt<ensembleCaseValide.size())
              {
                  s_masquePionCDC.setPosition(ensembleCaseValide.at(compt).x*75+37.5,ensembleCaseValide.at(compt).y*75+37.5);
                  ensembleImCaseValide.insert(ensembleImCaseValide.end(),s_masquePionCDC);
                  compt++;
              }
          }
      }
      else
        ensembleImCaseValide.clear();

}


void Decor::retourMenu()
{
   m_menu->retourMenuP();
}

void Decor::demarrerHorl()
{
   m_info->demarrerH();
}

void Decor::compteurTemps()
{
    m_info->gestionTemps();
}

void Decor::Fin_Jeu()
{
//on verifie sil ne reste plus de pions pour chaque joueur
    if(m_tableJeu.joueurs.at(0).pions.size()==0)
    {
        fin_partie=true;
        partie_gagne=true;
    }
    if(m_tableJeu.joueurs.at(1).pions.size()==0)
    {
        fin_partie=true;
        partie_gagne=false;
    }
}

void Decor::gestionDplSouris()
{
    m_menu->elementActif();
}

void Decor::gestionSelectionSouris()
{
    m_menu->selectionElActif();
}

void Decor::gestMajD()
{
    gestIndicateurP();
    m_info->maj_Info(m_tableJeu);
}

void Decor::InitInfo()
{
    m_info->initInfo();
}

void Decor::gestionTour(int ind_J)
{
    int indic=ind_J;

    if(indic==HUMAIN)
    {
        m_joueurC->HumainTour(m_tableJeu);
        m_joueurC->PromotionPion(m_tableJeu);
    }

    if(indic==CPU)
    {
        m_joueurC->CPU_Tour(m_tableJeu);
        m_joueurC->PromotionPion(m_tableJeu);
    }

    if(indic==HUMAIN2)
    {

    }
}

 Decor::~Decor()
 {
     delete m_joueurC;
     delete m_menu;
     delete m_info;
 }
