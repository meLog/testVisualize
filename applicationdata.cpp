#include "applicationdata.h"


//Setter-------------------------------------------------------------------------
void ApplicationData::setName(QString name)
{
    _name = name;
}

void ApplicationData::setUrl(QString url)
{
    _url = url;
}

void ApplicationData::setStartTime(QTime start)
{
    _startTime = start;
}

void ApplicationData::setEndTime(QTime end)
{
    _endTime = end;
    calcTimes();
}


void ApplicationData::setTotalTime(long totalTime)
{
    _totalTime = totalTime;
}


//Getter--------------------------------------------------------------------------
QString ApplicationData::getName()
{
    return _name;
}

QString ApplicationData::getUrl()
{
    return _url;
}

QTime ApplicationData::getStartTime()
{
    return _startTime;
}

QTime ApplicationData::getEndTime()
{
    return _endTime;
}


long ApplicationData::getTotalTime()
{
    return _totalTime;
}

long ApplicationData::getTotalTimeAll()
{
    return _totalTimeAll;
}




//Methoden--------------------------------------------------------------------------
void ApplicationData::calcTimes()
{
    long tempTime;

    tempTime = _startTime.secsTo(_endTime);

    qDebug() << tempTime;

    _totalTime += tempTime;
    _totalTimeAll += tempTime;

}




