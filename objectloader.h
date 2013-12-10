#pragma once

#include "scene.h"
#include <QString>

using namespace std;

///
/// Classe servant au chargement des objets d'une scène depuis un fichier json
///
class ObjectLoader
{
public:

    ///
    /// Constructeur
    ///
    ObjectLoader(Scene *scene=nullptr, const QString& carClassName=nullptr);

    ///
    /// Constructeur de copie
    ///
    ObjectLoader(const ObjectLoader &copy);

    ///
    /// Opérateur d'affectation
    ///
    ObjectLoader& operator=(const ObjectLoader &copy);

    ///
    /// Scène dans laquelle les objets doivent être créés.
    ///
    Scene *scene() const;

    ///
    /// Nom de la classe de la voiture du joueur
    ///
    const QString& carClassName() const;

    ///
    /// Charge les objets et les ajoute à la scène.
    ///
    bool load(const QString& filename);

    ///
    /// Nombre de checkpoints créés par le loader
    ///
    int checkpointCount() const;

private:

    Scene  *m_scene;
    QString m_carClassName;
    int     m_checkpointCount;
};
