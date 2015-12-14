#include "visualize.h"


long Application::_totalTimeAll(0);

Visualize::Visualize()
{

}

QVector<ChartData> &Visualize::getChartDataVector()
{
    return _chartDataObjects;
}

QVector<Application> &Visualize::getAppclicationsVector()
{
    return _applications;
}

void Visualize::handleDataFromString(QString filepath)
{
    QString line;
    QFile file(filepath);
    QJsonDocument d;
    QJsonObject o;

    ChartData tempChart;
    ApplicationData tempApp;

    QString tempName, tempUrl, tempTimeString;
    bool tempOnWhitelist;
    QTime tempTime;

    int tempHour, hourDifference;

    _lastChangeChart = -1, _lastChangeApp = -1, _chartRef = -1, _appRef = -1, _calcHour = 0;

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!file.exists()){
        qDebug() << "Error read File!";
    }

    while(!file.atEnd()){
        line = file.readLine();
        d = QJsonDocument::fromJson(line.toUtf8());
        o = d.object();

        tempName = o.value(QString("process")).toString();
        tempUrl = o.value(QString("url")).toString();
        tempTimeString = o.value(QString("time")).toString();

        if(o.value(QString("whitelisted")).toString() == "true"){
            tempOnWhitelist = true;
        } else {
            tempOnWhitelist = false;
        }

        tempTime = QTime::fromString(tempTimeString, "hh:mm:ss");
        tempHour = tempTime.hour();

        //existing object is searched in vector
        findPosition(tempName, tempOnWhitelist, tempHour, _chartRef, _appRef, tempUrl);

        //if an old object exist
        if(_lastChangeApp != -1){
            int pos = findApplication(_chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].getName());
            //if application not in application vector
            if (pos == -1) {
                Application temp(_chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].getName());
                _applications.append(temp);
                pos = _applications.count() - 1;
            }
            //add time to application vector
            _applications[pos].addTotalTime(_chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].getStartTime().secsTo(tempTime));

            if(_chartDataObjects[_lastChangeChart].getHour() == tempHour){
                _chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].setEndTime(tempTime);
            } else {
                hourDifference = tempHour - _chartDataObjects[_lastChangeChart].getHour();
                QTime endTime(_chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].getStartTime().hour() + 1, 0, 0);
                _chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].setEndTime(endTime);
                for(int i = 1; i <= hourDifference; i++){
                    _calcHour = tempHour - hourDifference + i;
                    calcOverflow(_chartDataObjects[_lastChangeChart].getList(_lastChange));
                    QTime test(_calcHour, 59, 59);
                    if (tempTime < test) {
                        _chartDataObjects[_chartRef].getList(_lastChange)[_lastChangeApp].setEndTime(tempTime);
                    } else {
                        test = test.addSecs(1);
                        _chartDataObjects[_chartRef].getList(_lastChange)[_lastChangeApp].setEndTime(test);
                    }
                }
            }
            _lastChangeChart = _chartRef;
            _lastChangeApp = tempChart.getList(_lastChange).size()-1;
        }

        //if instance with actual hour not exist
        if(_chartRef == -1){
            tempChart.setHour(tempHour);
            _chartDataObjects.append(tempChart);
            _chartRef = _chartDataObjects.size()-1;
            _lastChangeChart = _chartRef;
        }

        if(tempName == "stopped"){
            _lastChangeApp = -1;
            _lastChangeChart = -1;

        } else if(_appRef != -1){
            _chartDataObjects[_chartRef].getList(tempOnWhitelist)[_appRef].setStartTime(tempTime);
            _lastChangeApp = _appRef;

        } else {
            tempApp.setName(tempName);
            tempApp.setStartTime(tempTime);
            tempApp.setUrl(tempUrl);
            _chartDataObjects[_chartRef].getList(tempOnWhitelist).append(tempApp);
            _lastChangeApp = _chartDataObjects[_chartRef].getList(tempOnWhitelist).size()-1;
            if(tempOnWhitelist){
                _lastChange = true;
            } else {
                _lastChange = false;
            }

        }
    }
    file.close();
}

void Visualize::findPosition(QString name, bool onWhitelist, int hour, int &chartRef, int &appRef, QString url)
{
    chartRef = -1;
    appRef = -1;

    for(int i = 0; i < _chartDataObjects.size(); i++){
        if(hour == _chartDataObjects[i].getHour()){
            chartRef = i;
            for(int j = 0; j < _chartDataObjects[i].getList(onWhitelist).size(); j++){
                if(name  == _chartDataObjects[i].getList(onWhitelist)[j].getName() && url == _chartDataObjects[i].getList(onWhitelist)[j].getUrl()){
                    appRef = j;
                }
            }
        }
    }
}

void Visualize::calcOverflow(QVector<ApplicationData> &data)
{
    ChartData tempChart;
    ApplicationData tempApp;
    QTime fullHour;


    fullHour.setHMS(_calcHour, 0, 0);

    //data[_lastChangeApp].setEndTime(fullHour);

    tempApp.setName(data[_lastChangeApp].getName());
    tempApp.setUrl(data[_lastChangeApp].getUrl());
    tempApp.setStartTime(fullHour);

    tempChart.setHour(_calcHour);

    tempChart.getList(_lastChange).append(tempApp);

    _chartDataObjects.append(tempChart);
    _chartRef = _chartDataObjects.size()-1;
    _lastChangeApp = 0;

}

int Visualize::findApplication(QString app)
{
    for (int i=0; i < _applications.count(); i++) {
        if (app == _applications[i].getName())
            return i;
    }
    return -1;
}


