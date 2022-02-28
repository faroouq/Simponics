/*
 * pHSensor.h
 *
 *  Created on: Aug 31, 2020
 *      Author: farouq
 */

#ifndef PHSENSOR_H_
#define PHSENSOR_H_

#include <omnetpp.h>
using namespace omnetpp;

namespace simponics{

class pHSensor:public cSimpleModule{
    private:
        double v=0.0;       //Electric and the response
        double i=0.0;       //characteristics of the sensor
        double t=0.0;
        double energy=0.0;  //Energy consumed by the system
        double ph=0.0;      //the humidity value
        double i_sleep=0.0; //current consumption during sleep
        double t_sleep=0.0; //duration of sleep

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

};
#endif /* PHSENSOR_H_ */
