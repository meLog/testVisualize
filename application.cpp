#include "application.h"

//Setter-------------------------------------------------------------------------
void Application::setName(QString name)
{
    _name = name;
}

void Application::setUrl(QString url)
{
    _url = url;
}

void Application::setTotalTime(long totalTime)
{
    _totalTime = totalTime;
}


//Getter--------------------------------------------------------------------------
QString Application::getName()
{
    return _name;
}

QString Application::getUrl()
{
    return _url;
}

long Application::getTotalTime()
{
    return _totalTime;
}

long Application::getTotalTimeAll()
{
    return _totalTimeAll;
}
