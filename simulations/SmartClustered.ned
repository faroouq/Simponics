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



import simponics.ecSensor;
import simponics.humidity;
import simponics.pHSensor;
import simponics.photoVoltaic;
import simponics.tempSensor;
import simponics.workStation;
import simponics.hydroponic;
import simponics.sensorNode;
import simponics.workStation;


network SmartClustered
{
    @display("bgb=992.94,479.94");
    submodules:
        hydroponic: hydroponic {
            @display("p=304.38,234.84;b=520.98,417.24");
        }


        tempSensor: tempSensor {
            @display("p=654.36,176.7");
        }
        sensorNode: sensorNode {
            @display("p=788.88,256.5");
        }
        humidity: humidity {
            @display("p=653.22003,273.6");
        }
        pHSensor: pHSensor {
            @display("p=653.22003,348.84");
        }
        ecSensor: ecSensor {
            @display("p=653.22003,438.9");
        }
        photoVoltaic: photoVoltaic {
            @display("p=653.22003,79.8");
        }
        workStation: workStation {
            @display("p=914.28,153.9");
        }
    connections allowunconnected:
        tempSensor.envPort <--> hydroponic.envPorts[0];
        tempSensor.mcuPort <--> sensorNode.sensor[0];
        sensorNode.sensor[1] <--> humidity.mcuPort;
        humidity.envPort <--> hydroponic.envPorts[1];
        hydroponic.envPorts[2] <--> pHSensor.envPort;
        sensorNode.sensor[2] <--> pHSensor.mcuPort;
        ecSensor.mcuPort <--> sensorNode.sensor[3];
        ecSensor.envPort <--> hydroponic.envPorts[3];
        sensorNode.powerPlug <--> photoVoltaic.powerPlug;
        photoVoltaic.envPort <--> hydroponic.envPorts[4];
        workStation.port <--> sensorNode.bsPort;
}
