#ifndef H_NOTE_H
struct NOTE
{
    char matcode[5];
    char matEtud[10];
    int seq;
    float note;
};
typedef struct NOTE NOTE;

struct Moyen
{
    float Valeur;
    int Nombres;    //Nombre de matiere
};
typedef struct Moyen Moyen;

/*-----------PROTOTYPES-----------*/
NOTE SaisieNote();
void Saisie_Note();
float TrouveNote(char MatEtud[], char CodeMat[], int Seq);
void AfficheNotesEtuds();
void AfficheNote();
void Affiche_Moyennes();

#endif // H_NOTE_H
