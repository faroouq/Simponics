/*
 * humidity.cc
 *
 *  Created on: Aug 30, 2020
 *      Author: farouq
 */



#include "humidity.h"
#include "sensoryMsg_m.h"

namespace simponics{

Define_Module(humidity);

/*******************************************************************************************
 *Initialization of simulation
 *******************************************************************************************/
void humidity::initialize()
{
    this->v=getAncestorPar("V");
    this->i=getAncestorPar("I");
    this->t=getAncestorPar("T");
    this->i_sleep=getAncestorPar("I_sleep");
}

/*******************************************************************************************
 *When message is received, it is processed here.
 *******************************************************************************************/
void humidity::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"humd?")==0){                  //if request for temperature is received
        send(msg,"envPort$o");                              //sensing the environment
        bubble("Sensing Env");

    }else if(strcmp(msg->getName(),"humd")==0){             //if this is a temperature result
        sensoryMsg *resp = dynamic_cast <sensoryMsg*> (msg);


        this->humd=resp->getDataValue(0);                   //Get the temperature sensed

        energy=-i*v*t;                                      //power consumed
        double t_slept=simTime().dbl();                     //get current simulation time
        energy -= i_sleep*v*(t_slept-t_sleep);              //energy consumed during sleeping
        this->t_sleep=simTime().dbl()+this->t;              //update time until next sleep

        resp->setName("humd?");                             //getting ready to send the results
        resp->setDataName(resp->getEntries(), "Energy");
        resp->setDataValue(resp->getEntries(), energy);
        resp->setEntries(resp->getEntries()+1);             //we are adding another entry

        EV<<"Sending temperature at "<<simTime().dbl()+t;
        sendDelayed(msg, t, "mcuPort$o");                   //sending message to Sensor node
        bubble("Forwarding to Sensor node");

    }else{
        bubble("Unknown Message");
        delete(msg);
    }
}
};
