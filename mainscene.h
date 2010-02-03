/*
 * This file is part of Honeycomb, a program like Paint or Kolourpaint, but
 * with hexagonal instead of rectangular pixels.
 *
 * Copyright (C) 2007 Andy Teijelo <andy@teijelo.net>
 *
 * Honeycomb is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * Honeycomb is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see http://www.gnu.org/licenses/.
 *
 * The file 'LICENSE' contains the text of the GNU General Public License.
 */
#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsSceneWheelEvent>
#include <QGraphicsScene>

class MainScene : public QGraphicsScene
{
    Q_OBJECT
    public:
        void wheelEvent(QGraphicsSceneWheelEvent *event);

    signals:
        void zoomIn();
        void zoomOut();
};

#endif // MAINSCENE_H
