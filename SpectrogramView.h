#ifndef SPECTROGRAMVIEW_H
#define SPECTROGRAMVIEW_H

#include <QObject>
#include <QQmlEngine>

class SpectrogramView : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SpectrogramView(QObject *parent = nullptr);

signals:
};

#endif // SPECTROGRAMVIEW_H
