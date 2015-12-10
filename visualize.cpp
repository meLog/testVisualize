#include "visualize.h"
#include "applicationdata.h"
#include "chartdata.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


long ApplicationData::_totalTimeAll(0);

Visualize::Visualize()
{

}

QVector<ChartData> &Visualize::getChartDataVector()
{
    return _chartDataObjects;
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
        //qDebug() << "Error read File!";
    }

    while(!file.atEnd()){
        qDebug() << "";
        qDebug() << "-------------Ein Durchlauf-------------";
        qDebug() << "";
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

        //qDebug() << "Welche Liste?" << tempOnWhitelist;
        tempTime = QTime::fromString(tempTimeString, "hh:mm:ss");
        tempHour = tempTime.hour();
        //qDebug() << "Eingelesene Zeit: " << tempHour;

        //qDebug() << "Vor findPosition" << _chartRef;

        //existing object is searched in vector
        findPosition(tempName, tempOnWhitelist, tempHour, _chartRef, _appRef, tempUrl);

        //qDebug() << "nach findPosition" << _chartRef;

        //if an old object exist
        if(_lastChangeApp != -1){
            qDebug() << "Prozess existiert bereits";
            if(_chartDataObjects[_lastChangeChart].getHour() == tempHour){
                qDebug() << "Gleiche Stunde - Whitelist - ohne Ueberlauf";
                qDebug() << _chartDataObjects[_lastChangeChart].getHour() << "h - Whitelist: " << _lastChange << " - Nummer in Liste: " << _lastChangeApp;
                _chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].setEndTime(tempTime);
                qDebug() << _chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].getTotalTime();
            } else {
                qDebug() << "Verrechnen mit Nächste Stunde Whitelist";
                hourDifference = tempHour - _chartDataObjects[_lastChangeChart].getHour();
                for(int i = 1; i <= hourDifference; i++){
                    _calcHour = tempHour - hourDifference + i;
                    calcOverflow(_chartDataObjects[_lastChangeChart].getList(_lastChange));
                }
                _chartDataObjects[_lastChangeChart].getList(_lastChange)[_lastChangeApp].setEndTime(tempTime);
            }
            _lastChangeChart = _chartRef;
            _lastChangeApp = tempChart.getList(_lastChange).size()-1;
        }
        //qDebug() << "Vor der if Abfrage" << _chartRef;
        //if instance with actual hour not exist
        if(_chartRef == -1){
            qDebug() << "Neue Stunde";
            tempChart.setHour(tempHour);
            _chartDataObjects.append(tempChart);
            qDebug() << "Geschriebene Zeit: " << tempHour;
            _chartRef = _chartDataObjects.size()-1;
            _lastChangeChart = _chartRef;
        }

        if(tempName == "stopped"){
            _lastChangeApp = -1;
            _lastChangeChart = -1;
            //qDebug() << "Log gestoppt";
            //qDebug() << "";
        } else if(_appRef != -1){
            _chartDataObjects[_chartRef].getList(tempOnWhitelist)[_appRef].setStartTime(tempTime);
            _lastChangeApp = _appRef;
        } else {
            qDebug() << "Neues Objekt anlegen...";
            tempApp.setName(tempName);
            tempApp.setStartTime(tempTime);
            tempApp.setUrl(tempUrl);
            _chartDataObjects[_chartRef].getList(tempOnWhitelist).append(tempApp);
            _lastChangeApp = _chartDataObjects[_chartRef].getList(tempOnWhitelist).size()-1;
            if(tempOnWhitelist){
                qDebug() << "...in die Whitelist";
                _lastChange = true;
            } else {
                qDebug() << "...in die Blacklist";
                _lastChange = false;
            }

        }
    }
    file.close();
    qDebug() << "ende";
}

void Visualize::findPosition(QString name, bool onWhitelist, int hour, int &chartRef, int &appRef, QString url)
{
    if(onWhitelist){
        for(int i = 0; i < _chartDataObjects.size(); i++){
            if(hour == _chartDataObjects[i].getHour()){
                //qDebug() << "findPosition - gleiche Stunde - Whitelist";
                chartRef = i;
                for(int j = 0; j < _chartDataObjects[i].getWhitelist().size(); j++){
                    //qDebug() << "findPosition - ForSchleife - Whitelist";
                    if(name  == _chartDataObjects[i].getWhitelist()[j].getName() && url == _chartDataObjects[i].getWhitelist()[j].getUrl()){
                        appRef = j;
                    } else {
                        appRef = -1;
                    }
                }
            } else {
                //qDebug() << "findPosition - nicht gleiche Stunde - Whitelist";
                chartRef = -1;
                appRef = -1;
            }
        }
    } else {
        for(int i = 0; i < _chartDataObjects.size(); i++){
            if(hour == _chartDataObjects[i].getHour()){
                //qDebug() << "findPosition - gleiche Stunde - Blacklist";
                chartRef = i;
                for(int j = 0; j < _chartDataObjects[i].getBlacklist().size(); j++){
                    //qDebug() << "findPosition - ForSchleife - Whitelist";
                    if(name  == _chartDataObjects[i].getBlacklist()[j].getName() && url == _chartDataObjects[i].getBlacklist()[j].getUrl()){
                        appRef = j;
                    } else {
                        appRef = -1;
                    }
                }
            } else {
                //qDebug() << "findPosition - nicht gleiche Stunde - Blacklist";
                chartRef = -1;
                appRef = -1;
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
    //setEndTimeAndCalc(data, fullHour);

    tempApp.setName(data[_lastChangeApp].getName());
    tempApp.setUrl(data[_lastChangeApp].getUrl());
    tempApp.setStartTime(fullHour);

    qDebug() << "Neue Stunde - Whitelist/Blacklist - Ueberlauf";
    tempChart.setHour(_calcHour);
    _chartDataObjects.append(tempChart);

    qDebug() << "Geschriebene Zeit: " << _calcHour;
    _chartRef = _chartDataObjects.size()-1;

    qDebug() << "Neues Objekt - Whitelist/Blacklist - Ueberlauf";
    tempChart.getList(_lastChange).append(tempApp);

}

/*
void Visualize::setEndTimeAndCalc(QVector<ApplicationData> &data, QTime time)
{
    qDebug() << data[_lastChangeApp].getName() <<
                " totalTime before: " << data[_lastChangeApp].getTotalTime() <<
                " totalTimeAll before: " << data[_lastChangeApp].getTotalTimeAll();
    data[_lastChangeApp].setEndTime(time);
    data[_lastChangeApp].calcTimes();
    qDebug() << data[_lastChangeApp].getName() <<
                " totalTime after: " << data[_lastChangeApp].getTotalTime() <<
                " totalTimeAll after: " << data[_lastChangeApp].getTotalTimeAll();
}
*/


