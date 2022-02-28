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

package simponics.simulations;



import simponics.baseStation;
import simponics.ecSensor;
import simponics.humidity;
import simponics.pHSensor;
import simponics.photoVoltaic;
import simponics.tempSensor;
import simponics.workStation;
import simponics.hydroponic;
import simponics.sensorNode;
import simponics.sensorNodeTank;
import simponics.workStation;


network Smart_multi_hop_4
{
    @display("bgb=1612.16,1219.68");
    submodules:
        hydroponic: hydroponic {
            @display("p=1015.52,362.56;b=46,46");
        }


        tempSensor: tempSensor {
            @display("p=1464.3201,830.72003");
        }
        sensorNode: sensorNode {
            @display("p=1367.52,975.04004");
        }
        humidity: humidity {
            @display("p=1202.08,830.72003");
        }
        pHSensor1: pHSensor {
            @display("p=871.2,830.72003");
        }
        ecSensor1: ecSensor {
            @display("p=661.76,762.08");
        }
        workStation: workStation {
            @display("p=191.84,1128.16");
        }
        baseStation: baseStation {
            @display("p=480.48,1068.3201");
        }
        sensorNodeTank: sensorNodeTank {
            @display("p=663.52,906.4");
        }
        sensorNode1: sensorNode {
            @display("p=350.24,767.36");
        }
        tempSensor1: tempSensor {
            @display("p=415.36002,554.4");
        }
        humidity1: humidity {
            @display("p=494.56,693.44");
        }
        sensorNode2: sensorNode {
            @display("p=191.84,397.76");
        }
        tempSensor2: tempSensor {
            @display("p=420.64,154.88");
        }
        humidity2: humidity {
            @display("p=404.80002,353.76");
        }
    connections allowunconnected:
        //----Sensors connecting to the environment----
        tempSensor.envPort <--> hydroponic.envPorts[0];
        tempSensor1.envPort <--> hydroponic.envPorts[1];
        tempSensor2.envPort <--> hydroponic.envPorts[2];
        humidity.envPort <--> hydroponic.envPorts[3];
        humidity1.envPort <--> hydroponic.envPorts[4];
        humidity2.envPort <--> hydroponic.envPorts[5];
        ecSensor1.envPort <--> hydroponic.envPorts[6];
        pHSensor1.envPort <--> hydroponic.envPorts[7];


        //------Sensors connecting to the Nodes------
        tempSensor.mcuPort <--> sensorNode.sensor[0];
        tempSensor1.mcuPort <--> sensorNode1.sensor[0];
        tempSensor2.mcuPort <--> sensorNode2.sensor[0];



        humidity.mcuPort <--> sensorNode.sensor[1];
        humidity1.mcuPort <--> sensorNode1.sensor[1];
        humidity2.mcuPort <--> sensorNode2.sensor[1];



        pHSensor1.mcuPort <--> sensorNodeTank.sensor[0];
        ecSensor1.mcuPort <--> sensorNodeTank.sensor[1];




        //----------Sensor nodes Networks-----------
        sensorNode2.bsPort <--> sensorNode1.port[0];
        sensorNode1.bsPort <--> sensorNodeTank.port[0];
        sensorNode.bsPort <--> baseStation.port[1];


        sensorNodeTank.bsPort <--> baseStation.port[0];


        workStation.port <--> baseStation.wsPort;
}
