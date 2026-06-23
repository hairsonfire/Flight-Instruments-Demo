#include "AltimeterWidget.h"

#include <QPainter>

AltimeterWidget::AltimeterWidget(QWidget* parent):
    QWidget(parent),
    m_altitude(0.0)
{
}

void AltimeterWidget::setAltitude(double altitude)
{
    m_altitude = altitude;

    update();
}

void AltimeterWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    painter.setRenderHint(QPainter::Antialiasing);

    drawFrame(painter);
    drawAllNeedles(painter);
    drawScale(painter);

    painter.end();
}

void AltimeterWidget::drawAllNeedles(QPainter& painter)
{
    const int needleLength100 = qMin(width(), height()) / 2 - 80;
    const int needleLength1000 = qMin(width(), height()) / 2 - 120;

    drawNeedle(painter, 25, needleLength1000, 10000, m_altitude);
    drawNeedle(painter, 20, needleLength100, 1000, m_altitude);
}

void AltimeterWidget::drawNeedle(QPainter& painter, int needleWidth, int needleLength, double maxValue, double value)
{
    painter.translate(width() / 2, height() / 2);

    double needleAngle = std::fmod(360.0 * value / maxValue, 360.0);

    painter.rotate(needleAngle);

    const int needleCenterOffset = 10;
    const int needleTipLength = 10;

    QPoint points[5] =
        {
            QPoint(- needleWidth / 2, - needleCenterOffset),
            QPoint(- needleWidth / 2, - needleCenterOffset - needleLength + needleTipLength),
            QPoint(0, - needleCenterOffset - needleLength),
            QPoint(needleWidth / 2, - needleCenterOffset - needleLength + needleTipLength),
            QPoint(needleWidth / 2, - needleCenterOffset),
        };

    painter.setPen(QPen(Qt::black, 0));
    painter.setBrush(Qt::white);

    painter.drawPolygon(points, 5);

    painter.resetTransform();
}

void AltimeterWidget::drawFrame(QPainter& painter)
{
    int size = qMin(width(), height()) - 40;
    QRect instrumentRect(
        (width() - size) / 2,
        (height() - size) / 2,
        size,
        size
        );

    painter.setPen(QPen(Qt::black, 0));
    painter.setBrush(Qt::black);
    painter.drawEllipse(instrumentRect);
}

void AltimeterWidget::drawScale(QPainter& painter)
{
    painter.setPen(QPen(Qt::white, 4));

    int centerX = width() / 2;
    int centerY = height() / 2;

    int radius = qMin(width(), height()) / 2;

    int altitude = 0;

    painter.setFont(QFont("Arial", 20));

    QFontMetrics fontMetrics = painter.fontMetrics();

    for (int angle = 0; angle < 360; angle += 36)
    {

        QString text = QString::number(altitude);
        altitude = altitude + 1;

        double rad = qDegreesToRadians(static_cast<double>(angle - 90));

        int textWidth = fontMetrics.horizontalAdvance(text);

        int textX = centerX + std::cos(rad) * (radius - 100) - textWidth / 2;
        int textY = centerY + std::sin(rad) * (radius - 100) + fontMetrics.ascent() / 2;

        int lineX1 = centerX + std::cos(rad) * (radius - 40);
        int lineY1 = centerY + std::sin(rad) * (radius - 40);
        int lineX2 = centerX + std::cos(rad) * (radius - 60);
        int lineY2 = centerY + std::sin(rad) * (radius - 60);

        painter.drawText(textX, textY, text);
        painter.drawLine(lineX1, lineY1, lineX2, lineY2);

        for(int lineCount = 1; lineCount < 10; lineCount += 1)
        {
            double subRad = qDegreesToRadians(static_cast<double>(angle - 90 + 3.6 * lineCount));
            QPointF p1(
                centerX + std::cos(subRad) * (radius - 40),
                centerY + std::sin(subRad) * (radius - 40)
                );

            QPointF p2(
                centerX + std::cos(subRad) * (radius - 45),
                centerY + std::sin(subRad) * (radius - 45)
                );
            painter.drawLine(p1, p2);
        }
    }
}