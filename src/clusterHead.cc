//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "clusterHead.h"
#include "sensoryMsg_m.h"

#include <array>
#include <math.h>

namespace simponics {

Define_Module(clusterHead);


/*******************************************************************************************
 *Initialization of simulation
 *******************************************************************************************/
void clusterHead::initialize()
{
    this->nSensors=getAncestorPar("nSensors");                  //Number of different type of sensors
    this->nNodes=getAncestorPar("nNodes");                       //Number of nodes in the network

    this->trackSensors=0;

    i_tx = getAncestorPar("I_tx").doubleValue();                //Transmission of current
    i_rx = getAncestorPar("I_rx").doubleValue();                //Reception current consumption
    v_trx= getAncestorPar("V_trx").doubleValue();               //Transceiver voltage
    tx_rate = getAncestorPar("rate").doubleValue();             //Transmission rate
    pktSize = getAncestorPar("pktSize").doubleValue();          //Packet size in bytes

    energy = getAncestorPar("energy").doubleValue();            //voltage of battery
    int_energy = energy;                                        //save the maximum capacity of the battery

    energyConsumption.setName("Residual Energy");               //Energy remaining in the battery
    latencyHis.setName("CH Latency");                           //Latency of network
    myID=this->getId();                                         //Index of node

    EV<<"Initialization"<<endl<<"myID:"<<myID<<endl;            //Show nodes ID


    this->energyConsumption.record(energy);                     //record energy consumption
}



/*******************************************************************************************
 *When message is received, it is processed here.
 *******************************************************************************************/
void clusterHead::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "photo?")==0){  //**************Source energy**************

        sensoryMsg *resp=dynamic_cast <sensoryMsg *> (msg);
        this->energy += resp->getDataValue(1);                          //energy charges battery
        this->energy = this->min(this->energy, this->int_energy);


        EV<<"Battery charging "<<this->energy<<endl;                    //New amount of charge
        bubble("Charging");



    }else if(strcmp(msg->getName(), "Data")==0){   //*************Is data going to the BS?***********
        double tx_time=this->pktSize*8/this->tx_rate;                   //then forward it towards the BS transmission time
        this->energy-=i_rx*v_trx*tx_time;                               //energy consumption due to reception of packet


        sensoryMsg *pkt=dynamic_cast <sensoryMsg *> (msg);             //convert message to the actual packet
        bubble("Packet received");                                      //Packet received
        EV<<"Received Packet from"<<pkt->getSource()<<endl;


        latencyHis.collect((simTime().dbl()-pkt->getTxTime()));           //Record latency


        if(this->nodeServiced[pkt->getSource()]){
            EV<<"Node is already serviced"<<endl;                       //Packet serviced

        }else{
            this->nodeServiced[pkt->getSource()]=true;                  //Marked node as received

            for(int i=0; i<=this->nSensors; i++){
                int val=strlen(pkt->getDataName(i));
                if(val>0){
                    int indx = this->findSensors(pkt->getDataName(i));

                    if(indx==-1){
                        indx=this->insertSensor(pkt->getDataName(i));   //if node does not exist then add it
                        this->sensorDataMean[indx]=0;                   //is the sensor value
                        this->sensorDataStdev[indx]=0;                  //sum of squares
                    }


                    if(indx>-1){
                        this->sensorDataMean[indx]+=pkt->getDataValue(0);           //is the sensor value
                        this->sensorDataStdev[indx]+=pow(pkt->getDataValue(0),2);   //sum of squares
                    }
                }
            }
        }


        if(this->countServiced()>=this->nNodes){                        //If nodes all sensor are serviced
            EV<<"Aggregating the data"<<endl;
            bubble("Aggregation");

            sensoryMsg *pkt = new sensoryMsg("Data");
            pkt->setSource(myID);                                       //Attach my ID to network

            for(int i=0; i<this->trackSensors;i++){
                char *myName= new char [5];
                strcpy(myName,to_string(sensorData[i]).c_str());
                pkt->setDataName(i, myName);                              //Data
                int nn=this->countServiced()-1;                             //exclude tank sensor
                int mu=sensorDataMean[i]/nn;
                pkt->setDataValue(i, mu);                                                   //Mean value
                pkt->setDataStdValue(i, sqrt(sensorDataStdev[i]/(nn-1)-mu));      //Standard Deviation
            }

            this->energy-=this->i_tx*this->v_trx*tx_time;               //Energy consumption due to transmission

            double whenToSend = simTime().dbl()+tx_time;                //When to send data
            pkt->setTxTime(simTime().dbl());                                //record transmission time

            EV<<"To sent packet to BS at "<<whenToSend<<endl;           //DEBUG
            sendDelayed(pkt, tx_time, "bsPort$o");                      //tx_time is the duration of wait
            //bubble("Forwarding Packet");

            trackSensors=0;                                             //start new aggregation
            clearServiced();                                            //reinitialize for next aggregation
            EV<<"Wait for next aggregation cycle"<<endl;
            bubble("New cycle");
        }

        delete(msg);                                                    //finished with packet



    }else{                                      //***********If the packet is not known**************
        bubble("Unknow packet");
        delete(msg);

    }



    if(this->dt<=(simTime().dbl()-this->t_int)){         //*******************RECORD NODES VITAL*******************
        this->energyConsumption.record(energy);
        this->t_int=simTime().dbl();
    }
}


/*******************************************************************************************
 *Finishing the simulation
 *******************************************************************************************/
void clusterHead::finish()
{
    energyConsumption.record(energy);

    EV<<"CH:"<<endl;
    EV<<"Mean = "<<latencyHis.getMean()<<endl;
    EV<<"Min = "<<latencyHis.getMin()<<endl;
    EV<<"Max = "<<latencyHis.getMax()<<endl;
    EV<<"Stdev = "<<latencyHis.getStddev()<<endl;
}


/*******************************************************************************************
 *Function returns maximum values
 *******************************************************************************************/
double clusterHead::min (double x, double y){
    if(x<y)
        return x;
    else
        return y;
}



/*******************************************************************************************
 *Create an integer equivalent of the character
 *******************************************************************************************/
int clusterHead::morph(const char *sensorName){
    int sensor=0;
    for(int i=0; i<strlen(sensorName); i++)
        sensor=(sensor*100)+((int)sensorName[i])%26+10;

    return sensor;
}


/*******************************************************************************************
 *Adds a sensor to the list and return the sensors index
 *******************************************************************************************/
int clusterHead::insertSensor(const char *sensorName){
    this->sensorData[this->trackSensors]=this->morph(sensorName);
    this->trackSensors+=1;
    return (this->trackSensors-1);
}


/*******************************************************************************************
 *Search list for the sensor, returns -1 if not found
 *******************************************************************************************/
int clusterHead::findSensors(const char *sensorName){
    int morphedSensor=this->morph(sensorName);
    for (int i=0; i<this->trackSensors; i++){                   //for each element
        //const char *dataName=this->sensorData[i];
        if(morphedSensor==this->sensorData[i])      //if sensor is found
            return i;                                       //return the index
    }

    return -1;                                              //else return -1
}


/*******************************************************************************************
 *Lets count the number of nodes serviced so far.
 *******************************************************************************************/
int clusterHead::countServiced(){
    int service=0;
    int arrSize=sizeof(this->nodeServiced)/sizeof(this->nodeServiced[0]);

    for (int i=0; i<arrSize; i++){
        if(this->nodeServiced[i])
            service++;
    }

    return service;
}



/*******************************************************************************************
 *Lets count the number of nodes serviced so far.
 *******************************************************************************************/
void clusterHead::clearServiced(){
    int service=0;
    int arrSize=sizeof(this->nodeServiced)/sizeof(this->nodeServiced[0]);

    for (int i=0; i<arrSize; i++){
        this->nodeServiced[i]=false;
    }
}
}; // namespace
