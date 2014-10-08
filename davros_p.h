/*
    Copyright (c) 2010 Kevin Funk <krf@electrostorm.net>
    Copyright (c) 2011 Casian Andrei <skeletk13@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DAVROSPRIVATE_H
#define DAVROSPRIVATE_H

#include "davros.h"

#include <QtCore/QMutex>
#include <QtCore/QString>
#include <QtCore/QThreadStorage>

class IndentPrivate
    : public QObject
{
private:
    explicit IndentPrivate(QObject* parent, const QString & area);

public:
    static IndentPrivate* instance(const QString & area);

    QThreadStorage<QString *> data;
};

class ContextPrivate
    : public QObject
{
private:
    explicit ContextPrivate(QObject* parent, const QString & area);

public:
    static ContextPrivate* instance(const QString & area);

    QMutex mutex;
    bool debugColorsEnabled;
    QtMsgType debugLevel;
    int colorIndex;
    Davros::LoggingType loggingType;
    QThreadStorage<QString *> logs;
    QThreadStorage<int *> nested;
};

static inline QString reverseColorize( const QString &text, int color, const QString & area)
{
    if( !Davros::debugColorEnabled(area) )
        return text;
    return QString( "\x1b[07;3%1m%2\x1b[00;39m" ).arg( QString::number(color), text );
}

static inline int toColor(QtMsgType level)
{
    switch( level ) {
        case QtWarningMsg:
            return 3; // red
        case QtCriticalMsg:
        case QtFatalMsg:
            return 1; // yellow
        default:
            return 0; // default: black
    }
}

#endif // DAVROSPRIVATE_H
