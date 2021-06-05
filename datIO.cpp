#include "datIO.h"

datIO::datIO(QObject *parent) : QObject(parent)
{

}

std::vector<uchar> datIO::readDat()
{
    std::vector<uchar> v;
    v.resize(9);
    FILE* fp = fopen("data.bin", "r");
    fread(v.data(), 1, 9, fp);
    fclose(fp);
    return v;
}

void datIO::writeDat(std::vector<uchar> v)
{
    FILE* fp = fopen("data.bin", "w");

    if (fp == NULL)
    {
        return;
    }

    fwrite((const char*)v.data(), 1, 9, fp);
    fclose(fp);
}
