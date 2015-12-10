#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QString>
#include <QTime>
#include <QDebug>
#include <QVector>


class Application
{
protected:
    QString _name;
    QString _url;
    long _totalTime;
    static long _totalTimeAll;

public:
    Application(QString name = "", QString url = ""): _name(name), _url(url), _totalTime(0) {}

    //Setter
    void setName(QString name);
    void setUrl(QString url);
    void setTotalTime(long totalTime);

    //Getter
    QString getName();
    QString getUrl();
    long getTotalTime();

    static long getTotalTimeAll();

signals:

public slots:
};

#endif // APPLICATION_H
