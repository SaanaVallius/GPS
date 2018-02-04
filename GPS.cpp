#include "GPS.h"
#include <stdio.h>

GPS::GPS(PinName tx, PinName rx) : _gps(tx, rx) {
    _gps.baud(9600);
    latitude = 0;
    longitude = 0;
    latDegrees = 0;
    longDegrees = 0;
    latDecimalMinutes = 0;
    longDecimalMinutes = 0; 
}
int GPS::sample() {
    float time;
    int lock;
    
    while(1){
        getLine();
        
        //Parsing GPS input data for GPGGA sentences
        if(sscanf(msg, "GPGGA,%f,%f,%c,%f,%c,%d",&time, &latitude, &ns, &longitude, &ew, &lock) >=1) {
            if(!lock) {
                latitude = 0;
                longitude = 0;
                return 0;
            } else {
                //Raw data is processed to get it to the desired format: 12 34.45689... where minutes are separated from degrees
                latDegrees = floor(latitude/100);
                latDecimalMinutes = latitude - 100*latDegrees;
                longDegrees = floor(longitude/100);
                longDecimalMinutes = longitude - 100*longDegrees; 
                return 1;
            }
         }
    }
}

void GPS::getLine() {
    //When there's input
    while(_gps.getc() != '$');
    
    //While
    for(int i=0; i<256; i++) {
        msg[i] = _gps.getc();
        if(msg[i] == '\r') {
            msg[i] = 0;
            return;
        }
    }
    error("overflowed message limit");
}

char * GPS::getOriginalDataStr(){
    getLine();
    return msg;
}

char * GPS::SMS(){
    //char space[] = "%%20";
    //("Latitude: %f %c\n\rLongitude: %f %c\n\r",gps.latitude,gps.ns,gps.longitude,gps.ew);
    sprintf(sms, "\n\rhttps://www.google.fi/search?q=%d+%f,+%d+%f\n\r",latDegrees, latDecimalMinutes, longDegrees, longDecimalMinutes);
    
    return sms;
}

double GPS::getLatitude(){
    return latitude;
}
    
double GPS::getLongitude(){
    return longitude;
}
