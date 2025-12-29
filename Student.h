#ifndef H_STUDENT_H

struct DATE
{
    int jour;
    int Mois;
    int Annee;
};
typedef struct DATE Date;

struct ETUDIANT
{
    char Mat[10];
    char Nom[20];
    Date DateNais;
    char Sexe;
    char Filiere[20];
};
typedef struct ETUDIANT ETUDIANT;

/*-------PROTOTYPES-----------*/
ETUDIANT Saisie_Etudiant();
void SaisieEtudiant();
int Affichage(int x, int y, int C);
void MENU();

#endif // H_STUDENT_H
