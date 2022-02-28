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
// Humidity sensor DHT 11
//Source:https://datasheetspdf.com/pdf-file/785590/D-Robotics/DHT11/1
//
simple humidity
{
    parameters:					//electric and time characteristics of the sensor
        double V = 5.0;			//voltage
        double I = 2.5e-3;		//current (A) consumed when sensing
        double T = 6.0;			//Minimum reading time is 1s.
		double I_sleep=100e-6;	//Current consumption during sleep

        @display("i=humiditySensor;is=n");
    gates:
        inout envPort;			//This is the port connected to hydroponics
        inout mcuPort;			//this is the port connected to MCU
}
