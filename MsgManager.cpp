#include "MsgManager.h"

MsgManager* MsgManager::msgManager = NULL;
MsgManager::MsgManager(QObject *parent) :
    QObject(parent)
{

}

MsgManager *MsgManager::instance()
{
    if ( msgManager == NULL)
    {
        QMutex mt;
        mt.lock();
        if ( msgManager == NULL )
        {
            msgManager = new MsgManager;
        }
        mt.unlock();
    }

    return msgManager;
}

bool MsgManager::registerSignal(const QString topic,
                                const QObject *obj,
                                const char* signal,
                                Qt::ConnectionType type)
{
    // 注册信号
    if ( m_mapSignal.contains(topic) )
    {   // 存在则尾插
        m_mapSignal[topic].push_back({obj, signal});
    }
    else
    {   // 不存在则新增
        m_mapSignal.insert(topic, {{obj, signal}});
    }


    // 建立连接
    if ( m_mapSlot.contains(topic) )
    {
        for (auto stObj: m_mapSlot.value(topic))
        {
            connect(obj, signal, stObj.obj, stObj.sigSlot, type);
        }
    }
}

bool MsgManager::registerSlot(const QString topic,
                              const QObject *obj,
                              const char* slot,
                              Qt::ConnectionType type)
{
    // 注册槽
    if ( m_mapSlot.contains(topic) )
    {   // 存在则尾插
        m_mapSlot[topic].push_back({obj, slot});
    }
    else
    {   // 不存在则新增
        m_mapSlot.insert(topic, {{obj, slot}});
    }


    // 建立连接
    if ( m_mapSignal.contains(topic) )
    {
        for (auto stObj: m_mapSignal.value(topic))
        {
            connect(stObj.obj, stObj.sigSlot, obj, slot, type);
        }
    }
}
