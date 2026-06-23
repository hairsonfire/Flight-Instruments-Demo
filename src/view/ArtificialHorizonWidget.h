#pragma once

#include <QOpenGLWidget>

class ArtificialHorizonWidget: public QWidget{
public:
    explicit ArtificialHorizonWidget(QWidget* parent = nullptr);

    void setPitch(double pitch);
    void setRoll(double roll);
private:
    void paintEvent(QPaintEvent* event) override;

    void drawHorizon(QPainter& painter);
    void drawInstrumentFrame(QPainter& painter);
    void drawAircraftReference(QPainter& painter);
    void drawRollScale(QPainter& painter);
    void drawPitchScale(QPainter& painter, int horizonY);
    void drawRollPointer(QPainter& painter);

    double m_pitch;
    double m_roll;

    static constexpr int PIXELS_PER_DEGREE = 2;
};
