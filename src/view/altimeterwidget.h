#pragma once

#include <QOpenGLWidget>

class AltimeterWidget: public QWidget
{
public:

    explicit AltimeterWidget(QWidget* parent = nullptr);

    void setAltitude(double altitude);

private:

    int m_altitude;

    void paintEvent(QPaintEvent* event) override;
    void drawAllNeedles(QPainter& painter);
    void drawNeedle(QPainter& painter, int needleWidth, int needleLength, double maxValue, double minValue);
    void drawFrame(QPainter& painter);
    void drawScale(QPainter& painter);
};
