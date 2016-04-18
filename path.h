#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QGraphicsScene>

#include "pathgraphicsitem.h"
#include "pathnode.h"
#include "pathedge.h"

class Path : public QObject
{
    Q_OBJECT
public:
    explicit Path(const QPointF& from,
                  const QPointF& to,
                  QObject *parent = 0);

    void addToScene(QGraphicsScene *scene);

    QString name() const { return _name; }
    void setName(const QString& name);

    bool isVisible() const { return _visible; }
    void setVisible(bool visible);

    double length() const { return _length; }
    void setLength(double l);

    void addEdge(PathNode *from, PathNode *to);

    void extenderClicked(PathNode *node) { /*TODO*/ }
    void removeNode(PathNode *node) { /*TODO*/ }
    void nodeReleased(PathNode *node) { /*TODO*/ }
    void nodeMoved(PathNode *node);
    void setFocus() { /*TODO*/ }
    void nodeSelectedChanged(PathNode *node, bool selected) { /*TODO*/ }

    void edgeHovered(PathEdge *e, const QPointF& pos);

    const QList<PathGraphicsItem*>& graphicItems() const { return items; }

//    QPointF headPos() const;
//    QPointF tailPos() const;
//    qreal headAngle() const;
//    qreal tailAngle() const;

    QPointF mapToScene(const QPointF& p);
    QPointF mapFromScene(const QPointF& p);

signals:
    void nameChanged(const QString&);
    void visibleChanged(bool);
    void lengthChanged(double length);

public slots:
    
private:

    PathNode *newExtenderNode(QGraphicsItem *parent);
    void createHoverNode();
    void updateExtenderLines();

    QList<PathGraphicsItem*> items;
    QString _name;
    bool _visible;
    double _length;

    PathNode *head;
    PathNode *tail;
    PathNode *tailExtenderNode;
    PathNode *headExtenderNode;
    PathNode *hoverNode;
    PathEdge *hoverEdge;
};

#endif // PATH_H
