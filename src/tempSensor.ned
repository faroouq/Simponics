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
// TODO auto-generated type
//
simple tempSensor
{
    parameters:
        double R = 10e+3;						//Resistor in the potential divider
        double v = 5.0;						//voltage connected
        double t = 0.5;


        @display("i=tempSensor;is=n");

    gates:
        inout envPort;
        inout mcuPort;
}
