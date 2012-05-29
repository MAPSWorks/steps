#ifndef PATHGRAPHICSITEM_H
#define PATHGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QLinkedList>
#include <QSet>

class PathEdgeSegment : public QGraphicsLineItem
{
    public:
        PathEdgeSegment(QGraphicsItem *parent = 0);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class PathEdge : public QGraphicsItem
{
    public:
        PathEdge(const QPointF& p1, const QPointF& p2, QGraphicsItem *parent = 0);
        QRectF boundingRect() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        double length() const;
        void setP1(const QPointF& p);
        void setP2(const QPointF& p);

    private:
        void updateSegments();
        void subdivide(QLinkedList<QPointF>& points, QLinkedList<QPointF>::iterator i,
                       double lat1, double lon1, double azi1, double s1, double s2, int depth);

        QPointF p1;
        QPointF p2;
        QLinkedList<PathEdgeSegment*> segments;
};

class PathGraphicsItem;

class PathNode : public QGraphicsEllipseItem
{
    public:
        PathNode(PathGraphicsItem *parent);

        PathEdge *inEdge;
        PathEdge *outEdge;
        PathNode *inNode;
        PathNode *outNode;
        PathGraphicsItem *parent;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
};

class PathGraphicsItem : public QGraphicsItem
{
    public:
        explicit PathGraphicsItem(QGraphicsItem *parent = 0);
        ~PathGraphicsItem();
        QRectF boundingRect() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void addNode(const QPointF& pos);
        void nodeMoved(PathNode *node);
        void setPos(const QPointF &pos);

    signals:

    public slots:

    private:
        PathNode *head;
        PathNode *tail;
        double length;
};

#endif // PATHGRAPHICSITEM_H
