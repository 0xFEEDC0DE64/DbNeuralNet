#include "debug.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>

QFile file("log.txt");
QTextStream textStream(&file);

bool initDebug()
{
    if(!file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << file.errorString();
        return false;
    }

    return true;
}

void debug(const QString &line)
{
    textStream << line << endl;
}
