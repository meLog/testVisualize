#include "applicationdata.h"


ApplicationData::ApplicationData(QString name, QString url) : Application::Application(name, url), _startTime(0,0,0), _endTime(0,0,0) {}

//Setter-------------------------------------------------------------------------
void ApplicationData::setStartTime(QTime start)
{
    _startTime = start;
}

void ApplicationData::setEndTime(QTime end)
{
    _endTime = end;
    calcTimes();
}


//Getter--------------------------------------------------------------------------
QTime ApplicationData::getStartTime()
{
    return _startTime;
}

QTime ApplicationData::getEndTime()
{
    return _endTime;
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

bool ApplicationData::operator<(const ApplicationData &a)
{
    return a._totalTime < this->_totalTime;
}




