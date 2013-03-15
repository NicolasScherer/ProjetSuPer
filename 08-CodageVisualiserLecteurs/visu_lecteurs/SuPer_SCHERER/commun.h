#ifndef COMMUN_H
#define COMMUN_H

#include <QLabel>
#include <QVBoxLayout>

//structure liste label lecteur
typedef struct s_labelLecteur{
    QLabel *label;
    int num_lecteur;
} T_labelLecteur;

//structure liste onglet
typedef struct s_Onglet{
    QWidget *onglet;
    QVBoxLayout *layout;
    int num_vue;
} T_Onglet;

#endif // COMMUN_H
