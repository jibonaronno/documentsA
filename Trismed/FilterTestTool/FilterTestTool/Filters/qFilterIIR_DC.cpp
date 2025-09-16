#include "qFilterIIR_DC.h"

// Y = Xn - Xn-1 + 0.99939*Yn-1
const double coeff = 0.99939;

qFilterIIR_DC::qFilterIIR_DC() :
    qAbstractFilter(0)
{
    privInit();
}

void qFilterIIR_DC::InitLead(int lead)
{
    x[lead][0] = x[lead][1] = 0;
    y[lead][0] = y[lead][1] = 0;
}

void qFilterIIR_DC::privInit() {
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
}

int32_t qFilterIIR_DC::privFilter(int32_t sample, int lead) {
    x[lead][1] = x[lead][0];
    x[lead][0] = sample;
    y[lead][1] = y[lead][0];
    y[lead][0] = x[lead][0] - x[lead][1] + coeff*y[lead][1];
    return y[lead][0];
}
