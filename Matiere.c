#include <stdio.h>
#include <stdlib.h>
#include "Matiere.h"
#include "Student.h"
//#define N 3

//MATIERE Matiere[N];

MATIERE SaisieMat()
{
    MATIERE Mat;
    int t=0, t2=0, choix;
    /*----------------CONTROLE DE SAISIE----------------------------------*/
    do
    {
        if(t==1)
        {
            Mat.Nom[0]='\0';
            printf("Cette matiere existe deja ou Le code est deja utilisé!!!\n");
            //Controle de saisie et option de sortie
            do
            {
                if(t2==1) printf("Choix Invalide!!!\n");
                printf("Voulez vous recomencer?\t\t<OUI>1\t<NON>-1\n_");
                scanf("%d", &choix);
                t2=1;
            }
            while(choix!=1 && choix!=-1);
            if(choix==-1) return;       //On sort completement de la fonction
        }
        fflush(stdin);
        printf("Nom de la Matiere : ");
        fgets(Mat.Nom, 20, stdin);
        printf("Code : ");
        fgets(Mat.Code, 5, stdin);
        t=1;
    }
    while(MatiereExist(Mat.Code, Mat.Nom));
    /*-----------------------------------------------------------------------*/
    printf("Credits : ");
    scanf("%d", &Mat.Credits);

    return Mat;
}

void Saisie_Matiere()
{
    FILE *f=fopen("fmate.ing", "a");
    MATIERE Mat;
    int choix=1;

    printf("*********************SAISIE DES MATIERE***************************\n");
    while (choix==1)
    {
        Mat=SaisieMat();
        if(Mat.Nom[0]!='\0')
        {
            fwrite(&Mat, sizeof(Mat), 1, f);
            printf("Enregistré.\n");
        }
        //Controle de saisie et option de sortie.
        do
        {
            printf("Voulez vous continuer la saisie?\t\t<Oui>:1\t<Non>:-1\n_");
            scanf("%d", &choix);
        }
        while(choix!=1 && choix!=-1);
    }
    fclose(f);
}

void Liste_Matiere()
{
    FILE *f=fopen("fmate.ing", "r");
    MATIERE Mat;
    if(Vide("fmate.ing")==1)
        printf("Aucune matiere enregistre!!\n");
    else
    {
        while(fread(&Mat, sizeof(Mat), 1, f)!=0)
        {
            printf("Nom : %sCode : %sCredits : %d\n", Mat.Nom, Mat.Code, Mat.Credits);
            printf("----------------------------------------------------------------------\n");
        }
    }
    fclose(f);
}
