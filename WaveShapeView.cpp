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

    size_t sampleOffset = 0;
    const float hoffs = 0.5;
    for(int i = 0; i < pointsCount/2; ++i)
    {
        // float y = float(abs(rand() % 50)) / 100.0;
        float y = GetSample(sampleOffset);
        sampleOffset += step;
        y += hoffs;
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

/**
 * @brief WaveShapeView::GetSample
 * @param offs
 * @return
 */
double WaveShapeView::GetSample(size_t offs)
{
    size_t n = 0;
    for(MyAVFrame::Ptr pFrame : m_lstAudioRealBuffer)
    {
        size_t samplesCount = pFrame->GetSamplesCount();
        if(n + samplesCount < offs)
        {
            n += samplesCount;
            continue;
        }
    }
    return 0;
}
