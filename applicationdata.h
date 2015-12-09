#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H


#include <QObject>
#include <QString>
#include <QTime>
#include <QDebug>
#include <QVector>


class ApplicationData
{
QString _name, _url;
QTime _startTime, _endTime;
long _totalTime;

static long _totalTimeAll;



public:
    ApplicationData(QString name = "", QString url = ""):
                    _name(name), _url(url), _startTime(0,0), _endTime(0,0), _totalTime(0){}

    //Setter
    void setName(QString name);
    void setUrl(QString url);
    void setStartTime(QTime start);
    void setEndTime(QTime end);
    void setTotalTime(long totalTime);

    //Getter
    QString getName();
    QString getUrl();
    QTime getStartTime();
    QTime getEndTime();
    long getTotalTime();
    static long getTotalTimeAll();

    //Methodes
    void calcTimes();

signals:

public slots:

};

#endif // APPLICATIONDATA_H
