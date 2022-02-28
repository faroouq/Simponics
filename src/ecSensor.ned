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
// Electric Conductivity Sensor
// It is modeled according to Atlas Scoentific Sensor
//	Source: https://www.atlas-scientific.com/files/EC_EZO_Datasheet.pdf
//
simple ecSensor
{
    parameters:					//electric and time characteristics of the sensor
        double V = 5.0;			//voltage
        double I = 50e-3;		//current (A) consumed when sensing
        double T = 1.0;			//Minimum reading time is 1s.
        double I_sleep = 0.7e-3;	//Current consumption during sleep

        @display("i=ecSensor;is=s");
    gates:
        inout envPort;			//This is the port connected to hydroponics
        inout mcuPort;			//this is the port connected to MCU
}
