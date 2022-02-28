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



import simponics.workStation;
import simponics.sensorNode;
import simponics.workStation;


//
// Sample network, consisting of a source and a sink.
//
network txTest
{
    @display("bgb=365,339");
    submodules:
        sensorNode: sensorNode {
            @display("p=36,51");
        }


        workStation: workStation {
            @display("p=299,182");
        }
    connections allowunconnected:
        workStation.port <--> sensorNode.bsPort;
}
