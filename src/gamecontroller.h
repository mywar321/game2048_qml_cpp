#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>
class TileModel;
class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QObject *parent = nullptr);

/********控制器操作接口**********/
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void gameStart();
/********控制器操作接口**********/


signals:
    void gameIsOver();
    void generateNewTile(int i, int j, int value);
    void merge(int src, int dst, int value);
    void move(int src, int dst,int value);
public slots:

private:
    void initTiles();
    bool isGameOver();
    void newTile();
    void mergeTile(TileModel *a, TileModel *b);
    void moveTile(TileModel *a, TileModel *b);
    void clearFlag();
    QVector<QVector<TileModel *>> m_tiles;

};

#endif // GAMECONTROLLER_H
