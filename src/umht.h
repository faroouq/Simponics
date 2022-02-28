/*
 * photoVoltaic.h
 *
 *  Created on: Sep 1, 2020
 *      Author: farouq
 */

#ifndef PHOTOVOLTAIC_H_
#define PHOTOVOLTAIC_H_


#include <omnetpp.h>
using namespace omnetpp;

namespace simponics{

class photoVoltaic:public cSimpleModule{
    private:
        double v=0.0;           //Electric and the response
        double i=0.0;           //characteristics of the sensor
        double t=0.0;
        double energy=0.0;      //Energy consumed by the system


    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        double min (double x, double y);
};

};


#endif /* PHOTOVOLTAIC_H_ */
