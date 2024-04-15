#ifndef WAVESHAPEVIEW_H
#define WAVESHAPEVIEW_H

#include <QQuickItem>
#include <QList>
#include <QQmlEngine>
#include <QSGGeometry>
#include "MyAVFrame.h"

class WaveShapeView : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QList<MyAVFrame::Ptr> audioRealBuffer READ audioRealBuffer WRITE setAudioRealBuffer NOTIFY audioRealBufferChanged FINAL)

public:
    explicit WaveShapeView(QQuickItem *parent = nullptr);

    QList<MyAVFrame::Ptr> audioRealBuffer() const;
    void setAudioRealBuffer(QList<MyAVFrame::Ptr> lst);

signals:
    void audioRealBufferChanged();

private:
    virtual QSGNode *updatePaintNode(QSGNode *pOldNode, UpdatePaintNodeData *pData) override;
    void CreateGeometryPoints(QSGGeometry::Point2D *pPoints, const int pointsCount, const QRectF rect);

    size_t GetSampleCount() const;

private:
    QList<MyAVFrame::Ptr> m_lstAudioRealBuffer;
};

#endif // WAVESHAPEVIEW_H
