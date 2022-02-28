


#include "hydroponic.h"
#include "sensoryMsg_m.h"

#include <math.h>

namespace simponics {

Define_Module(hydroponic);


/*******************************************************************************************
 *
 *******************************************************************************************/
void hydroponic::initialize()
{
    this->temperature=getAncestorPar("temperature");            //get the temperature
    this->ph=getAncestorPar("ph");                              //pH of the sensor
    this->ec=getAncestorPar("ec");
}


/*******************************************************************************************
 *
 *******************************************************************************************/
void hydroponic::handleMessage(cMessage *msg)
{   //************************Temperature of Hydroponics system*****************************
    if(strcmp(msg->getName(),"temp?")==0){
        char *mySensor=new char [5];
        strcpy(mySensor,msg->getArrivalGate()->getBaseName());
        strcat(mySensor,"$o");
        int mySensor_index=msg->getArrivalGate()->getIndex();

        delete(msg);                                //Msg has finish its work
        sensoryMsg *msg=new sensoryMsg("temp");     //Lets reply with temperature
        msg->setEntries(1);
        msg->setDataName(0, "temp");                //create the response for temperature
        msg->setDataValue(0, this->temperature);    //put response in message


        send(msg, mySensor, mySensor_index);
        bubble("Temp. sent");
        EV<<"Temp="+to_string(this->temperature)<<endl;


    //************************Humidity of Hydroponics System********************************
    }else if(strcmp(msg->getName(),"humd?")==0){
        char *mySensor=new char [5];
        strcpy(mySensor,msg->getArrivalGate()->getBaseName());
        strcat(mySensor,"$o");
        int mySensor_index=msg->getArrivalGate()->getIndex();

        delete(msg);                                //Msg has finish its work
        sensoryMsg *msg=new sensoryMsg("humd");     //Lets reply with temperature
        msg->setEntries(1);
        msg->setDataName(0, "humd");                //create the response for temperature
        msg->setDataValue(0, this->humidity);       //put response in message


        send(msg, mySensor, mySensor_index);
        bubble("humd. sent");
        EV<<"Humd="+to_string(this->humidity)<<endl;//Prompt for validation


    //************************pH of Hydroponics System********************************
    }else if(strcmp(msg->getName(),"ph?")==0){
        char *mySensor=new char [5];
        strcpy(mySensor,msg->getArrivalGate()->getBaseName());
        strcat(mySensor,"$o");
        int mySensor_index=msg->getArrivalGate()->getIndex();

        delete(msg);                            //Msg has finish its work
        sensoryMsg *msg=new sensoryMsg("ph");   //Lets reply with temperature
        msg->setEntries(1);
        msg->setDataName(0, "ph");              //create the response for temperature
        msg->setDataValue(0, this->ph);         //put response in message


        send(msg, mySensor, mySensor_index);
        bubble("pH sent");
        EV<<"pH="+to_string(this->ph)<<endl;    //Prompt for validation


    //************************EC of Hydroponics System********************************
    }else if(strcmp(msg->getName(),"ec?")==0){
        char *mySensor=new char [5];
        strcpy(mySensor,msg->getArrivalGate()->getBaseName());
        strcat(mySensor,"$o");
        int mySensor_index=msg->getArrivalGate()->getIndex();

        delete(msg);                                //Msg has finish its work
        sensoryMsg *msg=new sensoryMsg("ec");       //Lets reply with Electric Conductivity (EC)
        msg->setEntries(1);
        msg->setDataName(0, "ec");                  //create the response for EC
        msg->setDataValue(0, this->ec);             //put response in message


        send(msg, mySensor, mySensor_index);
        bubble("EC sent");
        EV<<"EC="+to_string(this->ec)<<endl;         //Prompt for validation


    //************************Solar of Hydroponics System********************************
    }else if(strcmp(msg->getName(),"photo?")==0){
        char *mySensor=new char [5];
        strcpy(mySensor,msg->getArrivalGate()->getBaseName());
        strcat(mySensor,"$o");
        int mySensor_index=msg->getArrivalGate()->getIndex();

        double myTime = simTime().dbl();            //Simulation time
        myTime = (double)(((int)myTime/(3600))%24); //Convert time to 24hr format
        this->irradiance = -25.6*pow(myTime,2) + 614.4*myTime - 2764.8;

        delete(msg);                                //Msg has finish its work
        sensoryMsg *msg=new sensoryMsg("photo");    //Lets reply with Electric Conductivity (EC)
        msg->setEntries(1);
        msg->setDataName(0, "photo");               //create the response for EC
        msg->setDataValue(0, this->irradiance);     //put response in message


        send(msg, mySensor, mySensor_index);
        bubble("EC sent");
        EV<<"EC="+to_string(this->irradiance)<<endl;      //Prompt for validation



    }else{
        bubble("Unknown Message");
        delete(msg);
    }
}


/*******************************************************************************************
 *
 *******************************************************************************************/
void hydroponic::finish()
{

}


}; //Namespace
