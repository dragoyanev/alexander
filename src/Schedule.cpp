//
// Schedule.cpp
//
// Copyright (C) 2017
//

#include "Schedule.h"

namespace TransportSystemDlg {

Schedule::Schedule()
{
    mId = 0;
    mVechicleId = 0;
    mRouteId = 0;
}

Schedule::~Schedule()
{
}

unsigned Schedule::id() const
{
    return mId;
}

void Schedule::setId(unsigned id)
{
    mId = id;
}

unsigned Schedule::vechicleId() const
{
    return mVechicleId;
}

void Schedule::setVechicleId(unsigned vechicleId)
{
    mVechicleId = vechicleId;
}

unsigned Schedule::routeId() const
{
    return mRouteId;
}

void Schedule::setRouteId(unsigned routeId)
{
    mRouteId = routeId;
}

}   // namespace TransportSystemDlg


