//
//  neuron.hpp
//  
//
//  Created by Juliette Margaria on 02/10/2017.
//
//

#ifndef neuron_hpp
#define neuron_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
class Neuron{
    public:
//====================Constructors---Destructors==================
    Neuron(bool background_noise);
    ~Neuron(){};
//====================Getters//Setters==================
    
    /**
     * Getter for external current
     @return current value of External current
     */
    double getIext()const;
    /**
     * Getter for Time Spike
     @return current value of Spike time
     */
    
    long getTimeSpike()const;
    /**
     * Getter for Refractory Time in step
     @return current value of RefractoryStep
     */
    long getRefractoryStep()const;
    /**
     * Getter for Membrane potential
     @return current value of Membrane Potential
     */
    double getMembranePotential()const;
    /**
     * Getter for Number of spike
     @return current value of Number of spike
     */
    long getNbrSpikes()const ;
    /**
     * Getter for J
     @return current value of J
     */
    double getJ()const;
    /**
     Set Membrane Potential
     @param MP: Membrane potential
     */
    void setMembranePotential(double MP);
    /**
     Set external current
     @param i_ext: external current
     */
    void setI_ext(double I);
    /**
     Set J
     @param j: weight of the connection in mV
     */
    void setJ( double j);
    
    
//====================Convertor==================
    /**
     Convert a double into a string
     @param c: the double to convert
     @return c in string
     */
    std::string double_to_string(double c)const;
//====================Fonctions==================
    /**
     Receive a sike a time arrival with wheight j.
     If more than one spike arrives at the same time, j is the sum of all of them
     @param arrival: time in step at which the spike arrives
     @param j: weight of the connection in mV
     */
    void receive(unsigned long arrival, double j);
//====================Update==================
    /**
     update the state of the neurone each time t
     @param steps: number of simulation steps
     */
    bool update(long steps);
    
    
    private:
    
//====================Attributs==================
    double MembranePotential_;//!<Membrane Potential
    long NbSpikes_; //!<Number of spike
    long TimeSpikes_;//!<Time of the last spike
    bool refractory_;//!<return true if the state is refractory
    double RefractoryStep_;//!<Refractory time in steps
    long tsim_;//!<clock
    double Iext_;//!<external current
    std::vector<double> Buffer_;//!< buffer for spike
    double c1;//!<constant for integration
    double c2;//!<constant for integration
    double J;//!< weight of the connections that provides the current neuron
    bool background_noise_;//!< To add or not the poisson distributions (easier for the test)
};

#endif /* neuron_hpp */
