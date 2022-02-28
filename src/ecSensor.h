/*
 * ecSensor.h
 *
 *  Created on: Sep 1, 2020
 *      Author: farouq
 */

#ifndef ECSENSOR_H_
#define ECSENSOR_H_


#include <omnetpp.h>
using namespace omnetpp;

namespace simponics{

class ecSensor:public cSimpleModule{
    private:
        double v=0.0;       //Electric and the response
        double i=0.0;       //characteristics of the sensor
        double t=0.0;
        double energy=0.0;  //Energy consumed by the system
        double ec=0.0;      //the electric conductivity value
        double t_sleep=0.0; //Time the system was sleeping
        double i_sleep=0.0; //current consumed during sleeping

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

};


#endif /* ECSENSOR_H_ */
