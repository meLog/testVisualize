#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <QObject>
#include <QVector>
#include "applicationdata.h"
#include "chartdata.h"

class Visualize
{
QVector<ChartData> _chartDataObjects;

int _lastChangeChart, _lastChangeApp, _chartRef, _appRef, _calcHour;
bool _lastChange;


public:
    Visualize();

    QVector<ChartData> &getChartDataVector();

    void handleDataFromString(QString filepath);

private:
    void findPosition(QString name, bool onWhitelist, int hour, int &chartRef, int &appRef, QString url = "");
    void calcOverflow(QVector<ApplicationData> &data);
    void setEndTimeAndCalc(QVector<ApplicationData> &data, QTime time);




signals:

public slots:
};

#endif // VISUALIZE_H
