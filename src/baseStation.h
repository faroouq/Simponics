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
//#include <string.h>
//#include <cstring>

using namespace std;
using namespace omnetpp;

namespace simponics {

/**
 * Message sink; see NED file for more info.
 */
class baseStation : public cSimpleModule
{
  private:
    //****************For users************************
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


    double t_int=0.0;               //interval between current time and the time data is received

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    double min (double x, double y);
};

}; // namespace

#endif
