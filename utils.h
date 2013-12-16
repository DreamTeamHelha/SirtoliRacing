#pragma once

#include <QString>
#include <QJsonArray>

/*
 * Regroupe des fonctions utilitaires
 */
namespace utils
{
    ///
    /// Retourne la valeur de pi
    ///
    inline float pi()
    {
        return 3.14159265;
    }

    ///
    /// Conversion degrés -> radians
    ///
    inline float toRadians(float degrees)
    {
        return pi() * degrees / 180;
    }

    ///
    /// Conversion degrés -> radians
    ///
    inline float toDegrees(float radians)
    {
        return 180 * radians / pi();
    }

    ///
    /// Converti un temps en milisecondes en une chaine de caractère
    /// au format minutes:secondes:centièmes
    ///
    QString showableTime(int ms);

    ///
    /// Parse un fichier json et retourne le tableau à sa racine.
    ///
    QJsonArray readJsonFile(QString path);
}
