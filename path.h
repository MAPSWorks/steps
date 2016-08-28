/*
 * path.h -- part of Steps, a simple maps app
 *
 * Copyright 2009-2016 Andy Teijelo <www.ateijelo.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

    void extenderClicked(PathNode *node);
    void removeNode(PathNode *node);
    void removeSelectedNodes();
    void nodeReleased(PathNode *node) { /*TODO*/ }
    void nodeMoved(PathNode *node);
    void setFocus() { /*TODO*/ }
    void nodeSelectedChanged(PathNode *node, bool selected);

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

    PathNode *newExtenderNode(const QList<QGraphicsLineItem *> &parents);
    PathNode *newHoverNode();
    void updateExtenderLines();

    QString _name;
    bool _visible;
    double _length;

    PathNode *head;
    PathNode *tail;
    PathNode *tailExtenderNode;
    PathNode *headExtenderNode;
    PathNode *hoverNode;
    PathEdge *hoverEdge = nullptr;

    QList<PathGraphicsItem*> items;
    QList<QGraphicsLineItem*> tailExtenderLines;
    QList<QGraphicsLineItem*> headExtenderLines;
};

#endif // PATH_H
