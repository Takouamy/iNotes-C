#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"
#include "Matiere.h"
#include "Note.h"
#include "Controles.h"
#define N 3     //Nombre de sequence

NOTE SaisieNote()
{
    NOTE Note;
    int t=0, t2=0, t3=0, choix;
    do
    {
        t2=0;
        if(t==1)
        {
            Note.matcode[0]='\0';
            do
            {
                if(t2==1) printf("Choix invalid!!\n");
                printf("Voulez vous recommencer?\t <OUI>1\t<NON>-1\n_");
                scanf("%d", &choix);
                t2=1;
            }
            while(choix!=1 && choix!=-1);
            if(choix==-1) return;
        }

        do
        {
            t2=0;
            if(t3==1)
            {
                printf("Cet etudiant n'exist pas\n");
                Note.matEtud[0]='\0';
                do
                {
                    if(t2==1) printf("Choix invalid!!\n");
                    printf("Voulez vous recommencer?\t <OUI>1\t<NON>-1\n_");
                    scanf("%d", &choix);
                    t2=1;
                }
                while(choix!=1 && choix!=-1);
                if(choix==-1) return;
            }
            fflush(stdin);
            printf("\nMatricule de l'etudiant : ");
            fgets(Note.matEtud, 10, stdin);
            t3=1;
        }
        while(EtudExist(Note.matEtud)==0);
        t3=0;
        do
        {
            t2=0;
            if(t3==1)
            {
                printf("Cette matiere n'existe pas\n");
                Note.matcode[0]='\0';
                do
                {
                    if(t2==1) printf("Choix invalid!!\n");
                    printf("Voulez vous recommencer?\t <OUI>1\t<NON>-1\n_");
                    scanf("%d", &choix);
                    t2=1;
                }
                while(choix!=1 && choix!=-1);
                if(choix==-1) return;
            }
            fflush(stdin);
            printf("Code de la matiere : ");
            fgets(Note.matcode, 5, stdin);
            t3=1;
        }
        while(MatExist(Note.matcode)==0);
        do
        {
            printf("Numero de sequence : ");
            scanf("%d", &Note.seq);
        }
        while(Note.seq<=0);
        t=1;
    }
    while(NoteExist(Note.matcode, Note.matEtud, Note.seq)==1);
    do
    {
        printf("Note : ");
        scanf("%f", &Note.note);
    }
    while(Note.note<0 || Note.note>20);
    return Note;
}
void Saisie_Note()
{
    FILE *f=fopen("fnote.ing", "a");
    NOTE Note;
    int choix=0, t=0;

    //Controle de sasie, car si il n'y a pas d'etudiant ou de matiere, il ne saurais avoir de notes
    if(Vide("fetude.ing")==1)
    {
        printf("Il n'y a aucun etudiant enregistré.\n");
        if(Vide("fmate.ing")==1)
        {
            printf("Il ny'a aucune matiere enregistré.\n");
        }
    }
    else
    {
        if (f==NULL)
            printf("PROBLEME D'OUVERTURE DE \"fnote.ing\"!!!\n");
        else
        {
            while(choix!=-1)
            {
                t=0;
                Note=SaisieNote();      //Saisie de la note
                if(Note.matcode[0]!='\0' && Note.matEtud[0]!='\0')       //Controle de saisie de la "saisie des notes"
                {
                    fwrite(&Note, sizeof(Note), 1, f);
                    do
                    {
                        if(t==1)
                            printf("Valeur Invalid");
                        fflush(stdin);
                        printf("Voulez vous continue ?\t\t<Oui>:1\t<Non>:-1");      //Option de sortie
                        scanf("%d", &choix);
                        if(choix!=-1 && choix!=1)
                            t=1;
                    }
                    while(choix!=-1 && choix!=1);       //Controle de saisie
                }
                else choix = -1;    //Sortie forceé
            }
        }
    }

    fclose(f);
}
float TrouveNote(char MatEtud[], char CodeMat[], int Seq)
{
    FILE *f=fopen("fnote.ing", "r");
    NOTE Note;
    float note=-1;
    if(f==NULL)
    {
        printf("PROBLEME D'OUVERTURE DE \"fnote.ing\" dans \"TrouveNote\"!!!\n");
    }
    else
    {
        if(Vide("fnote.ing")==1)
        {
            printf("Le fichier est vide\n");
            return -1;
        }
        else
        {
            while(!feof(f) && fread(&Note, sizeof(Note), 1, f)!=0)
            {
                if(strcmp(Note.matEtud, MatEtud)==0 && strcmp(Note.matcode, CodeMat)==0 && Note.seq==Seq)
                {
                    //printf("Entree\n");
                    note=Note.note;
                    break;
                }
                note=-1;
            }
            fclose(f);
            return note;
        }

    }

    fclose(f);
}
void AfficheNotesEtuds()
{
    FILE *f=fopen("fetude.ing", "r"), *g=fopen("fmate.ing", "r");
    ETUDIANT E;
    MATIERE Mat;
    float Note;

    if (f==NULL || g==NULL)
    {

        if(f==NULL)
            printf("PROBLEME D'OUVERTURE DE \"fetude.ing\"!!!\n");
        else
            printf("PROBLEME D'OUVERTURE DE \"fmate.ing\"!!!\n");
    }
    else
    {
        if(Vide("fetude.ing")==1)
            printf("Aucune note enregistre!!\n");
        else
        {
            while(!feof(f) && fread(&E, sizeof(E), 1, f)!=0)
            {

                printf("**************ETUDIANT %s***************\n", E.Nom);
                rewind(g);
                while(!feof(g) && fread(&Mat, sizeof(Mat), 1, g)!=0)
                {
                    for(int i=0; i<N; i++)
                    {
                        Note=TrouveNote(E.Mat, Mat.Code, i+1);
                        //Affichage
                        if(Note>=0)
                        {
                            printf("----------------------------------------------\nSequence : %d\nMatiere : %sNote : %f\n", i+1, Mat.Nom, Note);
                        }
                        else
                        {
                            printf("----------------------------------------------\nSequence : %d\nMatiere : %sNote : INVALIDE\n", i+1,Mat.Nom);
                        }
                    }
                }
            }
        }
    }
    fclose(g);
    fclose(f);
}
void AfficheNote()
{
    int choix, t=0, Seq;
    float Note;
    char MatEtud[10], CodeMat[5];
    if(Vide("fetude.ing")==1)
        printf("Il y'a aucune note enregistre\n");
    else
    {
        do
        {
            if(t==1)
                printf("Choix Invalid!!!\n");
            printf("1-Note d'un Etudiant\n2-Notes de tous les etudiant\n\tVotre choix : ");
            scanf("%d", &choix);
            if(choix!=1 && choix!=2)
                t=1;
        }
        while(choix!=1 && choix!=2);

        if(choix==1)
        {
            fflush(stdin);
            printf("Entrer le matricule de l'etudiant : ");
            fgets(MatEtud, 10, stdin);
            printf("Entrer le code de la matiere : ");
            fgets(CodeMat, 5, stdin);
            printf("Entrer la sequence : ");
            scanf("%d", &Seq);
            Note=TrouveNote(MatEtud, CodeMat, Seq);
            printf("Note : %f\n", Note);
        }
        else
        {
            AfficheNotesEtuds();
        }
    }
}
Moyen MoyEtud(char Matri[], int Seq)
{
    FILE *f=fopen("fmate.ing", "r");
    MATIERE Mat;
    float note, Som=0;
    int cpt=0, SommeCredits=0;
    Moyen Moy;

    if (f==NULL)
        printf("PROBLEME D'OUVETURE DE \"fmate.ing\" dans \"MoyEtud\"\n ");
    else
    {
        while(fread(&Mat, sizeof(Mat), 1, f)!=0)
        {
            note=TrouveNote(Matri, Mat.Code, Seq);
            if(note>=0)
            {
                Som=Som + note*Mat.Credits;
                SommeCredits = SommeCredits + Mat.Credits;
                cpt++;
            }
        }
    }
    Moy.Nombres=cpt;
    if(cpt>0)
        Moy.Valeur=Som/SommeCredits;
    else Moy.Valeur=-1;
    fclose(f);

    return Moy;
}

void Affiche_Moyennes()
{
    FILE *f=fopen("fetude.ing", "r"), *g=fopen("fmate.ing", "r");
    ETUDIANT Etud;
    //MATIERE Mat;
    Moyen Moy;

    char Matri[10];
    float Somme, SommeCredits;
    int choix, Seq, t=0;

    printf("**************MOYENNE DES ETUDIANTS D'UNE CLASSE***************\n");
    if(Vide("fetude.ing")==1)
    {
        printf("Il n'y a aucun etudiant enregistré.\n");
        if(Vide("fmate.ing")==1)
        {
            printf("Il ny'a aucune matiere enregistré.\n");
            if(Vide("fnote.ing")==1)
                printf("Il n'y a aucune note enregistre.\n");
        }
    }
    else
    {
        if (f==NULL || g==NULL)
        {

            if(f==NULL)
                printf("PROBLEME D'OUVERTURE DE \"fetude.ing\"!!!\n");
            else
                printf("PROBLEME D'OUVERTURE DE \"fmate.ing\"!!!\n");
        }
        else
        {
            do
            {
                if(t==1)
                    printf("Choix Invalid!\n");
                printf("\n1-Moyen d'un Etudiant\n2-Moyende de la classe");
                scanf("%d", &choix);
                t=1;
            }
            while(choix!=1 && choix!=2);

            if(choix==1)
            {
                fflush(stdin);
                printf("Entrer les information de l'etudiant!\nMatricule : ");
                fgets(Matri, 10, stdin);
                printf("Sequence : ");
                scanf("%d", &Seq);
                Moy = MoyEtud(Matri, Seq);
                if(Moy.Valeur>=0)
                    printf("Sequence %d\nMoyenne : %f\n", Seq, Moy.Valeur);
                else printf("Sequence %d\nMoyene : Indisponible\n", Seq);

            }
            else
            {
                while(fread(&Etud, sizeof(Etud), 1, f)!=0)
                {
                    for(int i=0; i<N; i++)
                    {
                        Moy=MoyEtud(Etud.Mat, i+1);
                        if(Moy.Valeur>0)
                            printf("Etudiant %sSequence %d\tMoyenne : %f (Nombre de matiere %d)\n", Etud.Nom,i+1, Moy.Valeur, Moy.Nombres);
                        else printf("Sequence %d\tMoyenne : Indisponible\n", i+1);
                    }
                }
            }

            fclose(g);
            fclose(f);
        }
    }
}
//Fonction qui supprime les notes
void Suprime(char MatEtud[], char CodeMat[], int Seq)
{
    FILE *f=fopen("fnote.ing", "r"), *g=fopen("zozo.ing", "w+");
    NOTE Note;


    if(f==NULL)
        printf("PROBLEME D'OUVERTURE DE \"fnote.ing\"!!!\n");
    else
    {
        while(!feof(f))
        {
            fread(&Note, sizeof(Note), 1, f);
            if(strcmp(Note.matEtud, MatEtud)!=0 || strcmp(Note.matcode, CodeMat)!=0 || Note.seq!=Seq)
            {
                fwrite(&Note, sizeof(Note), 1, g);
            }
        }
    }
    fclose(f);
    f=fopen("fnote.ing", "w");
    rewind(g);
    while(!feof(g) && fread(&Note, sizeof(Note), 1, g)!=0)
    {
        fwrite(&Note, sizeof(Note), 1, f);
    }

    fclose(f);
    fclose(g);
}
//Choix 9
void Suprim_Note()
{
    FILE *f=fopen("fnote.ing", "r");
    char MatEtud[10];
    char CodeMat[5];
    int Seq;
    float note;
    int t=0;
    float choix;
    if(Vide("fetude.ing")==1)
        printf("Il y'a aucune note enregistre\n");
    else
    {
        do
        {
            if(t==1)
            {
                printf("Cette note n'existe pas!!\nRessaiyer? <OUI>1\<NON>-1 : ");
                scanf("%d", &choix);
                if(choix==-1) break;    //On sort de la boucle completement
            }
            fflush(stdin);
            printf("Entrer le matricule de l'etudiant : ");
            fgets(MatEtud, 10, stdin);
            printf("Entrer le code de la matiere : ");
            fgets(CodeMat, 5, stdin);
            printf("Entrer la sequence : ");
            scanf("%d", &Seq);
            note=TrouveNote(MatEtud, CodeMat, Seq);
            if(note<0) t=1;
            else t=0;
        }
        while(note<0);
        if(t==0)
        {
            printf("Note prcedente : %f\nEtes vous sur de vouloir effecee?\t<OUI>:1\t<NON>:-1 : ", note);
            scanf("%f", &choix);
            if(choix==1)
                Suprime(MatEtud, CodeMat, Seq);
        }
    }
}
//Fonction charge de la modification des notes
void Modif_Note()
{
    //L'idee est de suprimer la note precedente et d'ajouter la nouvelle.
    FILE *f=fopen("fnote.ing", "r+");
    char MatEtud[10];
    char CodeMat[5];
    int Seq;
    NOTE Note;
    float note;
    int t=0, t1=0, t2=0, choix;

    if(Vide("fetude.ing")==1)
        printf("Il y'a aucune note enregistre\n");
    else
    {
        fflush(stdin);
        do
        {
            if(t==1)
            {
                do
                {
                    if(t1==1) printf("Choix Invalid!!\n");
                    printf("Cet Etudiant n'exist pas!!\nVoulez vous continuez ?\t<OUI>:1 <NON>:-1\n_");
                    scanf("%d", &choix);
                    t1=1;
                }
                while(choix!=1 && choix!=-1);
            }
            printf("Entrer le matricule de l'etudiant : ");
            fgets(MatEtud, 10, stdin);
            t=1;
        }
        while(EtudExist(MatEtud)==0);
        t=0;
        t1=0;
        do
        {
            if(t==1)
            {
                do
                {
                    if(t1==1) printf("Choix Invalid!!\n");
                    printf("Cette matiere n'existe pas!!\nVoulez vous continuez ?\t<OUI>:1 <NON>:-1\n_");
                    scanf("%d", &choix);
                    t1=1;
                }
                while(choix!=1 && choix!=-1);
            }
            printf("Entrer le code de la matiere : ");
            fgets(CodeMat, 5, stdin);
        }
        while(MatExist(CodeMat)==0);
        do
        {
            if(t==1) printf("Il y'a que %d sequence(s)\n", N);
            printf("Entrer la sequence : ");
            scanf("%d", &Seq);
            t=1;
        }
        while(Seq>N || Seq<=0);
        note=TrouveNote(MatEtud, CodeMat, Seq);

        if(note>=0) //i.e si la note existe
        {
            printf("Note prcedente : %f\n", note);
            do
            {
                printf("Nouvelle Note : ");
                scanf("%f", &note);
            }
            while(note<0 || note>20);
            //Suprime(MatEtud, CodeMat, Seq);
            Note.seq = Seq;
            //printf("Hello World\n");
            fseek(f, 0, SEEK_SET);      //Onplace le curseur au debut du fichier
            while(!feof(f) && fread(&Note, sizeof(Note), 1, f)!=0)
            {

                // printf("Hello 345\n");
                if(strcmp(Note.matEtud, MatEtud)==0 && strcmp(Note.matcode, CodeMat)==0)
                {
                    printf("Recherche de la note...\n");
                    Note.note=note;
                    //fseek(f, -sizeof(Note), SEEK_CUR);
                    Suprime(MatEtud, CodeMat, Seq);

                    printf("Note trouvé.\n");
                    break;
                }
            }
            fwrite(&Note, sizeof(Note), 1, f);
            printf("Note enregistre. \n");
        }
        else
        {
            printf("Cette note n'existe pas!!\n");
        }
    }
    fclose(f);
}
//Cherche un etudiant a partie du matricule
ETUDIANT SearchEtud(char Matri[])
{
    FILE *f=fopen("fetude.ing", "r");
    ETUDIANT Etud;

    if(f==NULL)
        printf("PROBLEME D'OUVERTURE DE \"fetude.ing\" A \"SearchEtud\".\n ");
    else
    {
        while(fread(&Etud, sizeof(Etud), 1, f)!=0)
        {
            if(strcmp(Etud.Mat, Matri)==0)
                break;
        }

    }
    return Etud;
}
//Affiche le PV
void AffichePVEtud(char Matri[])
{
    FILE *f=fopen("fmate.ing", "r");
    ETUDIANT Etud;
    MATIERE Mat;
    Moyen Moy;
    float note, Som=0, MoyenG;

    Etud = SearchEtud(Matri);
    printf("Nom : %sMatricule : %sSexe : %c\nDate de Naissance : %d/%d/%d\nFilliere : %s", Etud.Nom, Etud.Mat, Etud.Sexe, Etud.DateNais.jour, Etud.DateNais.Mois, Etud.DateNais.Annee, Etud.Filiere);
    printf("------------------Notes--------------------\n");

    while(fread(&Mat, sizeof(Mat), 1, f)!=0)
    {
        printf("%s", Mat.Nom);
        printf("\tSequence 1\tSequence 2\tSquence 3\tCredits\n");
        for(int i=0; i<N; i++)
        {
            note = TrouveNote(Matri, Mat.Code, i+1);
            if(note>=0)
            {
                printf("\t%0.2f\t", note);
            }
            else printf("\t//\t");
        }
        printf("\t%d\n", Mat.Credits);
    }
    printf("Moyen\t");
    rewind(f);
    while(fread(&Mat, sizeof(Mat), 1, f)!=0)
    {
        for(int i=0; i<N; i++)
        {
            Moy=MoyEtud(Matri, i+1);
            if(Moy.Nombres>0)
            {
                printf("%0.2f\t\t", Moy.Valeur);
                Som = Som + Moy.Valeur;
            }
            else printf("// \t\t");
        }
        printf("\n");
    }
    MoyenG=Som /N;

    printf("Moyen Generale : %f\n", MoyenG);
    system("pause");

}

void PV()
{
    char Matricule[20];
    fflush(stdin);
    printf("Entrer le matricule de l'etudiant : ");
    fgets(Matricule, 20, stdin);

    AffichePVEtud(Matricule);
}
