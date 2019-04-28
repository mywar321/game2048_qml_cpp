/*
** 2048游戏，游戏逻辑用C++实现，界面和动画用QML实现
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tilemodel.h"
#include "gamecontroller.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //qmlRegisterType<TileModel>("com.game2048.TileModel",1,0,"TileModel");
    qmlRegisterType<GameController>("com.game2048.GameController",1,0,"GameController");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
