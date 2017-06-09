//
// Route.cpp
//
// Copyright (C) 2017
//

#include "Route.h"

namespace TransportSystemDlg {

Route::Route()
{
    mId = 0;
    mPoints.clear();
    mDistance = 0;
    mDailyRepeats = 0;
}

Route::~Route()
{
}

unsigned Route::id() const
{
    return mId;
}

void Route::setId(unsigned id)
{
    mId = id;
}

const QList<QString> &Route::points() const
{
    return mPoints;
}

void Route::setPoints(const QList<QString> &points)
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

}   // namespace TransportSystemDlg


