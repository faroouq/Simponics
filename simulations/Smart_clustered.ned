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


network Smart_clustered
{
    @display("bgb=1635.2999,869.1975");
    submodules:
        hydroponic: hydroponic {
            @display("p=396.50626,282.79123;b=46,46");
        }


        tempSensor: tempSensor {
            @display("p=945.63,191.97");
        }
        sensorNode: sensorNode {
            @display("p=1151.82,302.175");
        }
        humidity: humidity {
            @display("p=926.07745,330.615");
        }
        pHSensor1: pHSensor {
            @display("p=926.07745,577.6875");
        }
        ecSensor1: ecSensor {
            @display("p=773.21246,774.99");
        }
        workStation: workStation {
            @display("p=1436.22,424.82248");
        }
        baseStation: baseStation {
            @display("p=1281.5775,181.305");
        }
        sensorNodeTank: sensorNodeTank {
            @display("p=1164.2625,739.44");
        }
        clusterHead: clusterHead {
            @display("p=1247.8049,510.1425");
        }


        photoVoltaic: photoVoltaic {
            @display("p=1162.485,56.879997");
        }
        photoVoltaic1: photoVoltaic {
            @display("p=1036.2825,424.82248");
        }
        photoVoltaic2: photoVoltaic {
            @display("p=1135.8225,565.245");
        }
        photoVoltaic3: photoVoltaic {
            @display("p=899.415,695.0025");
        }
    connections allowunconnected:
        tempSensor.mcuPort <--> sensorNode.sensor[0];
        humidity.mcuPort <--> sensorNode.sensor[1];

        tempSensor.envPort <--> hydroponic.envPorts[0];
        humidity.envPort <--> hydroponic.envPorts[1];
        sensorNode.bsPort <--> clusterHead.port[0];

        ecSensor1.envPort <--> hydroponic.envPorts[2];
        pHSensor1.envPort <--> hydroponic.envPorts[3];

        pHSensor1.mcuPort <--> sensorNodeTank.sensor[0];
        ecSensor1.mcuPort <--> sensorNodeTank.sensor[1];
        sensorNodeTank.bsPort <--> clusterHead.port[1];


        workStation.port <--> baseStation.wsPort;
        clusterHead.bsPort <--> baseStation.port[0];
        
        photoVoltaic.envPort <--> hydroponic.envPorts[4];
        photoVoltaic3.envPort <--> hydroponic.envPorts[5];
        photoVoltaic2.envPort <--> hydroponic.envPorts[6];
        photoVoltaic1.envPort <--> hydroponic.envPorts[7];
        
        
        photoVoltaic.powerPlug <--> baseStation.powerPlug;
        photoVoltaic3.powerPlug <--> sensorNodeTank.powerPlug;
        photoVoltaic2.powerPlug <--> clusterHead.powerPlug;
        photoVoltaic1.powerPlug <--> sensorNode.powerPlug;
}
