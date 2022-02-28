/*
 * tempSensor.h
 *
 *  Created on: Aug 27, 2020
 *      Author: farouq
 */

#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include <omnetpp.h>
//#include <string.h>
//#include <cstdio>
//#include <cstring>

using namespace std;
using namespace omnetpp;

namespace simponics{

/**
 * Thermistor 10k NTC
 */


class tempSensor: public cSimpleModule{
    private:
        double r1=0.0;          //Resistor in the potential divider
        double temp=0.0;        //temperature measured
        double v=0.0;           //voltage
        double t=0.0;           //time
        double energy=0.0;      //energy consumed

    protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
};
};
#endif /* TEMPSENSOR_H_ */
