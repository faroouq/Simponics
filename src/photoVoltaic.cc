/*
 * photoVoltaic.cc
 *
 *  Created on: Sep 1, 2020
 *      Author: farouq
 */


#include "photoVoltaic.h"
#include "sensoryMsg_m.h"

namespace simponics{

Define_Module(photoVoltaic);


/*******************************************************************************************
 *Initialization of simulation
 *******************************************************************************************/
void photoVoltaic::initialize()
{
    this->v=getAncestorPar("V");
    this->i=getAncestorPar("I");
    this->t=getAncestorPar("T");

    this->l=getAncestorPar("L");
    this->w=getAncestorPar("W");

    cMessage *msg = new cMessage("photo?");                     //decide when to sense the environment
    scheduleAt(this->t,msg);                                    //get the next time to calculate energy generated
}



/*******************************************************************************************
 *When message is received, it is processed here.
 *******************************************************************************************/
void photoVoltaic::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"photo?")==0){                 //if request for light intensity of the environment
        send(msg,"envPort$o");                              //sensing the environment
        bubble("Sensing Env");

    }else if(strcmp(msg->getName(),"photo")==0){            //if this is a pH result
        sensoryMsg *resp = dynamic_cast <sensoryMsg*> (msg);


        this->irradiance=resp->getDataValue(0);             //Get the photo sensed (W/m^2)
        double total_energy=(irradiance/(l*w))*t;           //to get the total energy (W), multiply with time to get energy
        energy=i*v*t;                                       //power consumed
        energy = this->min(energy, total_energy);           //the solar panel has a bounded power generation
        if(energy<0) energy=0;                              //no negative energy


        resp->setName("photo?");                            //getting ready to send the results
        resp->setDataName(resp->getEntries(), "Energy");
        resp->setDataValue(resp->getEntries(), energy);
        resp->setEntries(resp->getEntries()+1);             //we are adding another entry

        EV<<"Energy Generated "<<energy<<endl;
        send(msg, "powerPlug$o");                           //sending message to Sensor node
        bubble("Energy Generated");


        cMessage *msg = new cMessage("photo?");             //decide when to sense the environment
        double nxtTime = this->t+simTime().dbl();           //Next energy update
        EV<<"Next energy update at "<<nxtTime<<endl;        //DEBUG
        scheduleAt(nxtTime,msg);                            //get the next time to calculate energy generated

    }else{
        bubble("Unknown Message");
        delete(msg);
    }
}



/*******************************************************************************************
 *Function returns the minimum of two numbers
 *******************************************************************************************/
double photoVoltaic::min (double x, double y){
    if(x<y)
        return x;
    else
        return y;
}
};





