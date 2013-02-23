#ifndef CBDD_H
#define CBDD_H

#include <QObject>
#include <QString>
#include <QComboBox>
#include <QtSql>
#include "commun.h"

class CBdd : public QObject
{
    Q_OBJECT
public:
    explicit CBdd(QObject *parent = 0);
    ~CBdd();

    bool identifier(const QString &login, const QString &pass);
    bool getConfig(T_Config *c);
    bool setConfig(T_Config *c);

    // table pertes de réception des badges
    int perteDuBadge(int noB, int noL);
    int receptionRetrouvee(int noB);
    int lirePertes(int noL);
    int effacerPertes();

    // table personnnes
    int ListeDesPersonnes();
    int identitePersonne(int no);
    bool majPersonne(T_Pers *pers);
    bool effPersonne(T_Pers *pers);
    bool addPersonne(T_Pers *pers);
    int getNoPersSuivant();

    // table lecteurs
    int ListeDesLecteurs();
    int initLecteurs();
    bool LecteurHorsService(int no);
    bool LecteurEnService(int no);
    int getAdrIpLecteur(int no);
    int isLecteurExiste(int no);
    int getNoLecteur(QString adr);
    bool getPointsZone(int vue, int no, T_Point *pointA, T_Point *pointB);
    bool majLecteur(T_Lect *lect);
    bool effLecteur(T_Lect *lect);
    bool addLecteur(T_Lect *lect);
    int getNoLectSuivant();
    bool infoDeCeLecteur(QString &nol);

    // table useBadges
    int listerBadgesAffected();

    // table badges
    int ListeDesBadges();
    int identiteBadge(int no);
    bool majBadge(T_Bdg *bdg);
    bool effBadge(T_Bdg *bdg);
    bool addBadge(T_Bdg *bdg);
    int getNoBadgeSuivant();
    bool isBadgeExiste(QString &noB);

    // table badgeEnCours
    int creerBadgeEnCours();  // -1 si impossible existe deja
    bool isBadgeEnCours(QString &nob);
    bool modifBadgeEnCours(QString &nob, int x, int y);

    // mix
    int aQuiAppartientCeBadge(QString &nob);
    int aQuiSontLesBadges();

    QSqlQuery *query;

signals:

public slots:

private:
   QSqlDatabase db;
   QString req;  // requete
};

#endif // CBDD_H
