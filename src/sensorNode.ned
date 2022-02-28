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

package simponics;

//
// Sensor node simulates 802.15.4 Wireless device
//
simple sensorNode
{
    parameters:
        int nSensors = 4;							//Number of sensor nodes to connect to the node
        int nActuators = 1;							//Number of actuators
        int nPorts = 4;								//Number of nodes the sensor should be connected to
        
        bool isAggregate=false;						//if data aggregation is enabled

        double I_tx = 32.0e-3;						//Transmission of current
        double I_rx = 25.5e-3;						//Reception current consumption
        double V_trx = 3.3;							//Transceivers voltage
        double rate = 250e+3;						//Transmission rate 
        double pktSize = 1500; 						//Packet size in bytes

        double sampleRate = 1/60;					//number of samples per second

		int battery=3;								//number of AA size batteries
		
		double mu=2.0;								//inter-arrival rate
		
		
		
		//*****************************Do not touch*****************************//
		double voltage=1.7*battery;					//Voltage of battery AA
		double current=(2750e-3)*(1*60*60)*battery;	//Current
		double energy=voltage*current/battery;		//Energy contained in the battery
        @display("i=misc/node");


    gates:
        inout sensor[nSensors];
        inout actuator[nActuators];
        inout port[nPorts];							//for communication with other sensor nodes
        inout bsPort;
        inout powerPlug;
}
