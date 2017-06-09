//
// Route.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_ROUTE_H
#define TRANSPORTSYSTEMGUI_ROUTE_H

#include <QString>
#include <QList>

namespace TransportSystemDlg {

class Route
{
public:
    Route();
    ~Route();

    unsigned id() const;
    void setId(unsigned id);

    const QList<QString> &points() const;
    void setPoints(const QList<QString> &points);

//    QString point(unsigned num) const;
//    void setPoint(unsigned num, QString point);

    unsigned distance() const;
    void setDistance(unsigned distance);

    unsigned dailyRepeats() const;
    void setDailyRepeats(unsigned dailyRepeats);

private:
    unsigned mId;
    QList<QString> mPoints;
    unsigned mDistance;
    unsigned mDailyRepeats;
};

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_ROUTE_H

