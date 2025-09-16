#ifndef QACQ_ADS1298_H
#define QACQ_ADS1298_H

#include <stdint.h>
#include <QObject>
#include <QIODevice>
#include <QList>
#include "queues/fastqueue.h"

typedef enum  {
    AMP_COMMAND_START = 1,                  /**< Command that starts ECG signal transfer */
    AMP_COMMAND_STOP,                       /**< Command that stops any signal transfer */
    AMP_COMMAND_CALIBRATION,                /**< Command that initiates Calibration signal transfer */
    AMP_COMMAND_AN_ON,                      /**< Command to switch the hardware HPF from 0.05Hz to 391Hz for faster recovery time*/
    AMP_COMMAND_AN_OFF,                     /**< Command to switch back the hardware HPF from 391Hz to 0.05Hz */
    AMP_COMMAND_READ_CAL_DATA,
    AMP_COMMAND_GET_BOARD_VERSION,          /**< Command to request the baseboard hardware version */
    AMP_COMMAND_CHECK_CABLE_CONNECTED,      /**< Command to optionally enable INT while cable is disconnected (only Trismed patient cable) */
    AMP_COMMAND_DONT_CHECK_CABLE_CONNECTED, /**< Command to optionally disable patient cable status checking */
    AMP_COMMAND_ENABLE_HW_LEADOFF,          /**< Command to enable the hardware leadoff detection */
    AMP_COMMAND_DISABLE_HW_LEADOFF,         /**< Command to disable the hardware leadoff detection */
    AMP_COMMAND_INT_PULSE,                  /**< Command to enable INT shape as pulse */
    AMP_COMMAND_INT_CLOCK,                  /**< Command to enable INT shape as clock (one INT trigger performs several INT pulses) */
    AMP_COMMAND_FW_UPD = 0xc0               /**< Command to upgrade firmware (!!! NEVER USED BY CARDIPIA) */
} AMP_COMMANDS;

typedef struct {
  uint32_t Status;
  int32_t Leads[8];
} ADS1298_Frame;

#pragma pack(push, 1)
typedef struct {
    uint8_t sync;
    ADS1298_Frame frame;
} Raw_Tx_t;
#pragma pack(pop)

class qAcq_Ads1298 : public QObject
{
    Q_OBJECT

public:
    qAcq_Ads1298(QObject *parent = 0);
    ~qAcq_Ads1298();
    void SendCalibration(void);
    void SendSignal(void);
    void Stop(void);

    void RegisterQueue(FastQueue<Raw_Tx_t> * queue);
    void RemoveQueue(FastQueue<Raw_Tx_t> * queue);

signals:
    void sNewSamples(void);

private:
    QIODevice * device;
    QList<FastQueue<Raw_Tx_t>*> clientsQueue;

    AMP_COMMANDS currentCommand;
    FastQueue<char> *oldData;
    bool synchronized;

private slots:
    void onRxData();
};

#endif // QACQ_ADS1298_H
