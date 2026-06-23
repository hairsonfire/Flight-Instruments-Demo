#include "FlightDisplayWidget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

FlightDisplayWidget::FlightDisplayWidget(QWidget* parent):
    QWidget(parent)
{
    auto* centralWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(centralWidget);

    auto* titleLabel = new QLabel("Flight Display Panel", centralWidget);
    speedLabel = new QLabel(centralWidget);
    altitudeLabel = new QLabel(centralWidget);

    layout->addWidget(titleLabel);
    layout->addWidget(speedLabel);
    layout->addWidget(altitudeLabel);
    layout->addStretch();

    setSpeed(0);
    setAltitude(0);
}

void FlightDisplayWidget::setSpeed(int speed)
{
    speedLabel->setText(QString("Speed: %1 kt(s)").arg(speed));
}

void FlightDisplayWidget::setAltitude(int altitude)
{
    altitudeLabel->setText(QString("Altitude %1 ft").arg(altitude));
}