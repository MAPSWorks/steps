#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <QHash>
#include <QRect>
#include <QObject>
#include <QPoint>
#include <QByteArray>
#include <QLinkedList>

#include "tile.h"
#include "tilefetcher.h"

class TileLayer : public QObject
{
    Q_OBJECT

    typedef QLinkedList<Tile*> Column;
    typedef Column::iterator TilePointer;
    typedef QLinkedList<Column*>::iterator ColumnPointer;

    public:
        TileLayer();
        void setRegion(const QRect& r, int zoom);
        void clear();

    signals:
        void tileCreated(Tile *t,int x, int y, int zoom);

    private slots:
        void tileData(const QString& type, int x, int y, int z,
                           const QByteArray& bytes);

    private:
        ColumnPointer adjustBeforeIntersection(const QRect& n);
        void adjustColumn(Column* col, const QRect& n, int x);
        void adjustAfterIntersection(const QRect& n);
        void deleteColumn(Column* col);
        Tile* newTile(int x, int y);
        void deleteTile(Tile *t);
        QString tileKey(QString type, int x, int y, int z);

        int zoom;
        QString type;
        QString tileKeyTemplate;
        QRect region;
        TileFetcher fetcher;
        QLinkedList<Column*> columns;
        QHash<TileCoords,Tile*> tiles; // TileCoords is defined in tile.h

};

#endif // TILEMANAGER_H
