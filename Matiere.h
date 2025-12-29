#ifndef H_MATIERE_H
struct MATIERE
{
    char Code[5];
    char Nom[20];
    int Credits;
};
typedef struct MATIERE MATIERE;

MATIERE SaisieMat();
#endif // H_MATIERE_H
