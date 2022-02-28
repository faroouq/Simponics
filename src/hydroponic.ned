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
simple hydroponic
{
    parameters:
        double temperature=32.0;		//Temperature
        double humidity=20.5;			//Humidity
        double light=0.0;
        double ph=6.5;					//pH sensor reading
       	double ec = 1.4e-3;				//Electric conductivity of the system (initial condition)
        	
    	@display("i=NTF;is=n");
    
    gates:
        inout envPorts[100];			//sensors plug to the Hydroponcs for data

}
