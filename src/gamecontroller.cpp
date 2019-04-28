#include "gamecontroller.h"
#include "tilemodel.h"
#include <QRandomGenerator>
#include <QDebug>
GameController::GameController(QObject *parent) : QObject(parent)
{

}

void GameController::moveLeft()
{//TODO： 考虑边界问题
    clearFlag();
    for (int i=0;i<4;i++) {
        for (int j=1;j<4;j++) {
            int k = j;
            //向左找寻，如果是空白就移动到空白处，如果相等则合并，否则退出循环
            while (k > 0 && !m_tiles[i][k]->isBlank() && !m_tiles[i][k-1]->isMerged()) {
                if (m_tiles[i][k-1]->isBlank()) {
                    moveTile(m_tiles[i][k], m_tiles[i][k-1]);
                }
                else if (m_tiles[i][k-1]->value() == m_tiles[i][k]->value()) {
                    mergeTile(m_tiles[i][k],m_tiles[i][k-1]);
                    break;
                }
                else {
                    break;
                }
                k--;
            }
        }
    }
    newTile();


}

void GameController::moveRight()
{
    clearFlag();
    for (int i=0;i<4;i++) {
        for (int j=2;j>-1;j--) {
            int k = j;

            while (k < 3 && !m_tiles[i][k]->isBlank() && !m_tiles[i][k+1]->isMerged()) {
                if (m_tiles[i][k+1]->isBlank()) {
                    moveTile(m_tiles[i][k], m_tiles[i][k+1]);
                }
                else if (m_tiles[i][k+1]->value() == m_tiles[i][k]->value()) {
                    mergeTile(m_tiles[i][k],m_tiles[i][k+1]);
                    break;
                }
                else {
                    break;
                }
                k++;
            }
        }
    }
    newTile();
}

void GameController::moveUp()
{
    clearFlag();
    for (int i=0;i<4;i++) {
        for (int j=1;j<4;j++) {
            int k = j;
            //向左找寻，如果是空白就移动到空白处，如果相等则合并，否则退出循环
            while (k > 0 && !m_tiles[i][k]->isBlank() && !m_tiles[i][k-1]->isMerged()) {
                if (m_tiles[i][k-1]->isBlank()) {
                    moveTile(m_tiles[i][k], m_tiles[i][k-1]);
                }
                else if (m_tiles[i][k-1]->value() == m_tiles[i][k]->value()) {
                    mergeTile(m_tiles[i][k],m_tiles[i][k-1]);
                    break;
                }
                else {
                    break;
                }
                k--;
            }
        }
    }
    newTile();
}

void GameController::moveDown()
{
    clearFlag();
    for (int i=0;i<4;i++) {
        for (int j=1;j<4;j++) {
            int k = j;
            //向左找寻，如果是空白就移动到空白处，如果相等则合并，否则退出循环
            while (k > 0 && !m_tiles[i][k]->isBlank() && !m_tiles[i][k-1]->isMerged()) {
                if (m_tiles[i][k-1]->isBlank()) {
                    moveTile(m_tiles[i][k], m_tiles[i][k-1]);
                }
                else if (m_tiles[i][k-1]->value() == m_tiles[i][k]->value()) {
                    mergeTile(m_tiles[i][k],m_tiles[i][k-1]);
                    break;
                }
                else {
                    break;
                }
                k--;
            }
        }
    }
    newTile();
}

void GameController::gameStart()
{
    initTiles();
    newTile();
    newTile();
}

void GameController::initTiles()
{

    for (int i=0;i<4;i++) {
        QVector<TileModel *> tempV;
        for (int j=0;j<4;j++) {
            tempV.append(new TileModel(i,j,0));
        }
        m_tiles.append(tempV);
    }
}

bool GameController::isGameOver()
{
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            if (m_tiles[i][j]->value() == 0)
                return false;
            if (i > 0 &&
                    m_tiles[i-1][j]->value() == m_tiles[i][j]->value())
                return false;
            if (j > 0 &&
                    m_tiles[i][j-1]->value() == m_tiles[i][j]->value())
                return false;
        }
    }
    return true;
}

void GameController::newTile()
{
    if (isGameOver()) {
        emit gameIsOver();
        return;
    }
    QVector<TileModel *>  zeros;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            if (m_tiles[i][j]->value() == 0) {
                zeros.append(m_tiles[i][j]);
            }
        }
    }
    if (zeros.size() == 0)
        return;

    int new_i = QRandomGenerator::global()->bounded(0,zeros.size()-1);
    int new_value = (QRandomGenerator::global()->bounded(1,100) < 90) ? 1 : 2;  // 新格子数值2和4的概率 9比1
    zeros[new_i]->setValue(new_value);
    emit generateNewTile(zeros[new_i]->x(),
                         zeros[new_i]->y(),
                         zeros[new_i]->value());

}

void GameController::mergeTile(TileModel *a, TileModel *b) //a融合到b
{
    b->setValue(b->value()+1);
    a->setValue(0);
    b->setIsMerged(true);
    emit moveAndMerge(a->x()*4+a->y(),b->x()*4+b->y(),b->value());
}

void GameController::moveTile(TileModel *a, TileModel *b) //a移动到b
{
    b->setValue(a->value());
    b->setIsMerged(a->isMerged());
    a->setValue(0);
    a->setIsMerged(false);
    emit moveAndMerge(a->x()*4+a->y(),b->x()*4+b->y(),b->value());
}

void GameController::clearFlag()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            m_tiles[i][j]->setIsMerged(false);
}









