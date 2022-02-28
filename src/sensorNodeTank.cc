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

#include "sensorNodeTank.h"
#include "sensoryMsg_m.h"

namespace simponics {

Define_Module(sensorNodeTank);


/*******************************************************************************************
 *Initialization of simulation
 *******************************************************************************************/
void sensorNodeTank::initialize()
{
    sensors[0]="ph?";                                         //Telling the MCU the sensors connected
    sensors[1]="ec?";


    i_tx = getAncestorPar("I_tx").doubleValue();                //Transmission of current
    i_rx = getAncestorPar("I_rx").doubleValue();                //Reception current consumption
    v_trx= getAncestorPar("V_trx").doubleValue();               //Transceiver voltage
    tx_rate = getAncestorPar("rate").doubleValue();             //Transmission rate
    pktSize = getAncestorPar("pktSize").doubleValue();          //Packet size in bytes

    sampleRate = getAncestorPar("sampleRate").doubleValue();    //number of samples per second
    energy = getAncestorPar("energy").doubleValue();            //voltage of battery
    int_energy = energy;                                        //save the maximum capacity of the battery

    energyConsumption.setName("Residual Energy");               //Energy remaining in the battery
    myID=this->getId();                                         //Index of node

    EV<<"Initialization "<<endl<<"myID: "<<myID<<endl;          //Show nodes ID

    cMessage *msg = new cMessage("Sense");                      //decide when to sense the environment
    meanArrival=getAncestorPar("mu");                           //Get the mean arrival rate for packets. Simulates starting of the nodes
    scheduleAt(exponential(meanArrival),msg);

    this->energyConsumption.record(energy);                     //record energy consumption
}



/*******************************************************************************************
 *When message is received, it is processed here.
 *******************************************************************************************/
void sensorNodeTank::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "Sense")==0){ //****************It is sensing time************
        bubble("Sensing Time");

        sensorCnt=0;
        for(int i=0; i<this->nSensors; i++){
            cMessage *cpyMsg = new cMessage(this->sensors[i]);          //create query, then
            send(cpyMsg, "sensor$o", i);                                //send query to first sensor
        }


        EV<<"See you at "<<simTime().dbl()+(1.0/sampleRate)<<endl;
        scheduleAt(simTime().dbl()+(1.0/sampleRate), msg);



    }else if(strcmp(msg->getName(), "photo?")==0){  //**************Source energy**************

        sensoryMsg *resp=dynamic_cast <sensoryMsg *> (msg);
        this->energy += resp->getDataValue(1);                          //energy charges battery
        this->energy = this->min(this->energy, this->int_energy);


        EV<<"Battery charging (Solar)"<<this->energy<<endl;                    //New amount of charge
        bubble("Charging");



    }else if(strcmp(msg->getName(), "hydro?")==0){  //**************Source energy**************

        sensoryMsg *resp=dynamic_cast <sensoryMsg *> (msg);
        this->energy += resp->getDataValue(1);                          //energy charges battery
        this->energy = this->min(this->energy, this->int_energy);


        EV<<"Battery charging (Hydro)"<<this->energy<<endl;                    //New amount of charge
        bubble("Charging");



    }else if(strcmp(msg->getName(), "Data")==0){   //*************Is data going to the BS?***********
        double tx_time=this->pktSize*8/this->tx_rate;                   //then forward it towards the BS transmission time
        this->energy-=i_rx*v_trx*tx_time;                               //energy consumption due to reception of packet
        this->energy-=this->i_tx*this->v_trx*tx_time;                   //Energy consumption due to transmission

        double whenToSend = simTime().dbl()+tx_time;                    //When to send data
        EV<<"To sent packet to BS at "<<whenToSend<<endl;               //DEBUG
        sendDelayed(msg, tx_time, "bsPort$o");                          //tx_time is the duration of wait
        bubble("Forwarding Packet");

    }else{                                      //***********Your sensor node logic here**********
                                                                         //lets check if it is a sensor result
        sensoryMsg *resp=dynamic_cast <sensoryMsg *> (msg);
        bool foundSensor=false;

        for(int i=0; i<this->nSensors; i++){
            if (opp_strcmp(resp->getName(),this->sensors[i])==0){       //Lets check if the sensors exists
                foundSensor=true;

                for(int j=0; j<resp->getEntries(); j++){                //for each characteristic for the sensor
                    if(strcmp(resp->getDataName(j), "Energy")==0){      //data is energy consumption of sensor
                        this->energy+=resp->getDataValue(j);            //then add it to the sensor.
                    }else{
                        char *mySensor=new char [5];
                        strcpy(mySensor, resp->getDataName(j));         //for some reason I can't copy directly ;-(
                        this->sensorData[this->sensorCnt]=mySensor;
                        this->sensorDataValue[this->sensorCnt]=resp->getDataValue(j);

                        this->sensorCnt++;                              //count sensor recorded
                    }
                }

                delete(resp);                                           //The packet has exceed its use
                break;                                                  //break we have already treat the sensor
            }
        }


        if (this->sensorCnt==this->nSensors){                           //if we get data from all the sensor
            sensoryMsg *data=new sensoryMsg("Data");
            data->setEntries(this->sensorCnt);                          //No entries at
            data->setSource(this->myID);                                //source


            for(int i=0; i<this->sensorCnt; i++){
                data->setDataName(i, this->sensorData[i]);
                data->setDataValue(i, this->sensorDataValue[i]);
            }


            double tx_time=this->pktSize*8/this->tx_rate;               //transmission time
            this->energy-=this->i_tx*this->v_trx*tx_time;

            double whenToSend = simTime().dbl()+tx_time;                //When to send data
            data->setTxTime(simTime().dbl());                           //record transmission time
            EV<<"To sent packet to BS at "<<whenToSend<<endl;           //DEBUG
            sendDelayed(data, tx_time, "bsPort$o");                     //tx_time is the duration of wait


            this->sensorCnt=0;                                          //clear count for next round; it also stop you from sending more than once
        }

    }



    if(this->dt<=(simTime().dbl()-this->t_int)){         //*******************RECORD NODES VITAL*******************
        this->energyConsumption.record(energy);
        this->t_int=simTime().dbl();
    }
}


/*******************************************************************************************
 *Finishing the simulation
 *******************************************************************************************/
void sensorNodeTank::finish()
{
    energyConsumption.record(energy);

}


/*******************************************************************************************
 *Function returns maximum values
 *******************************************************************************************/
double sensorNodeTank::min (double x, double y){
    if(x<y)
        return x;
    else
        return y;
}

}; // namespace
