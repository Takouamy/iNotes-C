#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include "Style.h"
#define CADRE_X 10
#define CADRE_Y 5

Date SaisieDate()
{
    Date DateNais;
    printf("Date de naissance(numeros)\n");
    printf("Annee : ");
    DateNais.Annee=ControleAnnee();
    if (DateNais.Annee%4==0 && DateNais.Annee%100!=0) //Annee bisextille
    {
        printf("Mois : ");
        DateNais.Mois=ControleMois();
        if(DateNais.Mois==2)
        {
            printf("Jour : ");
            DateNais.jour=Controle(1, 29);
        }
        else
        {
            if(DateNais.Mois%2==0) //Les mois a 30 jours
            {
                printf("Jour : ");
                DateNais.jour=Controle(1, 30);
            }
            else
            {
                printf("Jour : ");
                DateNais.jour=Controle(1, 31);
            }
        }
    }
    else
    {
        printf("Mois : ");
        DateNais.Mois=ControleMois();
        if(DateNais.Mois==2)
        {
            printf("Jour : ");
            DateNais.jour=Controle(1, 29);
        }
        else
        {
            if(DateNais.Mois%2==0) //Les mois a 30 jours
            {
                printf("Jour : ");
                DateNais.jour=Controle(1, 30);
            }
            else
            {
                printf("Jour : ");
                DateNais.jour=Controle(1, 31);
            }
        }
    }
    return DateNais;
}
ETUDIANT Saisie_Etudiant()
{
    ETUDIANT Etud;
    int t=0, a=0, choix;
    /*---------------------------------CONTROLE DE SAISIE------------------------------*/
    do
    {
        if(t==1)
        {
            do
            {
                printf("Voulez voulez vous continuez?\t<OUI>1   <NON>-1 : ");
                scanf("%d", &choix);
                if(choix==1)
                    break;
                else if (choix==-1)
                    return;         //On sort de la fonction
            }
            while(choix!=1 && choix!=-1);//*/
        }
        fflush(stdin);
        printf("Nom : ");
        fgets(Etud.Nom, 20, stdin);
        fflush(stdin);
        printf("Matricule : ");
        fgets(Etud.Mat, 10, stdin);
        t=1;
    }
    while(EtudiantExist(Etud.Mat, Etud.Nom)==1);
    /*---------------------------------------------------------------------------------*/

    Etud.DateNais=SaisieDate();
    printf("Sexe : ");
    do{
        if(a==1)printf("Le sexe est soit M ou F\nReessaier_");
        fflush(stdin);
        scanf("%c", &Etud.Sexe);
        a=1;
    }while(Etud.Sexe!='M' && Etud.Sexe!='F');
    scanf("%c", &Etud.Sexe);
    fflush(stdin);
    printf("Filiere : ");
    fgets(Etud.Filiere, 20, stdin);
    printf("%s\n", Etud.Filiere);
    return Etud;
}

void Save_Etudiant(ETUDIANT E)
{
    FILE *f;
    f=fopen("fetude.ing", "a+");
    if(f==NULL)
        printf("Probleme d'ouverture du fichier");
    else
    {
        fwrite(&E, sizeof(E), 1, f);
    }
    fclose(f);
}

void SaisieEtudiant()
{
    ETUDIANT E;
    int ch;
    printf("********************ENREGISTREMENT DES ETUDIANTS******************************\n");
    do
    {
        E=Saisie_Etudiant();
        if(E.Filiere[0]!='\0')      //Si tous les infos ons bien ete remplis
        {
            //Enregistrement des Etudiants
            Save_Etudiant(E);
        }
        printf("\nVoulez vous continuer la saisie?\t1:Continuer\t\t-1:Quiiter\n");
        scanf("%d", &ch);
    }
    while(ch!=-1);
}

int Affichage(int x, int y, int C)
{
    int ch;
    char Menu[11][50]= {"1-Saisie Etudiant", "2-Liste Etudiant", "3-Saisie Matiere", "4-Liste Matiere","5-Saisie Notes","6-Afficher Notes","7-Moyenne des etudiant d'une classe","8-Modifier Note","9-Suprimer Note","10-Relever de note d'un etudiant","11-Quitter"};
    color(C, 0);
    int c;
    int cpt=0;
    do
    {
        gotoxy(x+1,y+1);printf("<---------MENU---------->\n");
        for(int i=0; i<11; i++)
        {
            if(i==cpt){color(C, 6);gotoxy(x+1, y+2+i);printf("%s\n",Menu[i]);}
            else{ color(C, 0);gotoxy(x+1, y+2+i);printf("%s\n",Menu[i]);}
        }
        c=getch();
        if(c==80)
        {
            if(cpt<11-1) cpt++;
        }
        else if(c==72)
        {
            if(cpt>0) cpt--;
        }
    }
    while(c!=13);
    //printf("Votre Choix : ");
    // scanf("%d", &ch);

    return cpt+1;
}

void Cadre(int x1, int x2, int y1, int y2, int C)
{
    color(C, 0);
    for(int i=x1; i<x2; i++)
    {
        gotoxy(i, y1);
        printf("%c", 196);
        gotoxy(i, y2);
        printf("%c", 196);
    }
    for(int i=y1; i<y2; i++)
    {
        gotoxy(x1, i);
        printf("%c", 179);
        gotoxy(x2, i);
        printf("%c", 179);
    }
    gotoxy(x1, y1);
    printf("%c", 218);
    gotoxy(x2, y1);
    printf("%c", 191);
    gotoxy(x1, y2);
    printf("%c", 192);
    gotoxy(x2, y2);
    printf("%c", 217);
}
void MENU()
{
    int choix;
    do
    {
        system("cls");
        Cadre(CADRE_X, 50, CADRE_Y, 30, 2);
        choix=Affichage(10, 10, 15);
        switch(choix)
        {
        case 1:
            system("cls");
            SaisieEtudiant();
            system("pause");
            break;
        case 2:
            system("cls");
            Liste_Etudiant();
            system("pause");
            break;
        case 3:
            system("cls");
            Saisie_Matiere();
            system("pause");
            break;
        case 4:
            system("cls");
            Liste_Matiere();
            system("pause");
            break;
        case 5:
            system("cls");
            Saisie_Note();
            system("pause");
            break;
        case 6:
            system("cls");
            AfficheNote();
            system("pause");
            break;
        case 7:
            system("cls");
            Affiche_Moyennes();
            system("pause");
            break;
        case 8:
            system("cls");
            Modif_Note();
            system("pause");
            break;
        case 9:
            system("cls");
            Suprim_Note();
            system("pause");
            break;
        case 10:
            system("cls");
            PV();
            break;
        case 11:
            gotoxy(CADRE_X+1, CADRE_Y+20);color(15, 0);printf("Au revoir;)\n");
            gotoxy(CADRE_X+1, CADRE_Y+21);system("pause");
            break;
        default:
            printf("Choix INVELIDE!!!\n");
            system("pause");
            break;
        }
    }
    while(choix!=11);
}

void Liste_Etudiant()
{
    FILE *f;
    ETUDIANT E;

    f=fopen("fetude.ing", "r");
    if (f==NULL)
        printf("Probleme d'ouverture\n");
    else
    {
        if(Vide("fetud.ing")==1)
            printf("Aucun etudiant enregistre!!\n");
        else
        {
            printf("********LISTE D'ETUDIANTS***************\n");
            while(feof(f)==0 && fread(&E, sizeof(E), 1, f)!=0)
            {
                printf("--------------------------------------\n");
                printf("Matricule : %sNom : %sSexe : %c\nFilliere : % s", E.Mat, E.Nom, E.Sexe, E.Filiere);   //Pas de"\n" parce que fgets prends "la mise a la ligne"
            }
        }
    }
    fclose(f);
}

