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


network Smart_multi_hop_clustered
{
    @display("bgb=1418.445,782.53876");
    submodules:
        hydroponic: hydroponic {
            @display("p=396.50626,282.79123;b=46,46");
        }


        tempSensor: tempSensor {
            @display("p=899.2462,252.86624");
        }
        sensorNode: sensorNode {
            @display("p=1059.345,228.92624");
        }
        humidity: humidity {
            @display("p=897.75,341.145");
        }
        photoVoltaic: photoVoltaic {
            @display("p=897.75,110.722496");
        }
        pHSensor1: pHSensor {
            @display("p=619.4475,628.425");
        }
        ecSensor1: ecSensor {
            @display("p=535.6575,715.20746");
        }
        photoVoltaic1: photoVoltaic {
            @display("p=731.66626,599.9962");
        }

        workStation: workStation {
            @display("p=1313.7075,599.9962");
        }
        baseStation: baseStation {
            @display("p=1210.4662,438.40125");
        }
        sensorNodeTank: sensorNodeTank {
            @display("p=969.57,629.92126");
        }
        clusterHead: clusterHead {
            @display("p=1072.8113,395.00998");
        }
    connections allowunconnected:
        sensorNode.powerPlug <--> photoVoltaic.powerPlug;
        tempSensor.mcuPort <--> sensorNode.sensor[0];
        humidity.mcuPort <--> sensorNode.sensor[1];

        tempSensor.envPort <--> hydroponic.envPorts[0];
        humidity.envPort <--> hydroponic.envPorts[1];
        photoVoltaic.envPort <--> hydroponic.envPorts[4];
        sensorNode.bsPort <--> clusterHead.port[0];

        photoVoltaic1.powerPlug <--> sensorNodeTank.powerPlug;
        photoVoltaic1.envPort <--> hydroponic.envPorts[5];
        ecSensor1.envPort <--> hydroponic.envPorts[6];
        pHSensor1.envPort <--> hydroponic.envPorts[7];

        pHSensor1.mcuPort <--> sensorNodeTank.sensor[0];
        ecSensor1.mcuPort <--> sensorNodeTank.sensor[1];
        sensorNodeTank.bsPort <--> clusterHead.port[1];


        workStation.port <--> baseStation.wsPort;
        clusterHead.bsPort <--> baseStation.port[0];
}
