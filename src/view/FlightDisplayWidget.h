#pragma once

#include <QWidget>

class QLabel;

class FlightDisplayWidget: public QWidget
{
public:
    explicit FlightDisplayWidget(QWidget* parent = nullptr);

    void setSpeed(int speed);
    void setAltitude(int altitude);

private:
    QLabel* speedLabel;
    QLabel* altitudeLabel;
};
