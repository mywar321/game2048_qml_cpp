#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QQmlListProperty>
class TileModel;
class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<TileModel> tileList READ tileList NOTIFY tileListChanged)
public:
    explicit GameController(QObject *parent = nullptr);

    QQmlListProperty<TileModel> tileList();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void generateNewTile();
signals:
    void tileListChanged();
    void generateNew(int i);
public slots:

private:
    static void append_tile(QQmlListProperty<TileModel> *list, TileModel *tile);
    static int count_tile(QQmlListProperty<TileModel> *list);
    static TileModel* at_tile(QQmlListProperty<TileModel> *list, int i);
    static void clear_tile(QQmlListProperty<TileModel> *list);
    QList<TileModel *> m_tiles;
};

#endif // GAMECONTROLLER_H
