#include <QCoreApplication>
#include "applicationdata.h"
#include "visualize.h"
#include "chartdata.h"
#include <QDebug>
#include <QtAlgorithms>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Visualize myVis;
    //myVis.handleDataFromString("C:\\Users\\Rick\\Google Drive\\FH Sachen\\5. Semester\\EMS\\ricks code\\maitime-20151026.json");
    myVis.handleDataFromString("C:\\maitime-20151026.json");
    //qDebug() << myVis.getChartDataVector()[4].getWhitelist()[0].getName() << myVis.getChartDataVector()[4].getWhitelist()[0].getTotalTime();
    //qDebug() << myVis.getChartDataVector()[4].getBlacklist()[0].getName() << myVis.getChartDataVector()[4].getBlacklist()[0].getTotalTime();


    std::sort(myVis.getAppclicationsVector().begin(), myVis.getAppclicationsVector().end());

    qDebug() << "";
    qDebug() << "-----------------Ausgabe-----------------";
    for(int i = 0; i < myVis.getChartDataVector().size(); i++){
        qDebug() << "Stunde: " << myVis.getChartDataVector()[i].getHour();
    }


    for(int i = 0; i < myVis.getChartDataVector().size(); i++){

        qDebug() << "--------Whitelist--------";
        qDebug() << "Anzahl Prozesse: " << myVis.getChartDataVector()[i].getWhitelist().size();
        for(int j = 0; j < myVis.getChartDataVector()[i].getWhitelist().size(); j++){

            std::sort(myVis.getChartDataVector()[i].getWhitelist().begin(), myVis.getChartDataVector()[i].getWhitelist().end());

            qDebug() << "Stunde: " << myVis.getChartDataVector()[i].getHour() <<
                        "Name: " << myVis.getChartDataVector()[i].getWhitelist()[j].getName() <<
                        "Zeit: " << myVis.getChartDataVector()[i].getWhitelist()[j].getTotalTime();
        }

        qDebug() << "--------Blacklist--------";
        qDebug() << "Anzahl Prozesse: " << myVis.getChartDataVector()[i].getWhitelist().size();
        for(int j = 0; j < myVis.getChartDataVector()[i].getBlacklist().size(); j++){

            std::sort(myVis.getChartDataVector()[i].getBlacklist().begin(), myVis.getChartDataVector()[i].getBlacklist().end());

            qDebug() << "Stunde: " << myVis.getChartDataVector()[i].getHour() <<
                        "Name: " << myVis.getChartDataVector()[i].getBlacklist()[j].getName() <<
                        "Zeit: " << myVis.getChartDataVector()[i].getBlacklist()[j].getTotalTime();
        }
    }
    for (int i=0; i < myVis.getAppclicationsVector().count(); i++)
        qDebug() << "Application: " << myVis.getAppclicationsVector()[i].getName() <<
                    " Zeit: " << myVis.getAppclicationsVector()[i].getTotalTime();

    return a.exec();
}

