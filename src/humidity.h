/*
 * humidity.h
 *
 *  Created on: Aug 30, 2020
 *      Author: farouq
 *
 *      Characteristics of the humidity sensors
 *      source of data is obtained
 *
 *
 */

#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <omnetpp.h>
using namespace omnetpp;

namespace simponics{

class humidity:public cSimpleModule{
    private:
        double v=0.0;       //Electric and the response
        double i=0.0;       //characteristics of the sensor
        double t=0.0;
        double energy=0.0;  //Energy consumed by the system
        double humd=0.0;    //the humidity value
        double i_sleep=0.0; //current consumption during sleep
        double t_sleep=0.0; //duration of sleep

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

};

#endif /* HUMIDITY_H_ */
