//
// Route.cpp
//
// Copyright (C) 2017
//

#include <QRegularExpression>

#include "Route.h"

namespace TransportSystemDlg {

const unsigned Route::MAX_ROUTE_DISTANCE = 1000;
const unsigned Route::MAX_ROUTE_DAILY_REPEATS = 50;

const QString Route::ROUTE_REGULAR_EXPRESSION_VALID = "([a-zA-Z0-9 ;]*)";
const QString Route::ROUTE_REGULAR_EXPRESSION_INVALID = "([^a-zA-Z0-9 ;]+)";

Route::Route()
{
    mPoints = "";
    mDistance = 0;
    mDailyRepeats = 0;
}

Route::Route(const QString &points, unsigned distance, unsigned dailyRepeats)
{
    setPoints(points);
    setDistance(distance);
    setDailyRepeats(dailyRepeats);
}

Route::~Route()
{
}

const QString &Route::points() const
{
    return mPoints;
}

void Route::setPoints(const QString &points)
{
    mPoints = points;
}

unsigned Route::distance() const
{
    return mDistance;
}

void Route::setDistance(unsigned distance)
{
    mDistance = distance;
}

unsigned Route::dailyRepeats() const
{
    return mDailyRepeats;
}

void Route::setDailyRepeats(unsigned dailyRepeats)
{
    mDailyRepeats = dailyRepeats;
}

bool Route::pointsValid(const QString &points)
{
    QRegularExpression re(ROUTE_REGULAR_EXPRESSION_INVALID);

    return !points.contains(re);
}

bool Route::distanceValid(unsigned distance)
{
    return distance <= MAX_ROUTE_DISTANCE;
}

bool Route::dailyRepeatsValid(unsigned dailyRepeats)
{
    return dailyRepeats <= MAX_ROUTE_DAILY_REPEATS;
}

QDebug operator<<(QDebug debug, const Route &route) {
    QString str;
    str += route.points() + " ";
    str += QString("%1 ").arg(route.distance());
    str += QString("%1 ").arg(route.dailyRepeats());
    debug << str;
    return debug;
}

}   // namespace TransportSystemDlg


