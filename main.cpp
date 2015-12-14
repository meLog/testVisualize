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
    //qDebug() << myVis.getChartDataVector()[4].getList(true)[0].getName() << myVis.getChartDataVector()[4].getList(true)[0].getTotalTime();
    //qDebug() << myVis.getChartDataVector()[4].getList(false)[0].getName() << myVis.getChartDataVector()[4].getList(false)[0].getTotalTime();


    std::sort(myVis.getAppclicationsVector().begin(), myVis.getAppclicationsVector().end());

    qDebug() << "";
    qDebug() << "-----------------Ausgabe-----------------";
    for(int i = 0; i < myVis.getChartDataVector().size(); i++){
        qDebug() << "Stunde: " << myVis.getChartDataVector()[i].getHour();
    }


    for(int i = 0; i < myVis.getChartDataVector().size(); i++){

        qDebug() << "--------Whitelist--------";
        qDebug() << "Anzahl Prozesse: " << myVis.getChartDataVector()[i].getList(true).size();
        for(int j = 0; j < myVis.getChartDataVector()[i].getList(true).size(); j++){

            std::sort(myVis.getChartDataVector()[i].getList(true).begin(), myVis.getChartDataVector()[i].getList(true).end());

            qDebug() << "Stunde: " << myVis.getChartDataVector()[i].getHour() <<
                        "Name: " << myVis.getChartDataVector()[i].getList(true)[j].getName() <<
                        "Zeit: " << myVis.getChartDataVector()[i].getList(true)[j].getTotalTime();
        }

        qDebug() << "--------Blacklist--------";
        qDebug() << "Anzahl Prozesse: " << myVis.getChartDataVector()[i].getList(false).size();
        for(int j = 0; j < myVis.getChartDataVector()[i].getList(false).size(); j++){

            std::sort(myVis.getChartDataVector()[i].getList(false).begin(), myVis.getChartDataVector()[i].getList(false).end());

            qDebug() << "Stunde: " << myVis.getChartDataVector()[i].getHour() <<
                        "Name: " << myVis.getChartDataVector()[i].getList(false)[j].getName() <<
                        "Zeit: " << myVis.getChartDataVector()[i].getList(false)[j].getTotalTime();
        }
    }
    for (int i=0; i < myVis.getAppclicationsVector().count(); i++)
        qDebug() << "Application: " << myVis.getAppclicationsVector()[i].getName() <<
                    " Zeit: " << myVis.getAppclicationsVector()[i].getTotalTime();

    return a.exec();
}

