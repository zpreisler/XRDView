#ifndef DATABASEXRD_H
#define DATABASEXRD_H
#include "phaselist.h"
#include "phase.h"
#include <QString>
#include <QDir>
#include <QList>




class DatabaseXRD : QMultiHash<QString,Phase>
{

public:
    DatabaseXRD();
    void  read_cifs(QDir path);
    QList<Phase> random();



};

#endif // DATABASEXRD_H
