#include "cmsg.h"
#include "commun.h"

CMsg::CMsg(QObject *parent) :
    QObject(parent)
{
    // calculer la clef d'accès à la file de messages
    key = ftok(FICHIER, LETTRE);
    id = msgget(key, IPC_CREAT);

} // method

CMsg::~CMsg()
{
} // method

int CMsg::ajouterMsg(QString &trame)
{
    T_MSG tag;
    tag.trame = trame; // trame brute
    tag.sens = trame.mid(1,2).toInt(0,16);
    tag.noLect = trame.mid(9,2).toInt(0,16);
    tag.mouv = trame.mid(6,3).toInt(0,16);
    tag.type = tag.noLect;
    return msgsnd(id, &tag, sizeof(T_MSG), IPC_NOWAIT);
} // method

int CMsg::lireMsg(int type, T_MSG *mess) // 0 pour n'importe quel type
{
    return msgrcv(id, &mess, sizeof(T_MSG), type, IPC_NOWAIT);
} // method
