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
import simponics.clusterHead;


network Smart_clustered_4
{
    @display("bgb=2824.822,1405.356");
    submodules:
        hydroponic: hydroponic {
            @display("p=430.155,684.33746;b=46,46");
        }


        tempSensor: tempSensor {
            @display("p=1089.6074,469.25998");
        }
        sensorNode: sensorNode {
            @display("p=1645.226,589.798");
        }
        humidity: humidity {
            @display("p=993.6225,682.56");
        }
        pHSensor1: pHSensor {
            @display("p=1084.275,881.63995");
        }
        ecSensor1: ecSensor {
            @display("p=993.6225,963.40497");
        }
        workStation: workStation {
            @display("p=2731.696,682.924");
        }
        baseStation: baseStation {
            @display("p=2362.014,293.488");
        }
        sensorNodeTank: sensorNodeTank {
            @display("p=1865.342,962.302");
        }
        clusterHead: clusterHead {
            @display("p=2288.642,682.924");
        }


        sensorNode1: sensorNode {
            @display("p=1755.2839,293.488");
        }
        tempSensor1: tempSensor {
            @display("p=1089.292,132.634");
        }
        humidity1: humidity {
            @display("p=902.97,291.50998");
        }
        sensorNode2: sensorNode {
            @display("p=2105.212,1300.942");
        }
        tempSensor2: tempSensor {
            @display("p=812.3175,1102.0499");
        }
        humidity2: humidity {
            @display("p=746.55,1246.0275");
        }
        photoVoltaic: photoVoltaic {
            @display("p=659.4525,1329.57");
        }
        photoVoltaic1: photoVoltaic {
            @display("p=954.51746,1078.9425");
        }
        photoVoltaic2: photoVoltaic {
            @display("p=1128.7125,794.5425");
        }
        photoVoltaic3: photoVoltaic {
            @display("p=993.6225,590.13");
        }
        photoVoltaic4: photoVoltaic {
            @display("p=977.625,371.4975");
        }
        photoVoltaic5: photoVoltaic {
            @display("p=858.5325,39.105");
        }
    connections allowunconnected:
        tempSensor.mcuPort <--> sensorNode.sensor[0];
        humidity.mcuPort <--> sensorNode.sensor[1];


        tempSensor1.mcuPort <--> sensorNode1.sensor[0];
        humidity1.mcuPort <--> sensorNode1.sensor[1];


        tempSensor2.mcuPort <--> sensorNode2.sensor[0];
        humidity2.mcuPort <--> sensorNode2.sensor[1];


        tempSensor.envPort <--> hydroponic.envPorts[0];
        humidity.envPort <--> hydroponic.envPorts[1];
        ecSensor1.envPort <--> hydroponic.envPorts[2];
        pHSensor1.envPort <--> hydroponic.envPorts[3];
        tempSensor1.envPort <--> hydroponic.envPorts[4];
        humidity1.envPort <--> hydroponic.envPorts[5];
        tempSensor2.envPort <--> hydroponic.envPorts[6];
        humidity2.envPort <--> hydroponic.envPorts[7];


        photoVoltaic.envPort <--> hydroponic.envPorts[8];
        photoVoltaic1.envPort <--> hydroponic.envPorts[9];
        photoVoltaic2.envPort <--> hydroponic.envPorts[10];
        photoVoltaic3.envPort <--> hydroponic.envPorts[11];
        photoVoltaic4.envPort <--> hydroponic.envPorts[12];
        photoVoltaic5.envPort <--> hydroponic.envPorts[13];


        pHSensor1.mcuPort <--> sensorNodeTank.sensor[0];
        ecSensor1.mcuPort <--> sensorNodeTank.sensor[1];


        sensorNode.bsPort <--> clusterHead.port[0];
        sensorNodeTank.bsPort <--> clusterHead.port[1];
        sensorNode1.bsPort <--> clusterHead.port[2];
        sensorNode2.bsPort <--> clusterHead.port[3];

        workStation.port <--> baseStation.wsPort;
        clusterHead.bsPort <--> baseStation.port[0];


        photoVoltaic5.powerPlug <--> baseStation.powerPlug;
        photoVoltaic4.powerPlug <--> sensorNode1.powerPlug;
        photoVoltaic3.powerPlug <--> sensorNode.powerPlug;
        photoVoltaic2.powerPlug <--> clusterHead.powerPlug;
        photoVoltaic1.powerPlug <--> sensorNodeTank.powerPlug;
        photoVoltaic.powerPlug <--> sensorNode2.powerPlug;
}
