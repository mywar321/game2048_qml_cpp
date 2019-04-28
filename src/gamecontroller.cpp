#include "gamecontroller.h"
#include "tilemodel.h"
#include <QDebug>
GameController::GameController(QObject *parent) : QObject(parent)
{
    for (int i=0;i<16;i++) {
        m_tiles.append(new TileModel(i/4,i%4,i+1));
    }
}

QQmlListProperty<TileModel> GameController::tileList()
{
    return QQmlListProperty<TileModel>(this,nullptr,
                                       GameController::append_tile,
                                       GameController::count_tile,
                                       GameController::at_tile,
                                       GameController::clear_tile);
}

void GameController::moveLeft()
{
    m_tiles.at(0)->setValue(9);

    emit generateNew(3);
}

void GameController::generateNewTile()
{
    m_tiles.at(3)->setValue(0);

    emit generateNew(3);
}

void GameController::append_tile(QQmlListProperty<TileModel> *list, TileModel *tile)
{
    GameController *controller = qobject_cast<GameController *>(list->object);
    if (tile != nullptr)
        controller->m_tiles.append(tile);
}

int GameController::count_tile(QQmlListProperty<TileModel> *list)
{
    GameController *controller = qobject_cast<GameController *>(list->object);
    return  controller->m_tiles.count();
}

TileModel* GameController::at_tile(QQmlListProperty<TileModel> *list, int i)
{
    GameController *controller = qobject_cast<GameController *>(list->object);
    return controller->m_tiles.at(i);
}

void GameController::clear_tile(QQmlListProperty<TileModel> *list)
{
    GameController *controller = qobject_cast<GameController *>(list->object);
    controller->m_tiles.clear();
}







