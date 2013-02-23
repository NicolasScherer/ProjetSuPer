#include <QMessageBox>
#include <QComboBox>

#include "cbdd.h"

CBdd::CBdd(QObject *parent) :
    QObject(parent)
{
    QString req;

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("lsbb");
    db.setUserName("lsbb");
    db.setPassword("lsbb");
    if (!db.open())
        QMessageBox::critical(0, tr("Impossible d'ouvrir le Bdd."),
                     tr("Impossible d'établir une connexion avec la Bdd.\n"),
                              QMessageBox::Cancel);
    query = new QSqlQuery();
} // methode

/////////////////////////////////////////////////////////
CBdd::~CBdd()
{
    delete query;
    db.close();
} // method

/////////////////////////////////////////////////////////////
//    CONFIG
////////////////////////////////////////////////////////////
bool CBdd::getConfig(T_Config *c)
{
    req = "SELECT * FROM config LIMIT 1";
    query->prepare(req);
    if (!query->exec()) return false;
    query->next();
    c->maxLect = query->value(0).toInt();
    c->maxVal = query->value(1).toInt();
    c->tempoM = query->value(2).toInt();
    c->tempoR = query->value(3).toInt();
    c->tempoA = query->value(4).toInt();
    return true;
} // method

////////////////////////////////////////////////////////////
bool CBdd::setConfig(T_Config *c)
{
    req = "UPDATE config ";
    req += "SET maxLect=:ml, maxVal=:mv, tempoM=:tm, tempoR=:tr, tempoA=:ta ";
//    req += "LIMIT 1";
    query->prepare(req);
    query->bindValue(":ml", c->maxLect);
    query->bindValue(":mv",c->maxVal);
    query->bindValue(":tm", c->tempoM);
    query->bindValue(":tr", c->tempoR);
    query->bindValue(":ta", c->tempoA);
    return query->exec();
} // method

//////////////////////////////////////////////
//          useBadges                        //
//////////////////////////////////////////////
//////////////////////////////////////////////
int CBdd::listerBadgesAffected()
{
 return 1;
} // method


//////////////////////////////////////////////
//          badgeEnCours                    //
//////////////////////////////////////////////
//////////////////////////////////////////////
int CBdd::creerBadgeEnCours()
{
 return 1;
} // method

////////////////////////////////////////////
bool CBdd::isBadgeEnCours(QString &nob)
{
    return true;
} // method

bool modifBadgeEnCours(QString &nob, int x, int y)
{
    return true;
} // method

/////////////////////////////////////////////////
//                     Mix                     //
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int CBdd::aQuiSontLesBadges()
{
    req = "SELECT badges.noBadge, personnes.nom, personnes.pnom ";
    req += "FROM badges ";
    req += "LEFT JOIN useBadges ON badges.noBadge= useBadges.noBadge ";
    req += "LEFT JOIN personnes ON useBadges.noPers = personnes.noPers ";
    req += "ORDER BY badges.noBadge DESC ";
    query->prepare(req);
    if (!query->exec()) return -1;
    if (query->size() > 0) {
      query->next();
      return query->size();
    } else {
        return -1;
    } // else
} // method

int CBdd::aQuiAppartientCeBadge(QString &nob) {
    req = "SELECT personnes.* FROM useBadges, personnes ";
    req += "WHERE useBadges.noBadge=:nob ";
    req += "AND personnes.noPers = useBadges.noPers ";
    req += "ORDER BY noEnr DESC LIMIT 1";
    query->prepare(req);
    query->bindValue(":nob", nob);
    if (!query->exec()) return -1;
    if (query->size() == 1) {
      query->next();
      return query->value(0).toInt();
    } else {
        return -1;
    } // else
} // method


/////////////////////////////////////////////////
//            PERSONNES                        //
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int CBdd::getNoPersSuivant() {
    req = "SELECT noPers FROM personnes ";
    req += "ORDER BY noPers DESC LIMIT 1";
    query->prepare(req);
    if (!query->exec()) return -1;
    query->next();
    return query->value(0).toInt()+1;
} // method

/////////////////////////////////////////////////////////
bool CBdd::addPersonne(T_Pers *pers) {
    req = "INSERT INTO personnes ";
    req += "VALUES ('', :nom, :pnom, :societe, :dateDeb, :dateFin, :noPers, :email, :ident, :pass, :exploit) ";
    query->prepare(req);
    query->bindValue(":nom", pers->nom);
    query->bindValue(":pnom", pers->pnom);
    query->bindValue(":societe", pers->societe);
    query->bindValue(":dateDeb", pers->dateDeb);
    query->bindValue(":dateFin", pers->dateFin);
    query->bindValue(":email", pers->email);
    query->bindValue(":noPers", pers->noPers);
    query->bindValue(":ident", pers->ident);
    query->bindValue(":pass", pers->pass);
    query->bindValue(":exploit", pers->exploit);
    return query->exec();

} // method

/////////////////////////////////////////////////////////
bool CBdd::effPersonne(T_Pers *pers) {
    req = "DELETE FROM personnes ";
    req += "WHERE noPers=:noPers LIMIT 1";
    query->prepare(req);
    query->bindValue(":noPers", pers->noPers);
    return query->exec();
} // method

/////////////////////////////////////////////////////////
bool CBdd::majPersonne(T_Pers *pers) {
    req = "UPDATE personnes ";
    req += "SET nom=:nom, pnom=:pnom, societe=:societe, dateDeb=:dateDeb, dateFin=:dateFin, email=:email, ";
    req += "ident=:ident, pass=:pass, exploit=:exploit ";
    req += "WHERE noPers=:noPers LIMIT 1";
    query->prepare(req);
    query->bindValue(":nom", pers->nom);
    query->bindValue(":pnom", pers->pnom);
    query->bindValue(":societe", pers->societe);
    query->bindValue(":dateDeb", pers->dateDeb);
    query->bindValue(":dateFin", pers->dateFin);
    query->bindValue(":email", pers->email);
    query->bindValue(":ident", pers->ident);
    query->bindValue(":pass", pers->pass);
    query->bindValue(":exploit", pers->exploit);
    query->bindValue(":noPers", pers->noPers);
    return query->exec();

} // method

/////////////////////////////////////////////////////////
int CBdd::identitePersonne(int no)
{
    req = "SELECT * FROM personnes WHERE noPers=:no LIMIT 1";
    query->prepare(req);
    query->bindValue(":no", no);
    query->exec();
    query->next();
    return query->size();
} // method

////////////////////////////////////////////////////////
int CBdd::ListeDesPersonnes()
{
    int nb;
    req = "SELECT * FROM personnes";
    query->prepare(req);
    query->exec();
    nb = query->size();
    return nb;
} // method

////////////////////////////////////////////////////////
bool CBdd::identifier(const QString &login, const QString &pass)
{
    req = "SELECT noPers FROM personnes WHERE ident=:login AND pass=:pass AND exploit='Y' LIMIT 1";
    query->prepare(req);
    query->bindValue(":login", login);
    query->bindValue(":pass", pass);
    if (!query->exec())
    {
        qDebug("Erreur MySQL");
        return false;
    } // if exec
    query->next();

    int no=query->size();
    if (no < 1) {
        qDebug("Mauvaise identification");
        return false;
    } else {
        return true;
    } // else
} // methode


//////////////////////////////////////////////
//            BADGES                        //
//////////////////////////////////////////////
//////////////////////////////////////////////
bool CBdd::isBadgeExiste(QString &noB)
{
    req = "SELECT * FROM badges WHERE noBadge=:noB LIMIT 1";
    query->prepare(req);
    query->bindValue(":noB", noB);
    if (!query->exec())
    {
        qDebug("Erreur MySQL");
        return false;
    } // if exec
    int no=query->size();
    if (no == 1) {
      query->next();
      return true;
    }
    return false;
} // method

//////////////////////////////////////////////////////////
int CBdd::ListeDesBadges()
{
    return true;
} // method

/////////////////////////////////////////////////////////
int CBdd::identiteBadge(int no)
{
    return true;
} // method

/////////////////////////////////////////////////////////
bool CBdd::majBadge(T_Bdg *bdg)
{
    return true;
} // method

/////////////////////////////////////////////////////////
bool CBdd::effBadge(T_Bdg *bdg)
{
    return true;
} // method

/////////////////////////////////////////////////////////
bool CBdd::addBadge(T_Bdg *bdg)
{
    return true;
} // method

/////////////////////////////////////////////////////////
int CBdd::getNoBadgeSuivant()
{
    return true;
} // method

//////////////////////////////////////////////
//                PERTES                    //
//////////////////////////////////////////////
//////////////////////////////////////////////
int CBdd::lirePertes(int noL)
{
    req = "SELECT * FROM pertes ";
    if (noL > 0)                     // selement les badges pour un lecteur
       req += "WHERE noLect=:noL ";
    query->prepare(req);
    if (noL > 0)
        query->bindValue(":noL", noL);
    if (!query->exec())
        return -1;
    int no=query->size();
    if (no > 0) {
      return no;
    } // if no
    return -1;
} // method

/////////////////////////////////////////////////////
int CBdd::effacerPertes()
{
    req = "DELETE FROM pertes ";
    query->prepare(req);
    if (!query->exec()) return -1;
    return query->numRowsAffected();
} // method

//////////////////////////////////////////////////
int CBdd::perteDuBadge(int noB, int noL)
{
    req = "SELECT noEnr FROM pertes ";
    req += "WHERE noBadge=:noB ";
    req += "AND noLect=:noL LIMIT 1";
    query->prepare(req);
    query->bindValue(":noB", noB);
    query->bindValue(":noL", noL);
    if (!query->exec())
        return -1;
    if (query->size() == 1) { // update
        req = "UPDATE pertes SET ";
        req += "noLect=:noL ";
        req += "WHERE noBadge=:noB LIMIT 1";
        query->prepare(req);
        query->bindValue(":noB", noB);
        query->bindValue(":noL", noL);
        if (!query->exec())
            return -1;
    } else {  // creation
        req = "INSERT INTO pertes ";
        req += "VALUES ('', :noB, :noL, '') ";
        query->prepare(req);
        query->bindValue(":noB", noB);
        query->bindValue(":noL", noL);
        if (!query->exec())
            return -1;
    } // else
    return 1;
} // method

///////////////////////////////////////////
int CBdd::receptionRetrouvee(int noB)
{
    req = "DELETE FROM pertes ";
    req += "WHERE noBadge=:noB LIMIT 1";
    query->prepare(req);
    query->bindValue(":noB", noB);
    if (!query->exec()) return -1;
    return query->numRowsAffected();
} // method

//////////////////////////////////////////////
//          COORDONNEES                     //
//////////////////////////////////////////////
//////////////////////////////////////////////
bool CBdd::infoDeCeLecteur(QString &nol) {
    req = "SELECT * FROM coordonnees ";
    req += "WHERE noLect=:nol LIMIT 1";
    query->prepare(req);
    query->bindValue(":nol", nol);
    if (!query->exec()) return false;
    if (!query->size()) return false;
    query->next();
    return true;
} // method

//////////////////////////////////////////////
bool CBdd::getPointsZone(int vue, int no, T_Point *pointA, T_Point *pointB)
{
    req = "SELECT * FROM coordonnees ";
    req += "WHERE noVue=:noV AND noZone=:noZ LIMIT 1 ";
    query->prepare(req);
    query->bindValue(":noV", vue);
    query->bindValue(":noZ", no);
    if (!query->exec()) return false;
    if (!query->size()) return false;
    query->next();
    pointA->x=query->value(2).toInt();
    pointA->y=query->value(3).toInt();
    pointB->x=query->value(4).toInt();
    pointB->y=query->value(5).toInt();
    return true;
} // method

//////////////////////////////////////////////
//          LECTEURS                        //
//////////////////////////////////////////////
//////////////////////////////////////////////

int CBdd::ListeDesLecteurs()
{
    return true;
} // method

//////////////////////////////////////////////
bool CBdd::LecteurEnService(int no)
{
    req = "UPDATE lecteurs SET ";
    req += "etat='E' ";
    req += "WHERE noCapteur=:no LIMIT 1 ";
    query->prepare(req);
    query->bindValue(":no", no);
    if (!query->exec()) return false;
    return query->numRowsAffected();
} // method

bool CBdd::LecteurHorsService(int no)
{
    req = "UPDATE lecteurs SET ";
    req += "etat='H' ";
    req += "WHERE noCapteur=:no LIMIT 1 ";
    query->prepare(req);
    query->bindValue(":no", no);
    if (!query->exec()) return false;
    return query->numRowsAffected();
} // method

//////////////////////////////////////////////
//  fixe tous les lecteurs à l'état inoccupé
int CBdd::initLecteurs()
{
    req = "UPDATE lecteurs SET ";
    req += "etat='I' ";
    query->prepare(req);
    if (!query->exec()) return -1;
    return query->numRowsAffected();
} // method

//////////////////////////////////////////////
int CBdd::getAdrIpLecteur(int no)
{
    req = "SELECT adresseIp FROM lecteurs ";
    req += "WHERE noCapteur=:no LIMIT 1 ";
    query->prepare(req);
    query->bindValue(":no", no);
    if (!query->exec()) return -1;
    if (!query->size()) return -1;
    query->next();
    return query->size();
} // method

int CBdd::isLecteurExiste(int no)
{
    req = "SELECT noEnr FROM lecteurs ";
    req += "WHERE noCapteur=:no AND etat='E' LIMIT 1 ";
    query->prepare(req);
    query->bindValue(":no", no);
    return query->exec();
}  // method

//////////////////////////////////////////////
int CBdd::getNoLecteur(QString adr)
{
    req = "SELECT noCapteur FROM lecteurs ";
    req += "WHERE adresseIp=:adr LIMIT 1 ";
    query->prepare(req);
    query->bindValue(":adr", adr);
    if (!query->exec()) return false;
    if (!query->size()) return false;
    query->next();
    return query->value(0).toInt();
} // method

//////////////////////////////////////////////
bool CBdd::majLecteur(T_Lect *lect)
{
    return true;
} // method

//////////////////////////////////////////////
bool CBdd::effLecteur(T_Lect *lect)
{
    return true;
} // method

//////////////////////////////////////////////
bool CBdd::addLecteur(T_Lect *lect)
{
    return true;
} // method

//////////////////////////////////////////////
int CBdd::getNoLectSuivant()
{
    return true;
} // method

