#ifndef PHASE_H
#define PHASE_H

#include <QString>
#include <QVariant>

class Phase : QMultiHash<QString,QVariant>
{


public:
    struct theta_struct{
        QList<qreal> theta;
        QList<qreal> intensity;
    };

    Phase();
    Phase(QString filename);
    Phase(QStringList keys, QVariantList values);
    quint64 len();
    theta_struct  get_theta(QList<qreal> *l=new QList<qreal>{1.541874}, QList<qreal> *scale=new QList<qreal>{1.0}, QList<qreal> *min_theta=nullptr , QList<qreal> *max_theta=nullptr, QList<qreal> *min_intensity=nullptr , QList<qreal> *first_n_peaks=nullptr);

    bool compare(QList<QVariant> a,QList<QVariant> b);
    QList<QVariant> convert(QList<qreal> list);
    QList<qreal> convert(QList<QVariant> list);
    void set_name(QString name);
    void set_point(qreal point);
    QString label();
    void insert_val(QString k,QVariant val);

private:
    void  replace_list(QString key,QList<QVariant> list);
    bool  comparator(qreal a, qreal b);
    QList<qreal> sort(QList<qreal> list);
    QList<qreal> sort_desc(QList<qreal> list);
};

#endif // PHASE_H
