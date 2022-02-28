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


network Smart_multi_hop
{
    @display("bgb=1192.5112,876.8025");
    submodules:
        hydroponic: hydroponic {
            @display("p=406.97998,294.76123;b=46,46");
        }


        tempSensor: tempSensor {
            @display("p=887.27625,261.84375");
        }
        sensorNode: sensorNode {
            @display("p=1015.95374,537.15375");
        }
        humidity: humidity {
            @display("p=866.32874,442.88998");
        }
        pHSensor1: pHSensor {
            @display("p=568.575,632.91376");
        }
        ecSensor1: ecSensor {
            @display("p=345.63373,691.26746");
        }
        workStation: workStation {
            @display("p=1099.7438,731.66626");
        }
        baseStation: baseStation {
            @display("p=905.23126,782.53876");
        }
        sensorNodeTank: sensorNodeTank {
            @display("p=570.0712,782.53876");
        }
    connections allowunconnected:
        tempSensor.mcuPort <--> sensorNode.sensor[0];
        humidity.mcuPort <--> sensorNode.sensor[1];

        tempSensor.envPort <--> hydroponic.envPorts[0];
        humidity.envPort <--> hydroponic.envPorts[1];
        sensorNode.bsPort <--> sensorNodeTank.port[0];

        ecSensor1.envPort <--> hydroponic.envPorts[6];
        pHSensor1.envPort <--> hydroponic.envPorts[7];

        pHSensor1.mcuPort <--> sensorNodeTank.sensor[0];
        ecSensor1.mcuPort <--> sensorNodeTank.sensor[1];
        sensorNodeTank.bsPort <--> baseStation.port[0];


        workStation.port <--> baseStation.wsPort;
}
