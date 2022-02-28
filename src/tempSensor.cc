

#include "tempSensor.h"
#include "sensoryMsg_m.h"

namespace simponics{

    Define_Module(tempSensor);
    void tempSensor::initialize(){
        r1=getAncestorPar("R");                                 //get the value of the resistor in parallel with the thermistor
        v=getAncestorPar("v");
        t=getAncestorPar("t");
    }

    void tempSensor::handleMessage(cMessage *msg)
    {
        if(strcmp(msg->getName(),"temp?")==0){                  //if request for temperature is received
            send(msg,"envPort$o");                              //sensing the environment
            bubble("Sensing Env");

        }else if(strcmp(msg->getName(),"temp")==0){             //if this is a temperature result
            sensoryMsg *resp = dynamic_cast <sensoryMsg*> (msg);


            this->temp=resp->getDataValue(0);                   //Get the temperature sensed

            double r2=71829.88*exp(-0.0365*this->temp);         //get the resistance due to temperature
            r2=r2+r1;
            energy=-v*v/r2*t;                                   //power consumed

            resp->setName("temp?");                             //getting ready to send the results
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

}; //namespace
