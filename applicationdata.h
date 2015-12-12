#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include "application.h"


class ApplicationData : public Application
{
    QTime _startTime;
    QTime _endTime;

public:
    explicit ApplicationData(QString name = "", QString url = "");

    //Setter
    void setStartTime(QTime start);
    void setEndTime(QTime end);

    //Getter
    QTime getStartTime();
    QTime getEndTime();

    //Methodes
    void calcTimes();
    bool operator<(const ApplicationData &a);

signals:

public slots:

};

#endif // APPLICATIONDATA_H
