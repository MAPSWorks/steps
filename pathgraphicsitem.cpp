#include <QtDebug>
#include <QPen>
#include <QBrush>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <GeographicLib/GeodesicLine.hpp>

#include "pathgraphicsitem.h"
#include "geotools.h"

PathGraphicsItem::PathGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent), head(0), tail(0), length(0.0)
{
//    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(ItemHasNoContents);
    addNode(QPointF(0,0));
    addNode(QPointF(1000,0));
//    addNode(QPointF(2000,0));
//    addNode(QPointF(3000,0));
//    addNode(QPointF(4000,0));
}

void PathGraphicsItem::addNode(const QPointF &pos)
{
    PathNode *n = new PathNode(this);
    n->setPos(pos);
    n->setZValue(2);
    if (head != 0)
    {
        PathNode *m = tail;
        PathEdge *e = new PathEdge(m->pos(),n->pos(),this);
        e->setZValue(1);
        m->outEdge = e;
        m->outNode = n;
        n->inEdge = e;
        n->inNode = m;
        length += e->length();
    }
    else
    {
        head = n;
    }
    tail = n;
}

PathGraphicsItem::~PathGraphicsItem()
{
    PathNode *p = head;
    while (p != 0)
    {
        PathNode *q = p;
        p = p->outNode;
        delete q;
    }
}

QRectF PathGraphicsItem::boundingRect() const
{
    return QRectF();
}

void PathGraphicsItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
}

void PathGraphicsItem::nodeMoved(PathNode *node)
{
    qDebug() << "PathGraphicsItem::nodeMoved:";
    qDebug() << "    length: " << length; 
    if (node->inEdge)
    {
        length -= node->inEdge->length();
        node->inEdge->setP2(node->pos());
        length += node->inEdge->length();
    }
    if (node->outEdge)
    {
        length -= node->outEdge->length();
        node->outEdge->setP1(node->pos());
        length += node->outEdge->length();
    }
    qDebug() << "    length: " << length;
}

void PathGraphicsItem::setPos(const QPointF &pos)
{
    QGraphicsItem::setPos(pos);
    double d = 0;
    PathNode *p = head;
    while (p != 0)
    {
        if (p->outEdge != 0)
        {
            d += p->outEdge->length();
        }
        p = p->outNode;
    }
    length = d;
}

// ---------------- PathNode ----------------

PathNode::PathNode(PathGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), inEdge(0), outEdge(0), inNode(0), outNode(0), parent(parent)
{
    setFlag(ItemSendsScenePositionChanges);
    setBrush(QBrush(Qt::yellow));
    setFlag(ItemIsMovable);
    setCursor(Qt::ArrowCursor);
}

void PathNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal width = 5;
    qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    setRect(-width/lod,-width/lod,2*width/lod,2*width/lod);
    setPen(QPen(QBrush(Qt::red),3/lod));

    QGraphicsEllipseItem::paint(painter,option,widget);
}

QVariant PathNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged)
    {
        parent->nodeMoved(this);
        return QVariant();
    }
    else
    {
        return value;
    }
}

// ---------------- PathEdge ----------------

PathEdge::PathEdge(const QPointF &p1, const QPointF &p2, QGraphicsItem *parent)
    : QGraphicsItem(parent), p1(p1), p2(p2)
{
    setFlag(ItemHasNoContents);
    updateSegments();
}

QRectF PathEdge::boundingRect() const
{
    return QRectF();
}

void PathEdge::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
}

void PathEdge::setP1(const QPointF &p)
{
    p1 = p;
    updateSegments();
}

void PathEdge::setP2(const QPointF &p)
{
    p2 = p;
    updateSegments();
}

void PathEdge::subdivide(QLinkedList<QPointF>& points, QLinkedList<QPointF>::iterator i,
                         double lat1, double lon1, double azi1, double s1, double s2)
{
    const GeographicLib::Geodesic& g = GeographicLib::Geodesic::WGS84;
    if (points.size() >= 8)
        return;
    QPointF p = *i;
    QPointF r = *(i+1);
    double lat2,lon2;
    g.Direct(lat1,lon1,azi1,(s1+s2)/2,lat2,lon2);
    QPointF q(GeoTools::LatLon2Meters(QPointF(lon2,lat2)));

    qDebug() << "points:" << p << q << r;
    double ax = q.x()-p.x();
    double ay = q.y()-p.y();
    double d2a = ax*ax + ay*ay;
    double bx = r.x()-q.x();
    double by = r.y()-q.y();
    double d2b = bx*bx + by*by;
    double adotb = ax*bx + ay*by;
    double cos2 = adotb * qAbs(adotb) / (d2a * d2b);
    qDebug() << "cos2:" << cos2;

    if (cos2 < 0.999)
    {
        points.insert(i+1,q);
        subdivide(points,i,lat1,lon1,azi1,s1,(s1+s2)/2);
        subdivide(points,i+1,lat1,lon1,azi1,(s1+s2)/2,s2);
    }

}

void PathEdge::updateSegments()
{
    const GeographicLib::Geodesic& g = GeographicLib::Geodesic::WGS84;
    GeoTools gt;
    QPointF q1 = mapToScene(p1);
    QPointF q2 = mapToScene(p2);
    q1 = gt.Meters2LatLon(p1);
    q2 = gt.Meters2LatLon(p2);
    double azi1, azi2, s12;
    g.Inverse(q1.y(),q1.x(),q2.y(),q2.x(),s12,azi1,azi2);

    QLinkedList<QPointF> points;
    points.append(p1);
    points.append(p2);
    subdivide(points,points.begin(),q1.y(),q1.x(),azi1,0,s12);

    QLinkedList<PathEdgeSegment*>::iterator si = segments.begin();
    QLinkedList<QPointF>::iterator i = points.begin();
    while (true)
    {
        if (i == points.end())
            break;
        if ((i+1) == points.end())
            break;
        PathEdgeSegment *s;
        if (si != segments.end())
        {
            s = *si;
            si++;
        }
        else
        {
            s = new PathEdgeSegment(this);
            segments.append(s);
        }
        s->setLine(QLineF(*i,*(i+1)));
        i++;
    }
    while (si != segments.end())
    {
        delete *si;
        si = segments.erase(si);
    }
    qDebug() << "updateSegments:";
    foreach (PathEdgeSegment *s, segments)
        qDebug() << "   " << s->line();
}

double PathEdge::length() const
{
    QPointF q1 = mapToScene(p1);
    QPointF q2 = mapToScene(p2);
    GeoTools gt;
    q1 = gt.Meters2LatLon(p1);
    q2 = gt.Meters2LatLon(p2);
    const GeographicLib::Geodesic& g = GeographicLib::Geodesic::WGS84;
    double azi1, azi2,s12;
    g.Inverse(q1.y(),q1.x(),q2.y(),q2.x(),s12,azi1,azi2);

    return s12;
}

// ---------------- PathEdge ----------------

PathEdgeSegment::PathEdgeSegment(QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
}

void PathEdgeSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal width = 3;
    qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    setPen(QPen(QBrush(Qt::red),width/lod,Qt::SolidLine,Qt::RoundCap));

    QGraphicsLineItem::paint(painter,option,widget);
}
