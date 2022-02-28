/*
 * hydroponic.h
 *
 *  Created on: Aug 26, 2020
 *      Author: farouq
 */

#ifndef HYDROPONIC_H_
#define HYDROPONIC_H_

#include <omnetpp.h>
//#include <string.h>
//#include <cstring>

using namespace std;
using namespace omnetpp;


namespace simponics {
class hydroponic : public cSimpleModule
{
    private:
        double temperature=0.0;
        double humidity=0.0;
        double ph=0.0;
        double ec=0.0;
        double irradiance=0.0;
        double concetration[100]={};                //Each element of the array


    protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
      virtual void finish();
};
}; // namespace
#endif /* HYDROPONIC_H_ */
