#include <QSGNode>
#include <QSGFlatColorMaterial>
#include "WaveShapeView.h"

/**
 * @brief WaveShapeView::WaveShapeView
 * @param parent
 */
WaveShapeView::WaveShapeView(QQuickItem *parent) : QQuickItem{parent}
{
    setFlag(QQuickItem::ItemHasContents, true);
}

/**
 * @brief WaveShapeView::audioRealBuffer
 * @return
 */
QList<MyAVFrame::Ptr> WaveShapeView::audioRealBuffer() const
{
    return m_lstAudioRealBuffer;
}

/**
 * @brief WaveShapeView::setAudioRealBuffer
 * @param list
 */
void WaveShapeView::setAudioRealBuffer(QList<MyAVFrame::Ptr> lst)
{
    if(m_lstAudioRealBuffer == lst) return;
    m_lstAudioRealBuffer = lst;
    emit audioRealBufferChanged();
    update();
}

/**
 * @brief WaveShapeView::updatePaintNode
 * @return
 */
QSGNode* WaveShapeView::updatePaintNode(QSGNode* pOldNode, UpdatePaintNodeData* pData)
{
    if(width() <= 0 || height() <= 0)
    {
        delete pOldNode;
        return nullptr;
    }

    if(m_lstAudioRealBuffer.size() == 0)
        return nullptr;

    const QRectF rect = boundingRect();
    const int pointsCount = int(rect.width())*2;
    QSGGeometry *pSGGeometry = nullptr;

    QSGGeometryNode *pSGNode = static_cast<QSGGeometryNode*>(pOldNode);
    if (!pSGNode)
    {
        pSGNode = new QSGGeometryNode;
        pSGNode->setFlag(QSGNode::OwnsMaterial, true);
        pSGNode->setFlag(QSGNode::OwnsGeometry, true);

        pSGGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    }
    else
    {
        pSGGeometry = pSGNode->geometry();
        pSGGeometry->allocate(pointsCount);
    }

    if(pSGGeometry)
    {
        pSGGeometry->setLineWidth(1);
        pSGGeometry->setDrawingMode(QSGGeometry::DrawLines);

        QSGGeometry::Point2D *pPoints = pSGGeometry->vertexDataAsPoint2D();
        if(pPoints)
            CreateGeometryPoints(pPoints, pointsCount, rect);

        pSGNode->setGeometry(pSGGeometry);

        QSGFlatColorMaterial* pMaterial = new QSGFlatColorMaterial();
        if(pMaterial)
        {
            pMaterial->setColor(Qt::green);
            pSGNode->setMaterial(pMaterial);
        }
    }

    return pSGNode;
}

/**
 * @brief WaveShapeView::CreateGeometryPoints
 * @param pPoints
 */
void WaveShapeView::CreateGeometryPoints(QSGGeometry::Point2D* pPoints, const int pointsCount, const QRectF rect)
{
    const size_t samplesCount = GetSampleCount();
    const size_t step = samplesCount / size_t(rect.width());

    auto itFrame = m_lstAudioRealBuffer.begin();
    size_t frameBeginSample = 0;
    for(int i = 0; i < int(rect.width()); ++i)
    {
        size_t sampleOffset = i * step;
        MyAVFrame::Ptr pFrame = *itFrame;
        while(sampleOffset > frameBeginSample + pFrame->GetSamplesCount())
        {
            frameBeginSample += pFrame->GetSamplesCount();
            ++itFrame;
            pFrame = *itFrame;
        }

        // offset w zamach aktualnego frame'a
        size_t offs = sampleOffset - frameBeginSample;

        // wartość słupka
        double y = std::abs(pFrame->GetSample<double>(0, offs));
        y += 0.5;
        // y = std::min<double>(y, 1);
        pPoints[2*i].set(i, y * rect.height());
        pPoints[2*i+1].set(i, (1.0 - y) * rect.height());
    }
}

/**
 * @brief WaveShapeView::GetSampleCount
 * @return
 */
size_t WaveShapeView::GetSampleCount() const
{
    size_t cnt = 0;
    for(MyAVFrame::Ptr pFrame : m_lstAudioRealBuffer)
        cnt += pFrame->GetSamplesCount();
    return cnt;
}
