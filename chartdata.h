#ifndef CHARTDATA_H
#define CHARTDATA_H

#include "applicationdata.h"


class ChartData
{
    int _hour;
    QVector<ApplicationData> _whitelist;
    QVector<ApplicationData> _blacklist;

public:
    ChartData();

    void setHour(int hour);
    int getHour();

    QVector<ApplicationData> &getWhitelist();
    QVector<ApplicationData> &getBlacklist();
    QVector<ApplicationData> &getList(bool whitelist);


signals:

public slots:
};

#endif // CHARTDATA_H
