#pragma once
#include "tilemap.h"
#include <QString>
#include <QRgb>

class TilemapLoader
{
private:
    static const QRgb GRASS =   0xFF337920;
    static const QRgb ASPHALT = 0xFF383433;
    static const QRgb MUD =     0xFF5B4120;
public:
    TilemapLoader() = delete;
    ~TilemapLoader() = delete;
    ///
    /// Permet le chargement de la tilemap à partir d'une image.
    ///
   static Tilemap* load(QString path);
};


