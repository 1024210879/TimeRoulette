#ifndef DATIO_H
#define DATIO_H

#include <QObject>
#include <vector>
#include <string>

class datIO : public QObject
{
    Q_OBJECT
public:
    explicit datIO(QObject *parent = nullptr);

    static std::vector<uchar> readDat();
    static void writeDat(std::vector<uchar> v);

signals:

public slots:
};

#endif // DATIO_H
