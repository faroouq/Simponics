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

#include "baseStation.h"
#include "sensoryMsg_m.h"
#include <math.h>

namespace simponics {

Define_Module(baseStation);


/*******************************************************************************************
 *Initialization of simulation
 *******************************************************************************************/
void baseStation::initialize()
{

    i_tx = getAncestorPar("I_tx").doubleValue();                //Transmission of current
    i_rx = getAncestorPar("I_rx").doubleValue();                //Reception current consumption
    v_trx= getAncestorPar("V_trx").doubleValue();               //Transceiver voltage
    tx_rate = getAncestorPar("rate").doubleValue();             //Transmission rate
    pktSize = getAncestorPar("pktSize").doubleValue();          //Packet size in bytes


    energy = getAncestorPar("energy").doubleValue();            //voltage of battery
    int_energy = energy;                                        //save the maximum capacity of the battery

    energyConsumption.setName("Residual Energy");               //Energy remaining in the battery
    latencyHis.setName("BS Latency");                           //Latency
    myID=this->getId();                                         //Index of node

    EV<<"Initialization"<<endl<<"myID:"<<myID<<endl;            //Show nodes ID

    this->energyConsumption.record(energy);                     //record energy consumption
}



/*******************************************************************************************
 *When message is received, it is processed here.
 *******************************************************************************************/
void baseStation::handleMessage(cMessage *msg)
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
        this->energy-=this->i_tx*this->v_trx*tx_time;                   //energy consumption due to transmission

        sensoryMsg *resp=dynamic_cast <sensoryMsg *> (msg);
        double whenToSend = simTime().dbl()+tx_time;                    //When to send data
        latencyHis.collect((simTime().dbl()-resp->getTxTime()));          //get latency of the transmission

        EV<<"To sent packet to BS at "<<whenToSend<<endl;               //DEBUG
        sendDelayed(resp, tx_time, "wsPort$o");                         //tx_time is the duration of wait
        bubble("Forwarding Packet");


    }else{                                          //***********YAn unknown Message**********
       bubble("Unknown");
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
void baseStation::finish()
{
    energyConsumption.record(energy);

    EV<<"BS:"<<endl;
    EV<<"Mean = "<<latencyHis.getMean()<<endl;
    EV<<"Min = "<<latencyHis.getMin()<<endl;
    EV<<"Max = "<<latencyHis.getMax()<<endl;
    EV<<"Stdev = "<<latencyHis.getStddev()<<endl;

}


/*******************************************************************************************
 *Function returns minimum values
 *******************************************************************************************/
double baseStation::min (double x, double y){
    if(x<y)
        return x;
    else
        return y;
}

}; // namespace
