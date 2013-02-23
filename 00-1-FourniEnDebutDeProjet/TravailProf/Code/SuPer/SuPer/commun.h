#ifndef COMMUN_H
#define COMMUN_H

#include <QLabel>
#include <QString>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "cthreadclient.h"

// masque de l'octet d'état
#define MOUV 1
#define REC  2
#define AR 4
#define MOUV0 8  //mouv=0 avant alarme

// a enlever dans le futur
#define MAX_VAL 5   // pour faire la moyenne
#define MAX_LECT 5   // nbre max de lecteur

// configuration de SuPER
typedef struct {
    int tempoM,// ms tempo pour le timer mouvement
    tempoR,// ms tempo pour le timer de réception
    tempoA,// affichage général IHM
    maxVal,// Nbre de valeur pour faire la moyenne de sensibilité
    maxLect;// 5 max lecteur utilisé
} T_Config;

// message pour la file de messages (IPC Système V)
#define FICHIER "commun.h"
#define LETTRE 'S'
typedef struct msg {
    long type; // =no du lecteur
    pid_t pid; // du thread
    pthread_t noThread; // du thread
    int sens;
    int noBadge;
    int mouv;
    int noLect;
    QString trame; // trame brute
} T_MSG;

// structure pour le positionnement X, Y du label badge
typedef struct {
    int x,y;
} T_Point;

// correspondance entre le le label vert/rouge et le thread créé
typedef struct s_thread {
    CThreadClient *thcl;
    int noLect;
} T_Thread;

//
typedef struct s_personne {
    QString nom, pnom;
    QString societe;
    QString dateDeb, dateFin;
    QString email;
    int noPers; // no unique de la personne
    QString ident;
    QString pass;
    QString exploit;
} T_Pers;


// Permet le mise en correspondance d'un QLabel de position avec un badge.
// création dynamique des logo affiché représentant les personnes badgées.
typedef struct s_listeLabel {
    QLabel *l;     // référence du label d'affichage
    QTimer *wdm;   // timer de watchdog de mouvement
    QTimer *wdr[MAX_LECT];   // timer de watchdog de réception
    T_Pers pers;
    T_Point ptA, ptB, ptF;
    int noBadge;
    int noLect;  // dernier nO de lecteur lu
    int etat;  // bit0:Mouv(0:RAS, 1:TO)   bit1:REC(0:RAS, 1:TO)  bit2:SENS(0:haut, 1:bas) bit3:MOUV0
    int zone;   // lieu géographique d'affichage du badge
    int moySens[MAX_LECT][MAX_VAL];
    int indMoy[MAX_LECT];
    int sdp[MAX_LECT];
    int memSdp[MAX_LECT];
} T_ListeLabel;

typedef struct s_badge {
    QString dateMES;
    QString ref;
    QString noBadge;
    QString carac;
    QString enCours;
    int noBdg;
} T_Bdg;

typedef struct s_lecteur {
    QString mode;
    QString ref;
    QString desc;
    QString type;
    QString params;
    QString code;
    int noLect; // no unique de la personne
} T_Lect;

typedef struct s_camera {

} T_Cam;

#endif // COMMUN_H
