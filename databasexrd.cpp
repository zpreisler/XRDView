#include "databasexrd.h"

#include <QTextStream>
#include <QFile>
#include <QDir>

DatabaseXRD::DatabaseXRD()
{

}

void  DatabaseXRD::read_cifs(QDir path)
{

	QDir directory(path);
    QStringList files = directory.entryList(QStringList() << "*.cif",QDir::Files);

    foreach(QString filename, files) {
        qDebug()<<filename;

        QFile inputFile(path.filePath(filename));
        Phase phase(filename);

        if (inputFile.open(QIODevice::ReadOnly))
        {

            QTextStream in(&inputFile);
            while (!in.atEnd())
            {

               QString line = in.readLine();
               QStringList list1= line.split(' ');
               if(list1.length()>0){
                       QString y=list1.first();
                       QString st;

                       if(!y.compare("_chemical_formula_sum") or !y.compare("_chemical_name_mineral") or !y.compare("_chemical_name_common")){
                           for (int i = 1; i < list1.size(); i++) {
                               st=list1.at(i);

                               st.replace("'","");

                               if(st.length()>0)
                               {
                                    phase.insert_val(y,QVariant(st));
                               }

                           }

                       }else if(!y.compare("name")){

                                  st.replace("'","");
                                  phase.insert_val(y,QVariant(st));

                       }else if(!y.compare("point")){
                           qint64 val=list1.at(1).toInt();
                           phase.insert_val(y,QVariant(val));

                       }else if(!y.compare("_pd_peak_intensity")){
                           QList<qreal> vals;

                           for(int i=1;i<list1.length();i++){
                               qreal val=list1.at(i).toFloat();
                               vals.append(val);

                           }
                           phase.insert_val(y,QVariant::fromValue(vals));
                       }
                        QString key=phase.label();
                        this->insert(key,phase);
                         }

            }
            inputFile.close();
        }else{

        }

    }
}

QList<Phase> DatabaseXRD::random()
{
    QList<QString> list=uniqueKeys();
    quint64 len=list.length();
    quint64 v1 = rand() % len;
    QList<Phase> val;

	 val = values(list.at(v1));

    return(val);
}

