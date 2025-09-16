#include "qECG_RAW_File.h"
#include <QFile>

qECG_RAW_File::qECG_RAW_File(QObject *parent) : QObject(parent)
{

}

void qECG_RAW_File::Load(QString filename)
{
    uint32_t samples;
    QFile file(filename);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    int16_t data;
    if(file.isOpen()) {
        file.read(reinterpret_cast<char*>(&m_channelCount), sizeof(int32_t));
        file.read(reinterpret_cast<char*>(&samples), sizeof(uint32_t));
        m_leads.clear();
        for(int32_t i=0; i<m_channelCount; i++) {
            m_leads << QVector<int32_t>();
        }
        for(uint32_t samp=0; samp < samples; samp++) {
            for(int32_t i=0; i<m_channelCount; i++) {
                file.read(reinterpret_cast<char*>(&data), sizeof(uint16_t));
                m_leads[i] << static_cast<int32_t>(data);
            }
        }
    }
}

QVector<int32_t> qECG_RAW_File::GetChannel(int lead)
{
    return m_leads[lead];
}
