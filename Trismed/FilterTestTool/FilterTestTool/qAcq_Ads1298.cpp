#include "qAcq_Ads1298.h"
#include <QtExtSerialPort/qextserialport.h>

#define AMP_DEVICE_NAME "/dev/ttyO1"

#define AMP_SYNCHRONIZE_BYTE 0x55u

qAcq_Ads1298::qAcq_Ads1298(QObject *parent) :
    QObject(parent)
{
    oldData = new FastQueue<char>(100);
    synchronized = false;

    currentCommand = AMP_COMMAND_STOP;
    PortSettings portsettings;
    portsettings.BaudRate       = BAUD230400;
    portsettings.FlowControl    = FLOW_OFF;
    portsettings.DataBits       = DATA_8;
    portsettings.StopBits       = STOP_1;
    portsettings.Parity         = PAR_NONE;
    device = new QextSerialPort(QString(AMP_DEVICE_NAME), portsettings, QextSerialPort::EventDriven , this);
    connect (device, SIGNAL(readyRead()), this, SLOT(onRxData()));
    if (device->open(QIODevice::ReadWrite)) {
        qDebug()  << "Openned port:" << ((QextSerialPort*)device)->portName();
    } else {
        qCritical() << "Error opening the port";
    }
}

qAcq_Ads1298::~qAcq_Ads1298()
{
    Stop();
    delete device;
    delete oldData;
}

void qAcq_Ads1298::onRxData()
{
    Raw_Tx_t sample;

    int idx = 0;
    bool hasNewSamples = false;
    int oldDataCount = oldData->size();
    int _count = device->bytesAvailable();
    char *buffer = new char[oldDataCount + _count];

    if(oldDataCount) {
        oldData->popAll(buffer);
    }
    device->read(&buffer[oldDataCount],_count);
    _count += oldDataCount;

    switch(currentCommand) {
    case AMP_COMMAND_START:
    case AMP_COMMAND_CALIBRATION:
        while(idx < _count) {
            do {
                if(synchronized) break;
                if(buffer[idx]==AMP_SYNCHRONIZE_BYTE) {
                    synchronized = true;
                    break;
                } else {
                    idx++;
                    qDebug() << "Lost bytes " << idx;
                }
            } while (idx < _count);
            if((_count - idx) < static_cast<int>(sizeof(Raw_Tx_t))) {
                if(_count - idx)
                    oldData->push(&buffer[idx], _count - idx);
                break;
            }
            memmove((char*)&sample, &buffer[idx], sizeof(Raw_Tx_t));
            idx+=sizeof(Raw_Tx_t);
            hasNewSamples = true;
            for(auto item: clientsQueue) {
                item->lock();
                item->push(&sample, 1);
                item->unlock();
            }
            synchronized = false;
        }
        if(hasNewSamples) {
            emit sNewSamples();
        }
        break;
    }
}

void qAcq_Ads1298::SendCalibration()
{
    const char data = AMP_COMMAND_CALIBRATION;
    currentCommand = AMP_COMMAND_CALIBRATION;
    oldData->clear();
    device->write(&data, 1);
}

void qAcq_Ads1298::SendSignal()
{
    const char data = AMP_COMMAND_START;
    currentCommand = AMP_COMMAND_START;
    oldData->clear();
    device->write(&data, 1);
}

void qAcq_Ads1298::Stop()
{
    const char data = AMP_COMMAND_STOP;
    currentCommand = AMP_COMMAND_STOP;
    device->write(&data, 1);
}

void qAcq_Ads1298::RegisterQueue(FastQueue<Raw_Tx_t> *queue)
{
    if(!clientsQueue.contains(queue)) {
        clientsQueue.append(queue);
        qDebug() << "++" << clientsQueue.count();
    } else {
        qCritical() << "Queue already registered!!!";
    }
}

void qAcq_Ads1298::RemoveQueue(FastQueue<Raw_Tx_t> *queue)
{
    int idx=0;
    for(auto item: clientsQueue) {
        if(item == queue) {
            clientsQueue.removeAt(idx);
            qDebug() << "--" << clientsQueue.count();
        }
        idx++;
    }
}
