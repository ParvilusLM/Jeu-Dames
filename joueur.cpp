#include "joueur.h"


JoueurC::JoueurC()
{
    //joueur 1
    int cmpt=0;
    while(cmpt<12)
    {
        Pion nouvel_pion;
        nouvel_pion.type_pion=pion_R;
        nouvel_pion.selectionne=false;
        nouvel_pion.capture=false;
        nouvel_pion.s_pion.setOrigin(37.5,37.5);

        m_joueur_1.pions.insert(m_joueur_1.pions.end(),nouvel_pion);

        cmpt++;
    }
    m_joueur_1.nb_pions=m_joueur_1.pions.size();
    m_joueur_1.nb_pions_cap=0;


    //joueur_2
    int cmpt2=0;
    while(cmpt2<12)
    {
        Pion nouvel_pion;
        nouvel_pion.type_pion=pion_B;
        nouvel_pion.capture=false;
        nouvel_pion.s_pion.setOrigin(37.5,37.5);

        m_joueur_2.pions.insert(m_joueur_2.pions.end(),nouvel_pion);

        cmpt2++;
    }
    m_joueur_2.nb_pions=m_joueur_2.pions.size();
    m_joueur_2.nb_pions_cap=0;

}


void JoueurC::HumainTour(TableJeu &table_jeu)
 {
     table_jeu=table_jeu;
     bool pion_selec=false;
     int pion_type=0;

     int cmpt=0;
     while(cmpt<table_jeu.joueurs.at(1).pions.size())
     {
         if(table_jeu.joueurs.at(1).pions.at(cmpt).selectionne==true && table_jeu.joueurs.at(1).pions.at(cmpt).type_pion==pion_B)
         {
             pion_selec=true;
             pion_type=1;

         }

         if(table_jeu.joueurs.at(1).pions.at(cmpt).selectionne==true && table_jeu.joueurs.at(1).pions.at(cmpt).type_pion==pion_B_D)
         {
             pion_selec=true;
             pion_type=3;

         }

         cmpt++;
     }



     if(!pion_selec)
     {
        if(!SelectionPionAJouer(table_jeu))
        {
           fin_partie=true;
           partie_gagne=false;
        }

     }
     else
     {
         if(pion_type==1)
         {
             DeplacementSimplePion(table_jeu);
         }

         if(pion_type==3)
         {
             DeplacementDame(table_jeu);
         }

         PromotionPion(table_jeu);

     }
 }


 bool JoueurC::SelectionPionAJouer(TableJeu &table_jeu)
 {

     bool possible=false;

     int posit_X=sourisX/75;
     int posit_Y=sourisY/75;

     int compt=0;
     while(compt<table_jeu.joueurs.at(1).pions.size())
     {
        table_jeu.joueurs.at(1).pions.at(compt).selectionne=false;
        selec_valide=false;
        compt++;
     }

     if(h_capture)
     {
         possible=true;
         int commp=0;
         while(commp<ensemblePionValide.size())
         {
             if(ensemblePionValide.at(commp).x==posit_X && ensemblePionValide.at(commp).y==posit_Y)
             {
                 int cmpt=0;
                 while(cmpt<table_jeu.joueurs.at(1).pions.size())
                 {
                     if((posit_X*75+37.5)==table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().x && (posit_Y*75+37.5)==table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().y )
                     {
                         table_jeu.joueurs.at(1).pions.at(cmpt).selectionne=true;
                         selec_valide=true;
                         s_indic_selection.setPosition(table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().x,table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().y);

                     }

                     cmpt++;
                 }

             }

             commp++;
         }

     }

     if(!h_capture && h_deplacem)
     {
         possible=true;
         int commp=0;
         while(commp<ensemblePCapDeDepl.size())
         {
             if(ensemblePCapDeDepl.at(commp).x==posit_X && ensemblePCapDeDepl.at(commp).y==posit_Y)
             {
                 int cmpt=0;
                 while(cmpt<table_jeu.joueurs.at(1).pions.size())
                 {
                     if((posit_X*75+37.5)==table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().x && (posit_Y*75+37.5)==table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().y )
                     {
                         table_jeu.joueurs.at(1).pions.at(cmpt).selectionne=true;
                         selec_valide=true;
                         s_indic_selection.setPosition(table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().x,table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().y);

                     }

                     cmpt++;
                 }

             }

             commp++;
         }
     }


     h_capture=false;
     h_deplacem=false;

     return possible;
 }


 bool JoueurC::ia_selectionPionAJouer(TableJeu &table_jeu)
{

    //std::cout<<"Entree dans la fonction ia_selectionPionAJouer"<<std::endl;
    bool possible=false;
    bool poss_capture=false;
    bool poss_deplacem_simple=false;
    std::vector<sf::Vector2f> liste_pion_a_jouer;


    //std::cout<<"Possibilite capture: "<<poss_capture<<std::endl;
    //on test sil peut y avoir de capture
    int compt=0;
    while(compt<table_jeu.joueurs.at(0).pions.size())
    {
        if(table_jeu.joueurs.at(0).pions.at(compt).type_pion==pion_R)
        {
            bool m_gauche=false;
            bool m_droite=false;

            sf::Vector2f posInitialPion;
            posInitialPion.x=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().x;
            posInitialPion.y=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().y;

            int posiX=posInitialPion.x/75;
            int posiY=posInitialPion.y/75;

            if(!m_gauche && posiX>1 && posiY<6)
            {
                 bool prem_case=false;
                 bool deux_case=false;

                 int compt_1=0;
                 while(compt_1<table_jeu.joueurs.at(1).pions.size())
                 {

                     int posX=(posInitialPion.x/75)-1;
                     int posY=(posInitialPion.y/75)+1;

                     if(table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                     {
                         prem_case=true;
                     }

                     compt_1++;
                 }


                 int compt3=0;
                 while(compt3<table_jeu.joueurs.size())
                 {
                     int compt4=0;
                     while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                     {
                         int posX=(posInitialPion.x/75)-2;
                         int posY=(posInitialPion.y/75)+2;

                     if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
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

            if(!m_droite && posiX<6 && posiY<6)
            {
                 bool prem_case=false;
                 bool deux_case=false;

                 int compt_1=0;
                 while(compt_1<table_jeu.joueurs.at(1).pions.size())
                 {

                     int posX=(posInitialPion.x/75)+1;
                     int posY=(posInitialPion.y/75)+1;

                     if(table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                     {
                         prem_case=true;
                     }

                     compt_1++;
                 }


                 int compt3=0;
                 while(compt3<table_jeu.joueurs.size())
                 {
                     int compt4=0;
                     while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                     {
                         int posX=(posInitialPion.x/75)+2;
                         int posY=(posInitialPion.y/75)+2;

                     if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
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
                poss_capture=true;
            }
        }

        if(table_jeu.joueurs.at(0).pions.at(compt).type_pion==pion_R_D)
        {
            bool m_haut_g=false;
            bool m_haut_d=false;
            bool m_bas_g=false;
            bool m_bas_d=false;

            sf::Vector2f posInitialPion;
            posInitialPion.x=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().x;
            posInitialPion.y=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().y;


            int posiX=posInitialPion.x/75;
            int posiY=posInitialPion.y/75;

            if(!m_haut_g && posiX>1 && posiY>1)
            {
               bool prem_case_rempl=false;
               bool deux_case_vide=true;

               int comp=0;
               while(comp<table_jeu.joueurs.at(1).pions.size())
               {
                   int posX=(posInitialPion.x/75)-1;
                   int posY=(posInitialPion.y/75)-1;

                   if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                   {
                       prem_case_rempl=true;
                   }

                   comp++;
               }

               int comp2=0;
               while(comp2<table_jeu.joueurs.size())
               {
                   int comp3=0;
                   while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                   {
                       int posX=(posInitialPion.x/75)-2;
                       int posY=(posInitialPion.y/75)-2;

                       if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                       {
                           deux_case_vide=false;
                       }
                       comp3++;
                   }

                   comp2++;
               }

               if(prem_case_rempl && deux_case_vide)
               {
                   m_haut_g=true;
               }
            }



            if(!m_haut_d && posiX<6 && posiY>1)
            {
               bool prem_case_rempl=false;
               bool deux_case_vide=true;

               int comp=0;
               while(comp<table_jeu.joueurs.at(1).pions.size())
               {
                   int posX=(posInitialPion.x/75)+1;
                   int posY=(posInitialPion.y/75)-1;

                   if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                   {
                       prem_case_rempl=true;
                   }

                   comp++;
               }

               int comp2=0;
               while(comp2<table_jeu.joueurs.size())
               {
                   int comp3=0;
                   while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                   {
                       int posX=(posInitialPion.x/75)+2;
                       int posY=(posInitialPion.y/75)-2;

                       if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                       {
                           deux_case_vide=false;
                       }
                       comp3++;
                   }

                   comp2++;
               }

               if(prem_case_rempl && deux_case_vide)
               {
                   m_haut_d=true;
               }
            }



            if(!m_bas_g && posiX>1 && posiY<6)
            {
                bool prem_case_rempl=false;
               bool deux_case_vide=true;

               int comp=0;
               while(comp<table_jeu.joueurs.at(1).pions.size())
               {
                   int posX=(posInitialPion.x/75)-1;
                   int posY=(posInitialPion.y/75)+1;

                   if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                   {
                       prem_case_rempl=true;
                   }

                   comp++;
               }

               int comp2=0;
               while(comp2<table_jeu.joueurs.size())
               {
                   int comp3=0;
                   while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                   {
                       int posX=(posInitialPion.x/75)-2;
                       int posY=(posInitialPion.y/75)+2;

                       if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                       {
                           deux_case_vide=false;
                       }
                       comp3++;
                   }

                   comp2++;
               }

               if(prem_case_rempl && deux_case_vide)
               {
                   m_bas_g=true;
               }
            }



            if(!m_bas_d && posInitialPion.x/75<6 && posInitialPion.y/75<6)
            {
                bool prem_case_rempl=false;
               bool deux_case_vide=true;

               int comp=0;
               while(comp<table_jeu.joueurs.at(1).pions.size())
               {
                   int posX=(posInitialPion.x/75)+1;
                   int posY=(posInitialPion.y/75)+1;

                   if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                   {
                       prem_case_rempl=true;
                   }

                   comp++;
               }

               int comp2=0;
               while(comp2<table_jeu.joueurs.size())
               {
                   int comp3=0;
                   while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                   {
                       int posX=(posInitialPion.x/75)+2;
                       int posY=(posInitialPion.y/75)+2;

                       if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                       {
                           deux_case_vide=false;
                       }
                       comp3++;
                   }

                   comp2++;
               }

               if(prem_case_rempl && deux_case_vide)
               {
                   m_bas_d=true;
               }
            }

            if(m_bas_d || m_bas_g || m_haut_d || m_haut_g)
            {
                poss_capture=true;
            }
        }

        compt++;
    }
    //std::cout<<"Possibilite capture: "<<poss_capture<<std::endl;


    //si le test precedent est negatif on test maintenant sil peut y avoir de deplacement sans capture
    if(!poss_deplacem_simple)
    {
        int compt2=0;
        while(compt2<table_jeu.joueurs.at(0).pions.size())
        {
            if(table_jeu.joueurs.at(0).pions.at(compt2).type_pion==pion_R)
            {
                bool m_g=false;
                bool m_d=false;

                int posI_x=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().x/75;
                int posI_y=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().y/75;

                if(!m_g && posI_x>0 && posI_y<7)
                {
                    m_g=true;
                    int posX=posI_x-1;
                    int posY=posI_y+1;

                    int compt3=0;
                    while(compt3<table_jeu.joueurs.size())
                    {
                        int compt4=0;
                        while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                        {
                            if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                            {
                                m_g=false;
                            }

                            compt4++;
                        }

                        compt3++;
                    }
                }

                if(!m_d && posI_x<7 && posI_y<7)
                {
                    m_d=true;
                    int posX=posI_x+1;
                    int posY=posI_y+1;

                    int compt3=0;
                    while(compt3<table_jeu.joueurs.size())
                    {
                        int compt4=0;
                        while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                        {
                            if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                            {
                                m_d=false;
                            }

                            compt4++;
                        }

                        compt3++;
                    }
                }

                if(m_g || m_d)
                {
                    poss_deplacem_simple=true;
                }
            }

            if(table_jeu.joueurs.at(0).pions.at(compt2).type_pion==pion_R_D)
            {
                bool m_haut_g=false;
                bool m_haut_d=false;
                bool m_bas_g=false;
                bool m_bas_d=false;

                int posI_x=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().x/75;
                int posI_y=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().y/75;

                if(!m_haut_g && posI_x>0 && posI_y>0)
                {
                    m_haut_g=true;
                    int posX=posI_x-1;
                    int posY=posI_y-1;

                    int compt3=0;
                    while(compt3<table_jeu.joueurs.size())
                    {
                        int compt4=0;
                        while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                        {
                            if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                            {
                                m_haut_g=false;
                            }

                            compt4++;
                        }

                        compt3++;
                    }
                }

                if(!m_haut_d && posI_x<7 && posI_y>0)
                {
                    m_haut_d=true;
                    int posX=posI_x+1;
                    int posY=posI_y-1;

                    int compt3=0;
                    while(compt3<table_jeu.joueurs.size())
                    {
                        int compt4=0;
                        while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                        {
                            if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                            {
                                m_haut_d=false;
                            }

                            compt4++;
                        }

                        compt3++;
                    }
                }

                if(m_bas_g && posI_x>0 && posI_y<7)
                {
                    m_bas_g=true;
                    int posX=posI_x-1;
                    int posY=posI_y+1;

                    int compt3=0;
                    while(compt3<table_jeu.joueurs.size())
                    {
                        int compt4=0;
                        while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                        {
                            if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                            {
                                m_bas_g=false;
                            }

                            compt4++;
                        }

                        compt3++;
                    }
                }

                if(!m_bas_d && posI_x<7 && posI_y<7)
                {
                    m_bas_d=true;
                    int posX=posI_x+1;
                    int posY=posI_y+1;

                    int compt3=0;
                    while(compt3<table_jeu.joueurs.size())
                    {
                        int compt4=0;
                        while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                        {
                            if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                            {
                                m_bas_d=false;
                            }

                            compt4++;
                        }

                        compt3++;
                    }
                }

                if(m_haut_g || m_haut_d || m_bas_g || m_bas_d)
                {
                    poss_deplacem_simple=true;
                }

            }

            compt2++;
        }


    }



    //si les deux test sont negatif alors c'est la fin de la partie et elle perd
    if(poss_capture || poss_deplacem_simple)
    {
        //si au moins un des deux test est positif alors on fait les calcul pour determiner le pion qui doit etre jouer

        //std::cout<<"Entree dans la condition poss_capture || poss_deplacem_simple"<<std::endl;
        if(poss_capture)
        {
            ia_captur_p=true;
            //liste des pions qui peuvent capturer
            int compt=0;
            while(compt<table_jeu.joueurs.at(0).pions.size())
            {


                if(table_jeu.joueurs.at(0).pions.at(compt).type_pion==pion_R)
                {
                    bool m_gauche=false;
                    bool m_droite=false;

                    sf::Vector2f posInitialPion;
                    posInitialPion.x=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().x;
                    posInitialPion.y=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().y;

                    int posiX=posInitialPion.x/75;
                    int posiY=posInitialPion.y/75;

                    if(!m_gauche && posiX>1 && posiY<6)
                    {
                         bool prem_case=false;
                         bool deux_case=false;

                         int compt_1=0;
                         while(compt_1<table_jeu.joueurs.at(1).pions.size())
                         {

                             int posX=(posInitialPion.x/75)-1;
                             int posY=(posInitialPion.y/75)+1;

                             if(table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                             {
                                 prem_case=true;
                             }

                             compt_1++;
                         }


                         int compt3=0;
                         while(compt3<table_jeu.joueurs.size())
                         {
                             int compt4=0;
                             while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                             {
                                 int posX=(posInitialPion.x/75)-2;
                                 int posY=(posInitialPion.y/75)+2;

                             if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
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

                    if(!m_droite && posiX<6 && posiY<6)
                    {
                         bool prem_case=false;
                         bool deux_case=false;

                         int compt_1=0;
                         while(compt_1<table_jeu.joueurs.at(1).pions.size())
                         {

                             int posX=(posInitialPion.x/75)+1;
                             int posY=(posInitialPion.y/75)+1;

                             if(table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                             {
                                 prem_case=true;
                             }

                             compt_1++;
                         }


                         int compt3=0;
                         while(compt3<table_jeu.joueurs.size())
                         {
                             int compt4=0;
                             while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                             {
                                 int posX=(posInitialPion.x/75)+2;
                                 int posY=(posInitialPion.y/75)+2;

                             if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
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
                        sf::Vector2f nouvel_coord_pion;
                        nouvel_coord_pion.x=posInitialPion.x;
                        nouvel_coord_pion.y=posInitialPion.y;

                        liste_pion_a_jouer.insert(liste_pion_a_jouer.end(),nouvel_coord_pion);
                    }
                }

                if(table_jeu.joueurs.at(0).pions.at(compt).type_pion==pion_R_D)
                {
                    bool m_haut_g=false;
                    bool m_haut_d=false;
                    bool m_bas_g=false;
                    bool m_bas_d=false;

                    sf::Vector2f posInitialPion;
                    posInitialPion.x=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().x;
                    posInitialPion.y=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().y;

                    int posiX=posInitialPion.x/75;
                    int posiY=posInitialPion.y/75;

                    if(!m_haut_g && posiX>1 && posiY>1)
                    {
                       bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(1).pions.size())
                       {
                           int posX=(posInitialPion.x/75)-1;
                           int posY=(posInitialPion.y/75)-1;

                           if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)-2;
                               int posY=(posInitialPion.y/75)-2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_haut_g=true;
                       }
                    }



                    if(!m_haut_d && posiX<6 && posiY>1)
                    {
                       bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(1).pions.size())
                       {
                           int posX=(posInitialPion.x/75)+1;
                           int posY=(posInitialPion.y/75)-1;

                           if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)+2;
                               int posY=(posInitialPion.y/75)-2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_haut_d=true;
                       }
                    }



                    if(!m_bas_g && posiX>1 && posiY<6)
                    {
                        bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(1).pions.size())
                       {
                           int posX=(posInitialPion.x/75)-1;
                           int posY=(posInitialPion.y/75)+1;

                           if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)-2;
                               int posY=(posInitialPion.y/75)+2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_bas_g=true;
                       }
                    }



                    if(!m_bas_d && posiX<6 && posiY<6)
                    {
                        bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(1).pions.size())
                       {
                           int posX=(posInitialPion.x/75)+1;
                           int posY=(posInitialPion.y/75)+1;

                           if(table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)+2;
                               int posY=(posInitialPion.y/75)+2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_bas_d=true;
                       }
                    }

                    if(m_bas_d || m_bas_g || m_haut_d || m_haut_g)
                    {
                        sf::Vector2f nouvel_coord_pion;
                        nouvel_coord_pion.x=posInitialPion.x;
                        nouvel_coord_pion.y=posInitialPion.y;

                        liste_pion_a_jouer.insert(liste_pion_a_jouer.end(),nouvel_coord_pion);
                    }
                }

                compt++;
            }

        }

        if(!poss_capture && poss_deplacem_simple)
        {
            ia_simp_depl=true;
            int compt2=0;
            while(compt2<table_jeu.joueurs.at(0).pions.size())
            {
                if(table_jeu.joueurs.at(0).pions.at(compt2).type_pion==pion_R)
                {
                    bool m_g=false;
                    bool m_d=false;

                    int posI_x=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().x/75;
                    int posI_y=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().y/75;

                    //std::cout<<"Valeur de posI_x: "<<posI_x<<std::endl;
                    //std::cout<<"Valeur de posI_y: "<<posI_y<<std::endl;


                    if(!m_g && posI_x-1>=0 && posI_y+1<=7)
                    {
                        m_g=true;
                        //std::cout<<"Entree dans la condition deplacement en bas a gauche"<<std::endl;
                        int posX=posI_x-1;
                        int posY=posI_y+1;

                        int compt3=0;
                        while(compt3<table_jeu.joueurs.size())
                        {
                            int compt4=0;
                            while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                            {
                                if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                {
                                    m_g=false;
                                }

                                compt4++;
                            }

                            compt3++;
                        }
                    }

                    if(!m_d && posI_x+1<=7 && posI_y+1<=7)
                    {
                        m_d=true;
                        //std::cout<<"Entree dans la condition deplacement en bas a droite"<<std::endl;
                        int posX=posI_x+1;
                        int posY=posI_y+1;

                        int compt3=0;
                        while(compt3<table_jeu.joueurs.size())
                        {
                            int compt4=0;
                            while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                            {
                                if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                {
                                    m_d=false;
                                }

                                compt4++;
                            }

                            compt3++;
                        }
                    }

                    if(m_g || m_d)
                    {
                        sf::Vector2f nouvel_coord_pion;
                        nouvel_coord_pion.x=posI_x*75+37.5;
                        nouvel_coord_pion.y=posI_y*75+37.5;

                        liste_pion_a_jouer.insert(liste_pion_a_jouer.end(),nouvel_coord_pion);
                    }
                }

                if(table_jeu.joueurs.at(0).pions.at(compt2).type_pion==pion_R_D)
                {
                    bool m_haut_g=false;
                    bool m_haut_d=false;
                    bool m_bas_g=false;
                    bool m_bas_d=false;

                    int posI_x=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().x/75;
                    int posI_y=table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().y/75;

                    if(!m_haut_g && posI_x-1>=0 && posI_y-1>=0)
                    {
                        m_haut_g=true;
                        int posX=posI_x-1;
                        int posY=posI_y-1;

                        int compt3=0;
                        while(compt3<table_jeu.joueurs.size())
                        {
                            int compt4=0;
                            while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                            {
                                if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                {
                                    m_haut_g=false;
                                }

                                compt4++;
                            }

                            compt3++;
                        }
                    }

                    if(!m_haut_d && posI_x+1<=7 && posI_y-1>=0)
                    {
                        m_haut_d=true;
                        int posX=posI_x+1;
                        int posY=posI_y-1;

                        int compt3=0;
                        while(compt3<table_jeu.joueurs.size())
                        {
                            int compt4=0;
                            while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                            {
                                if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                {
                                    m_haut_d=false;
                                }

                                compt4++;
                            }

                            compt3++;
                        }
                    }

                    if(!m_bas_g && posI_x-1>=0 && posI_y+1<=7)
                    {
                        m_bas_g=true;
                        int posX=posI_x-1;
                        int posY=posI_y+1;

                        int compt3=0;
                        while(compt3<table_jeu.joueurs.size())
                        {
                            int compt4=0;
                            while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                            {
                                if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                {
                                    m_bas_g=false;
                                }

                                compt4++;
                            }

                            compt3++;
                        }
                    }

                    if(!m_bas_d && posI_x+1<=7 && posI_y+1<=7)
                    {
                        m_bas_d=true;
                        int posX=posI_x+1;
                        int posY=posI_y+1;

                        int compt3=0;
                        while(compt3<table_jeu.joueurs.size())
                        {
                            int compt4=0;
                            while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                            {
                                if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
                                {
                                    m_bas_d=false;
                                }

                                compt4++;
                            }

                            compt3++;
                        }
                    }

                    if(m_haut_g || m_haut_d || m_bas_g || m_bas_d)
                    {
                        sf::Vector2f nouvel_coord_pion;
                        nouvel_coord_pion.x=posI_x*75+37.5;
                        nouvel_coord_pion.y=posI_y*75+37.5;

                        liste_pion_a_jouer.insert(liste_pion_a_jouer.end(),nouvel_coord_pion);
                    }

                }

                compt2++;
            }

        }


        //choix du pion a jouer au hasard
        int taill_liste=liste_pion_a_jouer.size();
        int compp=0;
        while(compp<liste_pion_a_jouer.size())
        {
            //std::cout<<"ELEMENT DE liste_pion_a_jouer : "<<liste_pion_a_jouer.at(compp).x<<" : "<<liste_pion_a_jouer.at(compp).y<<std::endl;
            compp++;
        }
        int indice_choix=0;


        indice_choix=rand()%taill_liste;



        float positX=liste_pion_a_jouer.at(indice_choix).x;
        float positY=liste_pion_a_jouer.at(indice_choix).y;
        //std::cout<<"Valeur positX: "<<positX<<std::endl;
        //std::cout<<"Valeur positY: "<<positY<<std::endl;

        //selection du pion a jouer
        int compt2=0;
        while(compt2<table_jeu.joueurs.at(0).pions.size())
        {
            if(table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().x==positX && table_jeu.joueurs.at(0).pions.at(compt2).s_pion.getPosition().y==positY)
            {
                table_jeu.joueurs.at(0).pions.at(compt2).selectionne=true;
                //std::cout<<"Un pion est selectionne"<<std::endl;
            }

            compt2++;
        }

        possible=true;

    }
    else
    {
        possible=false;
    }


    //std::cout<<"Sortie dans la fonction ia_selectionPionAJouer"<<std::endl;

    return possible;
}


void JoueurC::CPU_Tour(TableJeu &table_jeu)
{
    table_jeu=table_jeu;
    //std::cout<<"Entree dans la fonction CPU_TOUR"<<std::endl;


    //on determine un pion a deplacer si possible
    if(ia_selectionPionAJouer(table_jeu))
    {
        int pion_type=0;

         int cmpt=0;
         while(cmpt<table_jeu.joueurs.at(0).pions.size())
         {
             if(table_jeu.joueurs.at(0).pions.at(cmpt).selectionne==true && table_jeu.joueurs.at(0).pions.at(cmpt).type_pion==pion_R)
             {
                 pion_type=0;


             }

             if(table_jeu.joueurs.at(0).pions.at(cmpt).selectionne==true && table_jeu.joueurs.at(0).pions.at(cmpt).type_pion==pion_R_D)
             {
                 pion_type=2;

             }

             cmpt++;
         }

         //std::cout<<pion_type<<std::endl;


         if(pion_type==0)
         {
             //std::cout<<"Entree dans la condition pion_type=0"<<std::endl;

             if(ia_captur_p)
             {
                 if(ia_PossibiliteCapture(table_jeu))
                 {
                     //std::cout<<"Entree dans la condition de capture pion simple"<<std::endl;
                     CapturePion(table_jeu,CPU);
                     int compt=0;
                     while(compt<table_jeu.joueurs.at(0).pions.size())
                     {
                         if(table_jeu.joueurs.at(0).pions.at(compt).selectionne)
                         {
                             table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(sourisX*75+37.5,sourisY*75+37.5);
                             table_jeu.joueurs.at(0).pions.at(compt).selectionne=false;
                         }

                         compt++;
                     }


                     LA_MAIN=true;
                 }

             }

             if(!ia_captur_p && ia_simp_depl)
             {
                 if(ia_simp_depl)
                 {
                     int compt=0;
                     while(compt<table_jeu.joueurs.at(0).pions.size())
                     {
                         if(table_jeu.joueurs.at(0).pions.at(compt).selectionne)
                         {
                             bool dir_b_g=false;
                             bool dir_b_d=false;

                             int posInitPX=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().x/75;
                             int posInitPY=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().y/75;

                             //std::cout<<"posInitPX: "<<posInitPX<<std::endl;
                             //std::cout<<"posInitPY: "<<posInitPY<<std::endl;


                             //
                             if(!dir_b_g && posInitPX-1>=0 && posInitPY+1<=7)
                             {
                                 dir_b_g=true;
                                 int posX=posInitPX-1;
                                 int posY=posInitPY+1;

                                 int compt2=0;
                                 while(compt2<table_jeu.joueurs.size())
                                 {
                                     int compt3=0;
                                     while(compt3<table_jeu.joueurs.at(compt2).pions.size())
                                     {
                                         if(table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().y==posY*75+37.5)
                                         {
                                             dir_b_g=false;
                                         }
                                         compt3++;
                                     }

                                     compt2++;
                                 }
                             }

                             if(!dir_b_d && posInitPX+1<=7 && posInitPY+1<=7)
                             {
                                 dir_b_d=true;
                                 int posX=posInitPX+1;
                                 int posY=posInitPY+1;

                                 int compt2=0;
                                 while(compt2<table_jeu.joueurs.size())
                                 {
                                     int compt3=0;
                                     while(compt3<table_jeu.joueurs.at(compt2).pions.size())
                                     {
                                         if(table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().y==posY*75+37.5)
                                         {
                                             dir_b_d=false;
                                         }
                                         compt3++;
                                     }

                                     compt2++;
                                 }
                             }


                             if(dir_b_g && !dir_b_d)
                             {
                                 int posX=posInitPX-1;
                                 int posY=posInitPY+1;

                                 table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                             }
                             else if(!dir_b_g && dir_b_d)
                             {
                                 int posX=posInitPX+1;
                                 int posY=posInitPY+1;

                                 table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                             }
                             else
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }

                             table_jeu.joueurs.at(0).pions.at(compt).selectionne=false;
                             LA_MAIN=true;
                         }
                         compt++;
                     }
                 }

             }



         }

         if(pion_type==2)
         {
             if(ia_captur_p)
             {
                 if(ia_PossibiliteCaptureDame(table_jeu))
                 {
                     CapturePion(table_jeu,CPU);
                     int compt=0;
                     while(compt<table_jeu.joueurs.at(0).pions.size())
                     {
                         if(table_jeu.joueurs.at(0).pions.at(compt).selectionne)
                         {
                             table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(sourisX*75+37.5,sourisY*75+37.5);
                             table_jeu.joueurs.at(0).pions.at(compt).selectionne==false;
                         }

                         compt++;
                     }



                     LA_MAIN=true;
                 }

             }

             if(!ia_captur_p && ia_simp_depl)
             {
                 if(ia_simp_depl)
                 {
                     int compt=0;
                     while(compt<table_jeu.joueurs.at(0).pions.size())
                     {
                         if(table_jeu.joueurs.at(0).pions.at(compt).selectionne)
                         {
                             bool dir_b_g=false;
                             bool dir_b_d=false;
                             bool dir_h_g=false;
                             bool dir_h_d=false;

                             int posInitPX=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().x/75;
                             int posInitPY=table_jeu.joueurs.at(0).pions.at(compt).s_pion.getPosition().y/75;


                             //
                             if(!dir_b_g && posInitPX>0 && posInitPY<7)
                             {
                                 dir_b_g=true;
                                 int posX=posInitPX-1;
                                 int posY=posInitPY+1;

                                 int compt2=0;
                                 while(compt2<table_jeu.joueurs.size())
                                 {
                                     int compt3=0;
                                     while(compt3<table_jeu.joueurs.at(compt2).pions.size())
                                     {
                                         if(table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().y==posY*75+37.5)
                                         {
                                             dir_b_g=false;
                                         }
                                         compt3++;
                                     }

                                     compt2++;
                                 }
                             }

                             if(!dir_b_d && posInitPX<7 && posInitPY<7)
                             {
                                 dir_b_d=true;
                                 int posX=posInitPX+1;
                                 int posY=posInitPY+1;

                                 int compt2=0;
                                 while(compt2<table_jeu.joueurs.size())
                                 {
                                     int compt3=0;
                                     while(compt3<table_jeu.joueurs.at(compt2).pions.size())
                                     {
                                         if(table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().y==posY*75+37.5)
                                         {
                                             dir_b_d=false;
                                         }
                                         compt3++;
                                     }

                                     compt2++;
                                 }
                             }

                             if(!dir_h_g && posInitPX>0 && posInitPY>0)
                             {
                                 dir_h_g=true;
                                 int posX=posInitPX-1;
                                 int posY=posInitPY-1;

                                 int compt2=0;
                                 while(compt2<table_jeu.joueurs.size())
                                 {
                                     int compt3=0;
                                     while(compt3<table_jeu.joueurs.at(compt2).pions.size())
                                     {
                                         if(table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().y==posY*75+37.5)
                                         {
                                             dir_h_g=false;
                                         }
                                         compt3++;
                                     }

                                     compt2++;
                                 }
                             }

                             if(!dir_h_d && posInitPX<7 && posInitPY>0)
                             {
                                 dir_h_d=true;
                                 int posX=posInitPX-1;
                                 int posY=posInitPY+1;

                                 int compt2=0;
                                 while(compt2<table_jeu.joueurs.size())
                                 {
                                     int compt3=0;
                                     while(compt3<table_jeu.joueurs.at(compt2).pions.size())
                                     {
                                         if(table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt2).pions.at(compt3).s_pion.getPosition().y==posY*75+37.5)
                                         {
                                             dir_h_d=false;
                                         }
                                         compt3++;
                                     }

                                     compt2++;
                                 }
                             }



                             //
                             if(dir_h_g && !dir_h_d && !dir_b_g && !dir_b_d)
                             {
                                 int posX=posInitPX-1;
                                 int posY=posInitPY-1;

                                 table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                             }
                             else if(!dir_h_g && dir_h_d && !dir_b_g && !dir_b_d)
                             {
                                 int posX=posInitPX+1;
                                 int posY=posInitPY-1;

                                 table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                             }
                             else if(!dir_h_g && !dir_h_d && dir_b_g && !dir_b_d)
                             {
                                 int posX=posInitPX-1;
                                 int posY=posInitPY+1;

                                 table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                             }
                             else if(!dir_h_g && !dir_h_d && !dir_b_g &&  dir_b_d)
                             {
                                 int posX=posInitPX+1;
                                 int posY=posInitPY+1;

                                 table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                             }
                             else if(dir_h_g && dir_h_d && !dir_b_g &&  !dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(dir_h_g && !dir_h_d && dir_b_g &&  !dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(dir_h_g && !dir_h_d && !dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(!dir_h_g && dir_h_d && dir_b_g &&  !dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(!dir_h_g && dir_h_d && !dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(!dir_h_g && !dir_h_d && dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(dir_h_g && dir_h_d && dir_b_g &&  !dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else if(nb_alea==1)
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(dir_h_g && dir_h_d && !dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else if(nb_alea==1)
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(dir_h_g && !dir_h_d && dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else if(nb_alea==1)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(!dir_h_g && dir_h_d && dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else if(nb_alea==1)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else if(dir_h_g && dir_h_d && dir_b_g &&  dir_b_d)
                             {
                                 int nb_alea=rand()%2;
                                 if(nb_alea==0)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else if(nb_alea==1)
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY-1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else if(nb_alea==2)
                                 {
                                     int posX=posInitPX-1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                                 else
                                 {
                                     int posX=posInitPX+1;
                                     int posY=posInitPY+1;

                                     table_jeu.joueurs.at(0).pions.at(compt).s_pion.setPosition(posX*75+37.5,posY*75+37.5);
                                 }
                             }
                             else
                             {

                             }

                             table_jeu.joueurs.at(0).pions.at(compt).selectionne=false;
                             LA_MAIN=true;
                         }
                         compt++;
                     }
                 }

             }

         }

         PromotionPion(table_jeu);
         //Fin_Jeu(table_jeu);
         ia_captur_p=false;
         ia_simp_depl=false;
    }
    else
    {
        LA_MAIN=true;
        fin_partie=true;
        partie_gagne=true;

    }

    //std::cout<<"Sortie dans la fonction CPU_TOUR"<<std::endl;

}


bool JoueurC::JeuPossibleSimplePion(TableJeu &table_jeu)
 {
     table_jeu=table_jeu;

     bool possible=false;
     bool espace_vide=true;
     bool poss_cap=false;

     int compt=0;
     while(compt<table_jeu.joueurs.size())
     {
         int compt2=0;
         while(compt2<table_jeu.joueurs.at(compt).pions.size())
         {
             if(table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x==(sourisX/75)*75+37.5 && table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y==(sourisY/75)*75+37.5)
             {
                 espace_vide=false;
             }

             compt2++;
         }

         compt++;
     }

     int cmpt=0;
     while(cmpt<table_jeu.joueurs.at(1).pions.size())
     {
         if(table_jeu.joueurs.at(1).pions.at(cmpt).selectionne==true)
         {
             int indic_pos_x;
             int indic_pos_y;

             indic_pos_x=table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().x/75;
             indic_pos_y=table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().y/75;



             //boucle pour savoir si il y a au moins une possibilite de capture
            int compteur=0;
            while(compteur<table_jeu.joueurs.at(1).pions.size())
            {
                if(table_jeu.joueurs.at(1).pions.at(compteur).selectionne==true && table_jeu.joueurs.at(1).pions.at(compteur).type_pion==pion_B)
                {
                     bool m_droite=false;
                     bool m_gauche=false;

                     sf::Vector2f posInitialPion;
                     posInitialPion.x=table_jeu.joueurs.at(1).pions.at(compteur).s_pion.getPosition().x;
                     posInitialPion.y=table_jeu.joueurs.at(1).pions.at(compteur).s_pion.getPosition().y;

                     int posiX=posInitialPion.x/75;
                     int posiY=posInitialPion.y/75;

                     if(!m_gauche && posiX>1 && posiY>1)
                     {
                         bool prem_case=false;
                         bool deux_case=false;

                         int compt_1=0;
                         while(compt_1<table_jeu.joueurs.at(0).pions.size())
                         {

                             int posX=(posInitialPion.x/75)-1;
                             int posY=(posInitialPion.y/75)-1;

                             if(table_jeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                             {
                                 prem_case=true;
                             }

                             compt_1++;
                         }

                        int compt_2=0;
                         while(compt_2<table_jeu.joueurs.at(1).pions.size())
                         {
                             int posX=(posInitialPion.x/75)-1;
                             int posY=(posInitialPion.y/75)-1;

                             if(table_jeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                             {
                                 prem_case=false;
                             }

                             compt_2++;
                         }


                         int compt3=0;
                         while(compt3<table_jeu.joueurs.size())
                         {
                             int compt4=0;
                             while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                             {
                                 int posX=(posInitialPion.x/75)-2;
                                 int posY=(posInitialPion.y/75)-2;

                             if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
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


                     if(!m_droite && posiX<6 && posiY>1)
                     {
                         bool prem_case=false;
                         bool deux_case=false;

                         int compt_1=0;
                         while(compt_1<table_jeu.joueurs.at(0).pions.size())
                         {
                             int posX=(posInitialPion.x/75)+1;
                             int posY=(posInitialPion.y/75)-1;

                             if(table_jeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(0).pions.at(compt_1).s_pion.getPosition().y==posY*75+37.5)
                             {
                                 prem_case=true;
                             }

                             compt_1++;
                         }

                        int compt_2=0;
                         while(compt_2<table_jeu.joueurs.at(1).pions.size())
                         {
                             int posX=(posInitialPion.x/75)+1;
                             int posY=(posInitialPion.y/75)-1;

                             if(table_jeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(1).pions.at(compt_2).s_pion.getPosition().y==posY*75+37.5)
                             {
                                 prem_case=false;
                             }

                             compt_2++;
                         }

                         int compt3=0;
                         while(compt3<table_jeu.joueurs.size())
                         {
                             int compt4=0;
                             while(compt4<table_jeu.joueurs.at(compt3).pions.size())
                             {
                                 int posX=(posInitialPion.x/75)+2;
                                 int posY=(posInitialPion.y/75)-2;

                             if(table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(compt3).pions.at(compt4).s_pion.getPosition().y==posY*75+37.5)
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

                     if(m_gauche || m_droite)
                     {
                         poss_cap=true;
                     }
                }

                compteur++;
            }


             if(poss_cap)
             {
                 if(espace_vide && PossibiliteCapture(table_jeu))
                 {
                     possible=true;
                     CapturePion(table_jeu,HUMAIN);
                 }
             }

             if(!poss_cap)
             {
                 if(espace_vide && ((sourisX/75==indic_pos_x-1 && sourisY/75==indic_pos_y-1) || (sourisX/75==indic_pos_x+1 && sourisY/75==indic_pos_y-1 && sourisX/75<8) ))
                 {
                     possible=true;
                 }
             }


         }

         cmpt++;
     }
     return possible;
 }

bool JoueurC::JeuPossibleDame(TableJeu &table_jeu)
 {
     table_jeu=table_jeu;

     bool possible=false;
     bool espace_vide=true;
     bool poss_cap=false;

     int compt=0;
     while(compt<table_jeu.joueurs.size())
     {
         int compt2=0;
         while(compt2<table_jeu.joueurs.at(compt).pions.size())
         {
             if(table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x==(sourisX/75)*75+37.5 && table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y==(sourisY/75)*75+37.5)
             {
                 espace_vide=false;
             }

             compt2++;
         }

         compt++;
     }

     int cmpt=0;
     while(cmpt<table_jeu.joueurs.at(1).pions.size())
     {
         if(table_jeu.joueurs.at(1).pions.at(cmpt).selectionne==true)
         {
             int indic_pos_x;
             int indic_pos_y;

             indic_pos_x=table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().x/75;
             indic_pos_y=table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.getPosition().y/75;

            //boucle pour savoir s'il y a au moins une possibilite de capture
            int compt=0;
            while(compt<table_jeu.joueurs.at(1).pions.size())
            {
                if(table_jeu.joueurs.at(1).pions.at(compt).selectionne && table_jeu.joueurs.at(1).pions.at(compt).type_pion==pion_B_D)
                {
                    bool m_haut_g=false;
                    bool m_haut_d=false;
                    bool m_bas_g=false;
                    bool m_bas_d=false;

                     sf::Vector2f posInitialPion;
                     posInitialPion.x=table_jeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().x;
                     posInitialPion.y=table_jeu.joueurs.at(1).pions.at(compt).s_pion.getPosition().y;

                    if(!m_haut_g)
                    {
                       bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(0).pions.size())
                       {
                           int posX=(posInitialPion.x/75)-1;
                           int posY=(posInitialPion.y/75)-1;

                           if(table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)-2;
                               int posY=(posInitialPion.y/75)-2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_haut_g=true;
                       }
                    }

                    if(!m_haut_d)
                    {
                       bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(0).pions.size())
                       {
                           int posX=(posInitialPion.x/75)+1;
                           int posY=(posInitialPion.y/75)-1;

                           if(table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)+2;
                               int posY=(posInitialPion.y/75)-2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_haut_d=true;
                       }
                    }

                    if(!m_bas_g)
                    {
                        bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(0).pions.size())
                       {
                           int posX=(posInitialPion.x/75)-1;
                           int posY=(posInitialPion.y/75)+1;

                           if(table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)-2;
                               int posY=(posInitialPion.y/75)+2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_bas_g=true;
                       }
                    }

                    if(!m_bas_d)
                    {
                        bool prem_case_rempl=false;
                       bool deux_case_vide=true;

                       int comp=0;
                       while(comp<table_jeu.joueurs.at(0).pions.size())
                       {
                           int posX=(posInitialPion.x/75)+1;
                           int posY=(posInitialPion.y/75)+1;

                           if(table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(0).pions.at(comp).s_pion.getPosition().y==posY*75+37.5)
                           {
                               prem_case_rempl=true;
                           }

                           comp++;
                       }

                       int comp2=0;
                       while(comp2<table_jeu.joueurs.size())
                       {
                           int comp3=0;
                           while(comp3<table_jeu.joueurs.at(comp2).pions.size())
                           {
                               int posX=(posInitialPion.x/75)+2;
                               int posY=(posInitialPion.y/75)+2;

                               if(table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().x==posX*75+37.5 && table_jeu.joueurs.at(comp2).pions.at(comp3).s_pion.getPosition().y==posY*75+37.5)
                               {
                                   deux_case_vide=false;
                               }
                               comp3++;
                           }

                           comp2++;
                       }

                       if(prem_case_rempl && deux_case_vide)
                       {
                           m_bas_d=true;
                       }
                    }

                    if(m_haut_d || m_haut_g || m_bas_d || m_bas_g)
                    {
                        poss_cap=true;
                    }
                }

                compt++;
            }



            if(poss_cap)
            {
                 if(espace_vide && PossibiliteCaptureDame(table_jeu))
                 {
                     possible=true;
                     CapturePion(table_jeu,HUMAIN);
                 }
            }

            if(!poss_cap)
            {
                 if(espace_vide && ((sourisX/75==indic_pos_x-1 && sourisY/75==indic_pos_y-1) || (sourisX/75==indic_pos_x+1 && sourisY/75==indic_pos_y-1 && sourisX/75<8) || (sourisX/75==indic_pos_x-1 && sourisY/75==indic_pos_y+1) || (sourisX/75==indic_pos_x+1 && sourisY/75==indic_pos_y+1 && sourisY/75<8)))
                 {
                     possible=true;
                 }
            }
         }

         cmpt++;
     }
     return possible;
 }

 bool JoueurC::ia_PossibiliteCapture(TableJeu &table_jeu)
{
    table_jeu=table_jeu;

    //std::cout<<"Entree dans la fonction ia_PossibiliteCapture()"<<std::endl;
    bool possible=false;

        // vecteur representant l'ensemble des cases des differents chemins
        std::vector<CaseValabe> eChemin;

        //vecteur pour stocker les cases a tester
        std::vector<CaseValabe> eCasesATester;

        //vector pour le chemin choisi
        std::vector<CaseValabe> eCaseChemChoisi;

        //valeur initial a verifier
        int val_a_verif=1;

    //creation du tableau virtuel pour tacer les chemins possibles
    int tableau_virtuel[8][8]={0};



    //remplissage du tableau virtuel
    int compt=0;
    while(compt<table_jeu.joueurs.size())
    {
        int compt2=0;
        while(compt2<table_jeu.joueurs.at(compt).pions.size())
        {
            //Position du pion dans le tableau virtuel
            int posx=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x/75;
            int posy=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y/75;

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-1;
                }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B_D)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-1;
                }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R)
            {
				if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-2;
                }

            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R_D)
            {
				if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-2;
                }

            }


            compt2++;
        }

        compt++;
    }

    //affichage du tableau virtuel
    /*
    int comm=0;
    while(comm<8)
    {
        int comm2=0;
        while(comm2<8)
        {
            std::cout<<tableau_virtuel[comm2][comm]<<"   ";

            comm2++;
        }

        std::cout<<"\n";
        comm++;
    }
    */


    //recherche de chemin pion simple...

       int n_chemins=1;
       int n_chemins_term=0;
       //std::cout<<"Entree dans la boucle semie infinie"<<std::endl;

       //boucle semi-infinie
       int compteur2=0;

       while(compteur2<1)
       {
           //std::cout<<"Valeur Val_a_verif: "<<val_a_verif<<std::endl;

                       if(val_a_verif==1)
                       {
                          CaseValabe eCase;
                          eCase.valeur_chemin=1;

                          int cmp=0;
                          while(cmp<8)
                          {
                              int cmp2=0;
                              while(cmp2<8)
                              {
                                  if(tableau_virtuel[cmp][cmp2]==1)
                                  {
                                       eCase.positionX=cmp;
                                       eCase.positionY=cmp2;
                                  }
                                  cmp2++;
                              }
                              cmp++;
                          }

                          eCase.lien_ch_precd=0;
                          eCase.num_chem=1;
                          eChemin.insert(eChemin.end(),eCase);

                       }


           //variable pour savoir le nombre de cases qu'on va tester
           int no_chemin=0;

           //initialisation de la variable no_chemin
           int cmp=0;
           while(cmp<8)
           {
               int cmp2=0;
               while(cmp2<8)
               {
                 if(tableau_virtuel[cmp][cmp2]==val_a_verif)
                 {
                     no_chemin++;
                 }

                 cmp2++;
               }
               cmp++;
           }

           //stockage des cases dans un nouvel vecteur
           eCasesATester.clear();
           int comp=0;
           int dern_el=eChemin.size()-1;
           int pseudo_no_ch=no_chemin;
           while(comp<no_chemin)
           {
               int ind_el=pseudo_no_ch-1;
               eCasesATester.insert(eCasesATester.end(),eChemin.at(dern_el-ind_el));
               pseudo_no_ch--;
               comp++;
           }


           int pseudo_comp=0;

           //boucle dans le tableau virtuel pour trouver la valeur a tester
           int compteur3=0;
           while(compteur3<8)
           {
               int compteur4=0;
               while(compteur4<8)
               {

                   if(tableau_virtuel[compteur3][compteur4]==val_a_verif)
                   {
                       bool dir_b_g=false;
                       bool dir_b_d=false;


                       //conditions pour savoir la direction que peut prendre le pion
                           if(!dir_b_g && compteur3>1 && compteur4<6)
                           {
                                 if(tableau_virtuel[compteur3-1][compteur4+1]==-1 && tableau_virtuel[compteur3-2][compteur4+2]>-1 && tableau_virtuel[compteur3-2][compteur4+2]<val_a_verif+1)
                                 {
                                     dir_b_g=true;
                                 }
                           }


                           if(!dir_b_d && compteur3<6 && compteur4<6)
                           {
                               if(tableau_virtuel[compteur3+1][compteur4+1]==-1 && tableau_virtuel[compteur3+2][compteur4+2]>-1 && tableau_virtuel[compteur3+2][compteur4+2]<val_a_verif+1)
                               {
                                   dir_b_d=true;
                               }
                           }

                       //.......

                       if(dir_b_g && !dir_b_d)
                           {
                               if(tableau_virtuel[compteur3-2][compteur4+2]<val_a_verif+1)
                               {
                                   tableau_virtuel[compteur3-2][compteur4+2]=val_a_verif+1;

                                   CaseValabe eCase;
                                   eCase.positionX=compteur3-2;
                                   eCase.positionY=compteur4+2;
                                   eCase.valeur_chemin=val_a_verif+1;
                                   eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.b_a_droite=false;
                                   eChemin.insert(eChemin.end(),eCase);
                               }

                           }

                           if(!dir_b_g && dir_b_d)
                           {
                               if(tableau_virtuel[compteur3+2][compteur4+2]<val_a_verif+1)
                               {
                                   tableau_virtuel[compteur3+2][compteur4+2]=val_a_verif+1;

                                   CaseValabe eCase;
                                   eCase.positionX=compteur3+2;
                                   eCase.positionY=compteur4+2;
                                   eCase.valeur_chemin=val_a_verif+1;
                                   eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.b_a_droite=true;
                                   eChemin.insert(eChemin.end(),eCase);
                               }

                           }

                           if(dir_b_g && dir_b_d)
                           {
                               if(tableau_virtuel[compteur3-2][compteur4+2]<val_a_verif+1)
                               {
                                   tableau_virtuel[compteur3-2][compteur4+2]=val_a_verif+1;

                                   CaseValabe eCase;
                                   eCase.positionX=compteur3-2;
                                   eCase.positionY=compteur4+2;
                                   eCase.valeur_chemin=val_a_verif+1;
                                   eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.b_a_droite=false;
                                   eChemin.insert(eChemin.end(),eCase);
                               }


                               if(tableau_virtuel[compteur3+2][compteur4+2]<val_a_verif+1)
                               {
                                   tableau_virtuel[compteur3+2][compteur4+2]=val_a_verif+1;

                                   CaseValabe eCase;
                                   eCase.positionX=compteur3+2;
                                   eCase.positionY=compteur4+2;
                                   eCase.valeur_chemin=val_a_verif+1;
                                   eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                                   eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem+1;
                                   eCase.b_a_droite=true;
                                   eChemin.insert(eChemin.end(),eCase);
                               }


                              n_chemins++;
                           }

                           if(!dir_b_g && !dir_b_d)
                           {
                               n_chemins_term++;
                           }

                       pseudo_comp++;
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


       //std::cout<<"Sortie de la boucle infinie "<<std::endl;
    //selection et insertion de la case d'arrivee dans eCaseChemChoisi
    int cmp=0;
    int limiteur_occur=0;
    while(cmp<eChemin.size())
    {
            if(eChemin.at(cmp).valeur_chemin==val_a_verif && limiteur_occur==0)
            {
                eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(cmp));
                sourisX=eChemin.at(cmp).positionX;
                sourisY=eChemin.at(cmp).positionY;
                possible=true;
                limiteur_occur++;
            }


        cmp++;
    }


    if(possible)
    {

    //initialisation du parcours du pion
        int pseudo_c=eChemin.size()-1;
        int comptt=0;
        while(comptt<eChemin.size())
        {
            if(eChemin.at(pseudo_c).num_chem==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).lien_ch_precd && eChemin.at(pseudo_c).valeur_chemin==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).valeur_chemin-1)
            {

                eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(pseudo_c));
            }

            pseudo_c--;
            comptt++;
        }

    //marquage des pions adverse qui seront capturer
    int nb_pions_capt=0;
    int compptt=0;
    while(compptt<eCaseChemChoisi.size()-1)
    {
            if(eCaseChemChoisi.at(compptt).b_a_droite)
            {
                int x=eCaseChemChoisi.at(compptt).positionX-1;
                int y=eCaseChemChoisi.at(compptt).positionY-1;

                int commp=0;
                while(commp<table_jeu.joueurs.at(1).pions.size())
                {
                    if(table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                    {
                        table_jeu.joueurs.at(1).pions.at(commp).capture=true;
                        nb_pions_capt++;
                    }
                    commp++;
                }
            }
            else
            {
                int x=eCaseChemChoisi.at(compptt).positionX+1;
                int y=eCaseChemChoisi.at(compptt).positionY-1;

                int commp=0;
                while(commp<table_jeu.joueurs.at(1).pions.size())
                {
                    if(table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                    {
                        table_jeu.joueurs.at(1).pions.at(commp).capture=true;
                        nb_pions_capt++;
                    }
                    commp++;
                }
            }





        compptt++;
    }

    //std::cout<<"ia Nombre de pions a capturer: "<<nb_pions_capt<<std::endl;

    //test pour savoir le nombre de pions vraiment selectionner
    int pion_v_sel=0;
    int compteurr=0;
    while(compteurr<table_jeu.joueurs.at(1).pions.size())
    {
        if(table_jeu.joueurs.at(1).pions.at(compteurr).capture)
        {
            pion_v_sel++;
        }

        compteurr++;
    }

    //std::cout<<"ia Nombre de pions a capturer vraiment: "<<pion_v_sel<<std::endl;

    }

    //std::cout<<"Sortie dans la fonction ia_PossibiliteCapture()"<<std::endl;
    return possible;
}

bool JoueurC::ia_PossibiliteCaptureDame(TableJeu &table_jeu)
{
    table_jeu=table_jeu;

    bool possible=false;

        // vecteur representant l'ensemble des cases des differents chemins
        std::vector<CaseValabe> eChemin;

        //vecteur pour stocker les cases a tester
        std::vector<CaseValabe> eCasesATester;

        //vector pour le chemin choisi
        std::vector<CaseValabe> eCaseChemChoisi;

        //valeur initial a verifier
        int val_a_verif=1;

        //creation du tableau virtuel pour tacer les chemins possibles
        int tableau_virtuel[8][8]={0};

        //....
        //remplissage du tableau virtuel
        int compt=0;
		while(compt<table_jeu.joueurs.size())
		{
			int compt2=0;
			while(compt2<table_jeu.joueurs.at(compt).pions.size())
			{
				//Position du pion dans le tableau virtuel
				int posx=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x/75;
				int posy=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y/75;

				if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B)
				{
					if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
					{
						tableau_virtuel[posx][posy]=1;
					}
					else
					{
						tableau_virtuel[posx][posy]=-1;
					}
				}

				if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B_D)
				{
					if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
					{
						tableau_virtuel[posx][posy]=1;
					}
					else
					{
						tableau_virtuel[posx][posy]=-1;
					}
				}

				if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R)
				{
					if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
					{
						tableau_virtuel[posx][posy]=1;
					}
					else
					{
						tableau_virtuel[posx][posy]=-2;
					}

				}

				if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R_D)
				{
					if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
					{
						tableau_virtuel[posx][posy]=1;
					}
					else
					{
						tableau_virtuel[posx][posy]=-2;
					}

				}


				compt2++;
			}

			compt++;
		}

    //....

        //variables de chemins pour la dame
        int n_chemins=1;
        int n_chemins_term=0;


        //boucle semi-infinie pour tracer les chemins que peut prendre le pion
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
                            if(tableau_virtuel[compt4-1][compt5-1]==-1 && tableau_virtuel[compt4-2][compt5-2]>-1 && tableau_virtuel[compt4-2][compt5-2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_h_g)
                            {
                                dir_haut_g=true;
                            }
                        }

                        if(compt4<6 && compt5>1)
                        {
                            if(tableau_virtuel[compt4+1][compt5-1]==-1 && tableau_virtuel[compt4+2][compt5-2]>-1 && tableau_virtuel[compt4+2][compt5-2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_h_d)
                            {
                                dir_haut_d=true;
                            }
                        }

                        //condition pour savoir quelle direction que peut prendre la dame en bas
                        if(compt4>1 && compt5<6)
                        {
                            if(tableau_virtuel[compt4-1][compt5+1]==-1 && tableau_virtuel[compt4-2][compt5+2]>-1 && tableau_virtuel[compt4-2][compt5+2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_b_g)
                            {
                                dir_bas_g=true;
                            }
                        }

                        if(compt4<6 && compt5<6)
                        {
                            if(tableau_virtuel[compt4+1][compt5+1]==-1 && tableau_virtuel[compt4+2][compt5+2]>-1 && tableau_virtuel[compt4+2][compt5+2]<val_a_verif+1 && !eCasesATester.at(no_case_eCaseATester).i_d_b_d)
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

        //selection et insertion de la case d'arrivee dans eCaseChemChoisi
        int cmp=0;
        int limiteur_occur=0;
        while(cmp<eChemin.size())
        {
                if(eChemin.at(cmp).valeur_chemin==val_a_verif && limiteur_occur==0)
                {
                    eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(cmp));
                    sourisX=eChemin.at(cmp).positionX;
                    sourisY=eChemin.at(cmp).positionY;
                    possible=true;
                    limiteur_occur++;
                }


            cmp++;
        }

        //si possible est vrai alors on trace le chemin choisi et on selectionne les pions qui seront capturer
        if(possible)
        {
            //intialisation du parcours du de la dame
            int pseudo_c=eChemin.size()-1;
            int compt4=0;
            while(compt4<eChemin.size())
            {
                if(eChemin.at(pseudo_c).num_chem==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).lien_ch_precd && eChemin.at(pseudo_c).valeur_chemin==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).valeur_chemin-1)
                {
                    eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(pseudo_c));
                }

                pseudo_c--;
                compt4++;
            }

            //marquage des pions adverses qui seront capturer
            int nb_pions_capt=0;
            int compt5=0;
            while(compt5<eCaseChemChoisi.size()-1)
            {
                if(eCaseChemChoisi.at(compt5).mouv_h_g)
                {
                    int x=eCaseChemChoisi.at(compt5).positionX+1;
                    int y=eCaseChemChoisi.at(compt5).positionY+1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(1).pions.size())
                    {
                        if(table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(1).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }
                else if(eCaseChemChoisi.at(compt5).mouv_h_d)
                {
                    int x=eCaseChemChoisi.at(compt5).positionX-1;
                    int y=eCaseChemChoisi.at(compt5).positionY+1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(1).pions.size())
                    {
                        if(table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(1).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }
                else if(eCaseChemChoisi.at(compt5).mouv_b_g)
                {
                    int x=eCaseChemChoisi.at(compt5).positionX+1;
                    int y=eCaseChemChoisi.at(compt5).positionY-1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(1).pions.size())
                    {
                        if(table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(1).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }
                else
                {
                    int x=eCaseChemChoisi.at(compt5).positionX-1;
                    int y=eCaseChemChoisi.at(compt5).positionY-1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(1).pions.size())
                    {
                        if(table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(1).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(1).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }

                compt5++;
            }

            //std::cout<<"ia dames Nombre de pions a capturer: "<<nb_pions_capt<<std::endl;

            //test pour savoir le nombre de pions vraiment selectionner
            int pion_v_sel=0;
            int compteurr=0;
            while(compteurr<table_jeu.joueurs.at(1).pions.size())
            {
                if(table_jeu.joueurs.at(1).pions.at(compteurr).capture)
                {
                    pion_v_sel++;
                }

                compteurr++;
            }

            //std::cout<<"ia dames Nombre de pions a capturer vraiment: "<<pion_v_sel<<std::endl;
        }

    return possible;
}

bool JoueurC::PossibiliteCapture(TableJeu &table_jeu)
{
    table_jeu=table_jeu;

    bool possible=false;

        // vecteur representant l'ensemble des cases des differents chemins
        std::vector<CaseValabe> eChemin;

        //vecteur pour stocker les cases a tester
        std::vector<CaseValabe> eCasesATester;

        //vector pour le chemin choisi
        std::vector<CaseValabe> eCaseChemChoisi;

        //valeur initial a verifier
        int val_a_verif=1;

    //creation du tableau virtuel pour tacer les chemins possibles
    int tableau_virtuel[8][8]={0};



    //remplissage du tableau virtuel
    int compt=0;
    while(compt<table_jeu.joueurs.size())
    {
        int compt2=0;
        while(compt2<table_jeu.joueurs.at(compt).pions.size())
        {
            //Position du pion dans le tableau virtuel
            int posx=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x/75;
            int posy=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y/75;

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-1;
                }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B_D)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-1;
                }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R)
            {
                    tableau_virtuel[posx][posy]=-2;
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R_D)
            {
                    tableau_virtuel[posx][posy]=-2;
            }


            compt2++;
        }

        compt++;
    }

    //recherche de chemin pion simple...

       int n_chemins=1;
       int n_chemins_term=0;

       //boucle semi-infinie
       int compteur2=0;

       while(compteur2<1)
       {

                       if(val_a_verif==1)
                       {
                          CaseValabe eCase;
                          eCase.valeur_chemin=1;

                          int cmp=0;
                          while(cmp<8)
                          {
                              int cmp2=0;
                              while(cmp2<8)
                              {
                                  if(tableau_virtuel[cmp][cmp2]==1)
                                  {
                                       eCase.positionX=cmp;
                                       eCase.positionY=cmp2;
                                  }
                                  cmp2++;
                              }
                              cmp++;
                          }

                          eCase.lien_ch_precd=0;
                          eCase.num_chem=1;
                          eChemin.insert(eChemin.end(),eCase);

                       }


           //variable pour savoir le nombre de cases qu'on va tester
           int no_chemin=0;

           //initialisation de la variable no_chemin
           int cmp=0;
           while(cmp<8)
           {
               int cmp2=0;
               while(cmp2<8)
               {
                 if(tableau_virtuel[cmp][cmp2]==val_a_verif)
                 {
                     no_chemin++;
                 }

                 cmp2++;
               }
               cmp++;
           }

           //stockage des cases dans un nouvel vecteur
           eCasesATester.clear();
           int comp=0;
           int dern_el=eChemin.size()-1;
           int pseudo_no_ch=no_chemin;
           while(comp<no_chemin)
           {
               int ind_el=pseudo_no_ch-1;
               eCasesATester.insert(eCasesATester.end(),eChemin.at(dern_el-ind_el));
               pseudo_no_ch--;
               comp++;
           }


           int pseudo_comp=0;

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

                               CaseValabe eCase;
                               eCase.positionX=compteur3-2;
                               eCase.positionY=compteur4-2;
                               eCase.valeur_chemin=val_a_verif+1;
                               eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.a_droite=false;
                               eChemin.insert(eChemin.end(),eCase);
                           }

                       }

                       if(!dir_gauche && dir_droite)
                       {
                           if(tableau_virtuel[compteur3+2][compteur4-2]<val_a_verif+1)
                           {
                               tableau_virtuel[compteur3+2][compteur4-2]=val_a_verif+1;

                               CaseValabe eCase;
                               eCase.positionX=compteur3+2;
                               eCase.positionY=compteur4-2;
                               eCase.valeur_chemin=val_a_verif+1;
                               eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.a_droite=true;
                               eChemin.insert(eChemin.end(),eCase);
                           }

                       }

                       if(dir_gauche && dir_droite)
                       {
                           if(tableau_virtuel[compteur3-2][compteur4-2]<val_a_verif+1)
                           {
                               tableau_virtuel[compteur3-2][compteur4-2]=val_a_verif+1;

                               CaseValabe eCase;
                               eCase.positionX=compteur3-2;
                               eCase.positionY=compteur4-2;
                               eCase.valeur_chemin=val_a_verif+1;
                               eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.a_droite=false;
                               eChemin.insert(eChemin.end(),eCase);
                           }


                           if(tableau_virtuel[compteur3+2][compteur4-2]<val_a_verif+1)
                           {
                               tableau_virtuel[compteur3+2][compteur4-2]=val_a_verif+1;

                               CaseValabe eCase;
                               eCase.positionX=compteur3+2;
                               eCase.positionY=compteur4-2;
                               eCase.valeur_chemin=val_a_verif+1;
                               eCase.lien_ch_precd=eCasesATester.at(pseudo_comp).num_chem;
                               eCase.num_chem=eCasesATester.at(pseudo_comp).num_chem+1;
                               eCase.a_droite=true;
                               eChemin.insert(eChemin.end(),eCase);
                           }


                          n_chemins++;
                       }

                       if(!dir_gauche && !dir_droite)
                       {
                           n_chemins_term++;
                       }

                       pseudo_comp++;
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


    //selection et insertion de la case d'arrivee dans eCaseChemChoisi
    int cmp=0;
    while(cmp<eChemin.size())
    {
        if(eChemin.at(cmp).positionX==sourisX/75 && eChemin.at(cmp).positionY==sourisY/75 && eChemin.at(cmp).valeur_chemin==val_a_verif)
        {
            eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(cmp));
            possible=true;
        }
        cmp++;
    }

    if(possible)
    {

    //initialisation du parcours du pion
        int pseudo_c=eChemin.size()-1;
        int comptt=0;
        while(comptt<eChemin.size())
        {
            if(eChemin.at(pseudo_c).num_chem==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).lien_ch_precd && eChemin.at(pseudo_c).valeur_chemin==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).valeur_chemin-1)
            {

                eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(pseudo_c));
            }

            pseudo_c--;
            comptt++;
        }

    //marquage des pions adverse qui seront capturer
    int nb_pions_capt=0;
    int compptt=0;
    while(compptt<eCaseChemChoisi.size()-1)
    {
        if(eCaseChemChoisi.at(compptt).a_droite)
        {
            int x=eCaseChemChoisi.at(compptt).positionX-1;
            int y=eCaseChemChoisi.at(compptt).positionY+1;

            int commp=0;
            while(commp<table_jeu.joueurs.at(0).pions.size())
            {
                if(table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                {
                    table_jeu.joueurs.at(0).pions.at(commp).capture=true;
                    nb_pions_capt++;
                }
                commp++;
            }
        }

        if(!eCaseChemChoisi.at(compptt).a_droite)
        {
            int x=eCaseChemChoisi.at(compptt).positionX+1;
            int y=eCaseChemChoisi.at(compptt).positionY+1;

            int commp=0;
            while(commp<table_jeu.joueurs.at(0).pions.size())
            {
                if(table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                {
                    table_jeu.joueurs.at(0).pions.at(commp).capture=true;
                    nb_pions_capt++;
                }
                commp++;
            }
        }

        compptt++;
    }
    //std::cout<<"Nombre de pions a capturer: "<<nb_pions_capt<<std::endl;
    //test pour savoir le nombre de pions vraiment selectionner
    int pion_v_sel=0;
    int compteurr=0;
    while(compteurr<table_jeu.joueurs.at(0).pions.size())
    {
        if(table_jeu.joueurs.at(0).pions.at(compteurr).capture)
        {
            pion_v_sel++;
        }

        compteurr++;
    }

    //std::cout<<"Nombre de pions a capturer vraiment: "<<pion_v_sel<<std::endl;

    }

    return possible;
}

bool JoueurC::PossibiliteCaptureDame(TableJeu &table_jeu)
{
    table_jeu=table_jeu;
    bool possible=false;

        // vecteur representant l'ensemble des cases des differents chemins
        std::vector<CaseValabe> eChemin;

        //vecteur pour stocker les cases a tester
        std::vector<CaseValabe> eCasesATester;

        //vector pour le chemin choisi
        std::vector<CaseValabe> eCaseChemChoisi;

        //valeur initial a verifier
        int val_a_verif=1;

        //creation du tableau virtuel pour tacer les chemins possibles
        int tableau_virtuel[8][8]={0};

        //....
        //remplissage du tableau virtuel
        int compt=0;
    while(compt<table_jeu.joueurs.size())
    {
        int compt2=0;
        while(compt2<table_jeu.joueurs.at(compt).pions.size())
        {
            //Position du pion dans le tableau virtuel
            int posx=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().x/75;
            int posy=table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y/75;

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-1;
                }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B_D)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).selectionne==true)
                {
                    tableau_virtuel[posx][posy]=1;
                }
                else
                {
                    tableau_virtuel[posx][posy]=-1;
                }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R)
            {
                    tableau_virtuel[posx][posy]=-2;
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R_D)
            {
                    tableau_virtuel[posx][posy]=-2;
            }


            compt2++;
        }

        compt++;
    }
    //....

        //variables de chemins pour la dame
        int n_chemins=1;
        int n_chemins_term=0;


        //boucle semi-infinie pour tracer les chemins que peut prendre le pion
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

        //selection et insertion de la case d'arrivee dans eCaseChemChoisi
        int compt3=0;
        while(compt3<eChemin.size())
        {
            if(eChemin.at(compt3).positionX==sourisX/75 && eChemin.at(compt3).positionY==sourisY/75 && eChemin.at(compt3).valeur_chemin==val_a_verif)
            {

                eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(compt3));
                possible=true;
            }

            compt3++;
        }

        //si possible est vrai alors on trace le chemin choisi et on selectionne les pions qui seront capturer
        if(possible)
        {
            //intialisation du parcours du de la dame
            int pseudo_c=eChemin.size()-1;
            int compt4=0;
            while(compt4<eChemin.size())
            {
                if(eChemin.at(pseudo_c).num_chem==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).lien_ch_precd && eChemin.at(pseudo_c).valeur_chemin==eCaseChemChoisi.at(eCaseChemChoisi.size()-1).valeur_chemin-1)
                {
                    eCaseChemChoisi.insert(eCaseChemChoisi.end(),eChemin.at(pseudo_c));
                }

                pseudo_c--;
                compt4++;
            }

            //marquage des pions adverses qui seront capturer
            int nb_pions_capt=0;
            int compt5=0;
            while(compt5<eCaseChemChoisi.size()-1)
            {
                if(eCaseChemChoisi.at(compt5).mouv_h_g)
                {
                    int x=eCaseChemChoisi.at(compt5).positionX+1;
                    int y=eCaseChemChoisi.at(compt5).positionY+1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(0).pions.size())
                    {
                        if(table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(0).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }
                else if(eCaseChemChoisi.at(compt5).mouv_h_d)
                {
                    int x=eCaseChemChoisi.at(compt5).positionX-1;
                    int y=eCaseChemChoisi.at(compt5).positionY+1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(0).pions.size())
                    {
                        if(table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(0).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }
                else if(eCaseChemChoisi.at(compt5).mouv_b_g)
                {
                    int x=eCaseChemChoisi.at(compt5).positionX+1;
                    int y=eCaseChemChoisi.at(compt5).positionY-1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(0).pions.size())
                    {
                        if(table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(0).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }
                else
                {
                    int x=eCaseChemChoisi.at(compt5).positionX-1;
                    int y=eCaseChemChoisi.at(compt5).positionY-1;

                    int commp=0;
                    while(commp<table_jeu.joueurs.at(0).pions.size())
                    {
                        if(table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().x==x*75+37.5 && table_jeu.joueurs.at(0).pions.at(commp).s_pion.getPosition().y==y*75+37.5)
                        {
                            table_jeu.joueurs.at(0).pions.at(commp).capture=true;
                            nb_pions_capt++;

                        }
                        commp++;
                    }
                }

                compt5++;
            }

            //std::cout<<"Nombre de pions a capturer: "<<nb_pions_capt<<std::endl;
            //test pour savoir le nombre de pions vraiment selectionner
            int pion_v_sel=0;
            int compteurr=0;
            while(compteurr<table_jeu.joueurs.at(0).pions.size())
            {
                if(table_jeu.joueurs.at(0).pions.at(compteurr).capture)
                {
                    pion_v_sel++;
                }

                compteurr++;
            }

            //std::cout<<"Nombre de pions a capturer vraiment: "<<pion_v_sel<<std::endl;
        }

    return possible;
}

void JoueurC::PromotionPion(TableJeu &table_jeu)
{
    table_jeu=table_jeu;

    int compt=0;
    while(compt<table_jeu.joueurs.size())
    {
        int compt2=0;
        while(compt2<table_jeu.joueurs.at(compt).pions.size())
        {
            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_B)
            {
               if(table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y==37.5)
               {
                   table_jeu.joueurs.at(compt).pions.at(compt2).type_pion=pion_B_D;
               }
            }

            if(table_jeu.joueurs.at(compt).pions.at(compt2).type_pion==pion_R)
            {
                if(table_jeu.joueurs.at(compt).pions.at(compt2).s_pion.getPosition().y==562.5)
                {
                    table_jeu.joueurs.at(compt).pions.at(compt2).type_pion=pion_R_D;
                }
            }

            compt2++;
        }

        compt++;
    }
}

void JoueurC::CapturePion(TableJeu &table_jeu,int joueur)
{
    table_jeu=table_jeu;

	int joueur_actif=0;
	 int joueur_passif=0;

	 joueur_actif=joueur;

	 if(joueur_actif==0)
	 {
		 joueur_passif=1;
	 }
	 else
		 joueur_passif=0;


		 /*
    //effacement des pions capture
    int pseudo_cmp=table_jeu.joueurs.at(joueur_passif).pions.size()-1;
    int nb_pion_sup=0;
    int compt=0;
    while(compt<table_jeu.joueurs.at(joueur_passif).pions.size())
    {
        if(table_jeu.joueurs.at(joueur_passif).pions.at(pseudo_cmp).capture)
        {
            table_jeu.joueurs.at(joueur_passif).pions.erase(table_jeu.joueurs.at(joueur_passif).pions.begin()+pseudo_cmp);
            nb_pion_sup++;

        }
        pseudo_cmp--;
        compt++;
    }
    std::cout<<"Nombre de pions supprimes: "<<nb_pion_sup<<std::endl;
    */


    //test pour savoir le nombre de pions vraiment selectionner
    int pion_v_sel=0;
    int compteurr=0;
    while(compteurr<table_jeu.joueurs.at(joueur_passif).pions.size())
    {
        if(table_jeu.joueurs.at(joueur_passif).pions.at(compteurr).capture)
        {
            pion_v_sel++;
        }

        compteurr++;
    }

    //std::cout<<"Nombre de pions a capturer vraiment: "<<pion_v_sel<<std::endl;

    //boucle semie infinie
    int nb_pion_sup=0;
    int compteur=0;
    while(compteur<1)
    {
        int pseudo_cmp=0;

        int compt=0;
        while(compt<table_jeu.joueurs.at(joueur_passif).pions.size())
        {
            if(table_jeu.joueurs.at(joueur_passif).pions.at(pseudo_cmp).capture)
            {
                table_jeu.joueurs.at(joueur_passif).pions.erase(table_jeu.joueurs.at(joueur_passif).pions.begin()+pseudo_cmp);
                nb_pion_sup++;
                pseudo_cmp--;

            }
            pseudo_cmp++;
            compt++;
        }

        if(pion_v_sel==nb_pion_sup)
        {
            compteur++;
        }
    }



    //std::cout<<"Nombre de pions supprimes: "<<nb_pion_sup<<std::endl;
}

Joueur JoueurC::getJoueur(int nJ)
{
    if(nJ==1)
    {
        return m_joueur_1;
    }

    if(nJ==2)
    {
        return m_joueur_2;
    }
}


void JoueurC::DeplacementSimplePion(TableJeu &table_jeu)
 {
   int cmpt=0;
     while(cmpt<table_jeu.joueurs.at(1).pions.size())
     {
         if(table_jeu.joueurs.at(1).pions.at(cmpt).selectionne==true)
         {

             if(JeuPossibleSimplePion(table_jeu))
             {
                 int posiX=sourisX/75;
                 int posiY=sourisY/75;
               table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.setPosition(posiX*75+37.5,posiY*75+37.5);
               LA_MAIN=false;
             }


             table_jeu.joueurs.at(1).pions.at(cmpt).selectionne=false;
             selec_valide=false;

         }

         cmpt++;
     }
 }

void JoueurC::DeplacementDame(TableJeu &table_jeu)
{
    int cmpt=0;
     while(cmpt<table_jeu.joueurs.at(1).pions.size())
     {
         if(table_jeu.joueurs.at(1).pions.at(cmpt).selectionne==true)
         {
             //quand il n'y a pas de pions a capturer
             if(JeuPossibleDame(table_jeu))
             {
                 int posiX=sourisX/75;
                 int posiY=sourisY/75;

               table_jeu.joueurs.at(1).pions.at(cmpt).s_pion.setPosition(posiX*75+37.5,posiY*75+37.5);
               LA_MAIN=false;
             }

             //quand il y a des pions a capturer

             table_jeu.joueurs.at(1).pions.at(cmpt).selectionne=false;
             selec_valide=false;


         }

         cmpt++;
     }
}



JoueurC::~JoueurC()
{
}
