#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    Settings();
    bool dynamicZoom()const
    {
        return m_dynamicZoom;
    }
    void setDynamicZoom(bool dynamicZoom)
    {
        m_dynamicZoom=dynamicZoom;
    }

private :
    bool m_dynamicZoom;
};

#endif // SETTINGS_H
