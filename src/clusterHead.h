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

#ifndef __SIMPONICS_SINK_H
#define __SIMPONICS_SINK_H

#include <omnetpp.h>


using namespace std;
using namespace omnetpp;

namespace simponics {

/**
 * Message sink; see NED file for more info.
 */
class clusterHead : public cSimpleModule
{
  private:
    //****************For users************************
    int children=2;                 //number of children in the cluster

    double dt=3600.0;               //after what time do you want to record data?


    //*******************Don't Touch*******************
    //statistics
    cOutVector energyConsumption;
    cDoubleHistogram latencyHis;

    double i_tx = 0.0;              //Transmission of current
    double i_rx = 0.0;              //Reception current consumption
    double v_trx = 0.0;             //Transceiver voltage
    double tx_rate = 0.0;           //Transmission rate
    double pktSize = 0.0;           //Packet size in bytes


    double energy=0.0;              //Energy of the battery
    double int_energy=0.0;          //Initial energy of the battery


    int myID=0;                     //Index of the nodes



    int nNodes=0;                   //Number of nodes in the network
    int trackSensors;               //Number of sensors recorded
    int nSensors=0;                 //Number of type of sensors in the network
    int sensorData[10];             //list of variables
    double sensorDataMean[10]={};   //Sensor data collected
    double sensorDataStdev[10]={};  //Standard deviation of sensor node data

    bool nodeServiced[100]={};       //we use it to know which node we are waiting for

    double t_int=0.0;               //interval between current time and the time data is received


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    void clearServiced();                           //Reinitialize variables for next aggregation
    int countServiced();                            //counts the number of serviced nodes an return it
    int insertSensor(const char *sensorName);       //Adds a sensor to the list
    int findSensors(const char *sensorName);        //search list for the sensor, returns -1 if not found
    double min (double x, double y);                //return minimum of two numbers
    int morph(const char *sensorName);              //converts string to integer equvalent, I am tired of strings :-(
};

}; // namespace

#endif
