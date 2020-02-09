#ifndef DEF_ENUMS
#define DEF_ENUMS

enum{col_A,col_B,col_C,col_D,col_E,col_F,col_G,col_H};
enum{rang_1,rang_2,rang_3,rang_4,rang_5,rang_6,rang_7,rang_8};
enum{pion_R,pion_B,pion_R_D,pion_B_D};
enum{CPU,HUMAIN,HUMAIN2};

enum TypeMenu
{
    MenuPrincipale,
    MenuNvlPartie,
    MenuInstructions,
    MenuApropos
};

enum TypeJeu
{
    HUMAINvsHUMAIN,
    HUMAINvsIA
};

enum
{
    AUCUN_EL_ACT,
    NP_ACTIF,
    I_ACTIF,
    AP_ACTIF,
    Q_ACTIF,
    JHvsH_ACTIF,
    JHvsIA_ACTIF,
    R_ACTIF
};

enum EtatH
{
    Demarre,
    EnPause
};



#endif // DEF_ENUMS
