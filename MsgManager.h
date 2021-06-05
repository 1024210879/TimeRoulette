#ifndef MSGMANAGER_H
#define MSGMANAGER_H

#include <QObject>
#include <QMutex>
#include <QHash>
#include <QList>

class MsgManager : public QObject
{
    Q_OBJECT


public:
    explicit MsgManager(QObject *parent = nullptr);


public:
    /**
     * @brief 获取 MsgManager 单例
     * @return
     */
    static MsgManager *instance();

    /**
     * @brief 注册信号
     * @param topic
     * @param obj
     * @param signal
     * @return
     */
    bool registerSignal(const QString topic,
                        const QObject* obj,
                        const char* signal,
                        Qt::ConnectionType type = Qt::QueuedConnection);

    /**
     * @brief 注册槽
     * @param topic
     * @param obj
     * @param slot
     * @return
     */
    bool registerSlot(const QString topic,
                      const QObject* obj,
                      const char* slot,
                      Qt::ConnectionType type = Qt::QueuedConnection);


private:
    static MsgManager* msgManager;

    typedef struct {
        const QObject* obj;
        const char* sigSlot;
    }StObj;

    QHash<QString, QList<StObj>> m_mapSignal;
    QHash<QString, QList<StObj>> m_mapSlot;
};

#endif // MSGMANAGER_H
