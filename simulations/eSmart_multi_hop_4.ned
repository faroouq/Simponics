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


network eSmart_multi_hop_4
{
    @display("bgb=6110.6245,4548.032");
    submodules:
        hydroponic: hydroponic {
            @display("p=3766.736,1264.0481;b=46,46");
        }


        tempSensor: tempSensor {
            @display("p=4389.2324,2858.4001");
        }
        sensorNode: sensorNode {
            @display("p=5386.496,3328.4482");
        }
        humidity: humidity {
            @display("p=5481.7764,2756.768");
        }
        pHSensor1: pHSensor {
            @display("p=2293.072,3264.9282");
        }
        ecSensor1: ecSensor {
            @display("p=1746.8,3150.592");
        }
        workStation: workStation {
            @display("p=5342.032,4192.3203");
        }
        baseStation: baseStation {
            @display("p=3633.3442,4154.208");
        }
        sensorNodeTank: sensorNodeTank {
            @display("p=2299.424,4058.9282");
        }
        sensorNode1: sensorNode {
            @display("p=774.94403,3690.5122");
        }
        tempSensor1: tempSensor {
            @display("p=774.94403,2350.24");
        }
        humidity1: humidity {
            @display("p=895.632,2858.4001");
        }
        sensorNode2: sensorNode {
            @display("p=228.67201,1848.4321");
        }
        tempSensor2: tempSensor {
            @display("p=520.864,641.552");
        }
        humidity2: humidity {
            @display("p=590.736,1162.416");
        }
        photoVoltaic: photoVoltaic {
            @display("p=3760.3843,3550.768");
        }
        photoVoltaic1: photoVoltaic {
            @display("p=4941.8564,2737.7122");
        }
        photoVoltaic2: photoVoltaic {
            @display("p=2636.08,3468.1921");
        }
        photoVoltaic3: photoVoltaic {
            @display("p=1238.64,3017.2002");
        }
        photoVoltaic4: photoVoltaic {
            @display("p=597.088,1626.112");
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


        photoVoltaic1.envPort <--> hydroponic.envPorts[8];
        photoVoltaic4.envPort <--> hydroponic.envPorts[9];
        photoVoltaic3.envPort <--> hydroponic.envPorts[10];
        photoVoltaic2.envPort <--> hydroponic.envPorts[11];
        photoVoltaic.envPort <--> hydroponic.envPorts[12];


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


        photoVoltaic1.powerPlug <--> sensorNode.powerPlug;
        photoVoltaic.powerPlug <--> baseStation.powerPlug;
        photoVoltaic2.powerPlug <--> sensorNodeTank.powerPlug;
        photoVoltaic3.powerPlug <--> sensorNode1.powerPlug;
        photoVoltaic4.powerPlug <--> sensorNode2.powerPlug;
}
