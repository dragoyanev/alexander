//
// Schedule.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_SCHEDULE_H
#define TRANSPORTSYSTEMGUI_SCHEDULE_H

#include <QString>
#include <QList>

namespace TransportSystemDlg {

class Schedule
{
public:
    Schedule();
    ~Schedule();

    unsigned id() const;
    void setId(unsigned id);

    unsigned vechicleId() const;
    void setVechicleId(unsigned vechicleId);

    unsigned routeId() const;
    void setRouteId(unsigned routeId);

private:
    unsigned mId;
    unsigned mVechicleId;
    unsigned mRouteId;
};

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_SCHEDULE_H

