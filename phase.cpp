#include "phase.h"
#include <cmath>

Phase::Phase()
{

}

Phase::Phase(QStringList keys, QVariantList values)
{

    for(int i=0;i<keys.length();i++){
        insert(keys.at(i),values.at(i));
    }
}
Phase::Phase(QString filename)
{

    insert("filename",filename);

}

quint64 Phase::len()
{
     QVariant val=value("_pd_peak_intensity");
     return(val.toUInt());
}

void Phase::insert_val(QString k, QVariant val)
{
    insert(k,val);

}

bool Phase::compare(QList<QVariant> a,QList<QVariant> b){
    /*
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    */
    return(a==b);

}

QList<QVariant> Phase::convert(QList<qreal> list){


    QList<QVariant> v;
    for(qreal q:list){
        v.append(QVariant(q));
    }

    return v;
}

QList<qreal> Phase::convert(QList<QVariant> list){

    QList<qreal> r;
    for(QVariant v:list) r.append(v.toReal());
    return r;
}

void  Phase::replace_list(QString key,QList<QVariant> list){
    remove(key);
    for(QVariant v:list)  insert(key,v);

}



Phase::theta_struct Phase::get_theta(QList<qreal> *l, QList<qreal> *scale, QList<qreal> *min_theta , QList<qreal> *max_theta, QList<qreal> *min_intensity , QList<qreal> *first_n_peaks)
{
    Phase::theta_struct ret;

    if(contains("l_last" )and contains("scale_last") and contains("min_theta_last")and contains("max_theta_last") and contains("min_intensity_last")and contains("first_n_peaks_last")and contains("intensity") and contains("theta"))
    {
            if(compare(convert(*l),values("l_last"))and compare(convert(*scale),values("scale_last"))and compare(convert(*min_theta),values("min_theta_last"))and compare(convert(*max_theta),values("max_theta_last"))and compare(convert(*min_intensity),values("min_intensity_last")))
            {

              ret.theta=(convert(values("theta")));
              ret.intensity=(convert(values("intensity")));

            }
    }else{

            replace_list("l_last",convert(*l));
            replace_list("scale_last",convert(*scale));
            replace_list("min_theta_last",convert(*min_theta));
            replace_list("max_theta_last",convert(*max_theta));
            replace_list("min_intensity_last",convert(*min_intensity));
            replace_list("first_n_peaks_last",convert(*first_n_peaks));

            QList<qreal> theta;
            QList<qreal> intensity;

            int k1=std::min(l->length(),scale->length());
            QList<qreal> pd_peak=convert(values("_pd_peak_intensity"));
            qreal d=pd_peak.at(0);
            qreal i=pd_peak.at(1);

            for (int k=0;k<k1;k++){
                qreal v=l->at(k);
                qreal g=v/(2.0 * d);
                theta.append(360.0*std::asin(g)/M_PI);
                intensity.append(i*scale->at(k)/1000);
            }
            bool mask[theta.length()];
            for(int i=0;i<theta.length();i++) mask[i]=true;
            if(min_theta)
               for(int i=0;i<theta.length();i++) mask[i]=mask[i] and( theta.at(i) > min_theta->at(i));
            if(max_theta)
               for(int i=0;i<theta.length();i++) mask[i]=mask[i] and (theta.at(i) < max_theta->at(i));
            if(min_intensity)
               for(int i=0;i<theta.length();i++) mask[i]=mask[i] and (theta.at(i) > min_intensity->at(i));

            //da completare
            if(theta.length()>0){
                if(values("first_n_peaks_list").length()>0){
                    //?????? self.intensity, self.theta = array(sorted(zip(self.intensity, self.theta), reverse = True)).T[:, 0:first_n_peaks]
                    QList t=theta;
                    std::sort(t.first(),t.last(),std::greater <>());
                    QList i=intensity;
                    std::sort(i.first(),i.last(),std::greater <>());
                    int min=std::min(t.length(),i.length())-1;
                    t=t.mid(0,min);
                    i=i.mid(0,min);
                    ret.theta=t;
                    ret.intensity=i;

                }
            }









    }

    return(ret);
}
void Phase::set_name(QString name){
    remove("name");
    insert("name",QVariant(name));
}
void Phase::set_point(qreal point){
    remove("poit");
    insert("point",QVariant(point));
}
QString Phase::label(){
    /*
     * if '_chemical_name_mineral' in self:
            return self['_chemical_name_mineral']
        elif '_chemical_name_common' in self:
            return self['_chemical_name_common']
        elif '_chemical_formula_sum' in self:
            return self['_chemical_formula_sum']
        else:
            return None*/
    if(contains("_chemical_name_mineral")) return value("_chemical_name_mineral").toString();
    else if(contains("_chemical_name_common")) return value("_chemical_name_common").toString();
    else if(contains("_chemical_formula_sum")) return value("_chemical_formula_sum").toString();
    else return(NULL);

}
