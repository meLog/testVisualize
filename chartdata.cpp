#include "chartdata.h"

ChartData::ChartData()
{

}

void ChartData::setHour(int hour)
{
    _hour = hour;
}


int ChartData::getHour()
{
    return _hour;
}

QVector<ApplicationData> &ChartData::getWhitelist()
{
    return _whitelist;
}

QVector<ApplicationData> &ChartData::getBlacklist()
{
    return _blacklist;
}

QVector<ApplicationData> &ChartData::getList(bool whitelist)
{
    if (whitelist) {
        return _whitelist;
    } else {
        return _blacklist;
    }
}


