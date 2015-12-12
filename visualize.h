#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QObject>
#include <QVector>
#include "chartdata.h"
#include "application.h"
#include "applicationdata.h"


class Visualize
{
    int _lastChangeChart;
    int _lastChangeApp;
    int _chartRef;
    int _appRef;
    int _calcHour;

    bool _lastChange;

    QVector<ChartData> _chartDataObjects;

    QVector<Application> _applications;


public:
    Visualize();

    QVector<ChartData> &getChartDataVector();
    QVector<Application> &getAppclicationsVector();

    void handleDataFromString(QString filepath);

private:
    void findPosition(QString name, bool onWhitelist, int hour, int &chartRef, int &appRef, QString url = "");
    void calcOverflow(QVector<ApplicationData> &data);
    void setEndTimeAndCalc(QVector<ApplicationData> &data, QTime time);
    int findApplication(QString app);

signals:

public slots:
};

#endif // VISUALIZE_H
