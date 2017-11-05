//
//  Network.hpp
//  
//
//  Created by Juliette Margaria on 30/10/2017.
//
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include "neuron.hpp"
class Network {
    public:
//====================Constructor/Destructor==================
    Network ();
    ~Network(){};
//====================Setters//Getters==================
    /**
     * Getter for Neurons_
     @return all the neurons in the network
     */
    std::vector<Neuron> getNeurons()const;
    /**
     * Getter Connections
     @return all the connections between the neurones
     */
    std::vector<std::vector<int> > getConnections () const;
 
   
    
//====================Update==================
    /**
     * update the state of the network until the time 't_stop'
     @param tstop: the time ...????
     */
     
    void update( unsigned long tstop);
    
    private:
//====================Attributs==================

    std::vector<Neuron> Neurons_;//!< vector of all neurons
    std::vector<std::vector<int> >Connections_;//!< connections between the different neurons
    unsigned long NbrNeuron;

};
#endif /* Network_hpp */
