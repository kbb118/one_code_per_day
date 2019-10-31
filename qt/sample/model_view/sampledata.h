#ifndef SAMPLEDATA_H
#define SAMPLEDATA_H

#include <QMetaType>
#include <QString>

class SampleData
{
public:
    SampleData();
    SampleData(const SampleData &obj);
    QString data();
    void setData(const QString &data);

private:
    QString m_data;
};
Q_DECLARE_METATYPE(SampleData)

#endif //SAMPLEDATA_H
