#include "mbed.h"

class GPS {
public:
    GPS(PinName tx, PinName rx);
    int sample();
    char * getOriginalDataStr();
    char * SMS();
    double getLatitude();
    double getLongitude();
private:
    float trunc ( float v);
    void getLine();
    Serial _gps;
    char msg[256];
    char sms[160];
    char ns;
    char ew;
    float longitude;
    float latitude;
    int latDegrees;
    int longDegrees;
    float latDecimalMinutes;
    float longDecimalMinutes; 
};
