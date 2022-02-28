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
// The Solar Panel is modeled accroding to the pocket9szed solar panel
// Source: https://www.parallax.com/sites/default/files/downloads/750-00030-Solar-Panel-6V-Specifications.pdf
//
simple umht
{
    parameters:
        double V = 5;		//Supply voltage
        double I = 150e-3;	//current
		double T = 1;		//time seconds


        @display("i=umht;is=s");
    gates:
        inout envPort;		//This is the port connected to hydroponics
        inout powerPlug;	//this is the port connected to MCU

}
