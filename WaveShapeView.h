#ifndef WAVESHAPEVIEW_H
#define WAVESHAPEVIEW_H

#include <QObject>
#include <QQmlEngine>

class WaveShapeView : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit WaveShapeView(QObject *parent = nullptr);

signals:
};

#endif // WAVESHAPEVIEW_H
