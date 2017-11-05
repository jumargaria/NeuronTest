//
//  mainN.cpp
//  
//
//  Created by Juliette Margaria on 02/10/2017.
//
//

#include "neuron.hpp"
#include "Network.hpp"
#include "constants.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <random>

int main (){

    unsigned int t_stop=10000;//time to stop the simulation
   // unsigned int const nbrNeurons(12500);
    
    Network Net;
    Net.update(t_stop);

return 0;
}


