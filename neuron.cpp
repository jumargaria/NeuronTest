//
//  neuron.cpp
//  
//
//  Created by Juliette Margaria on 02/10/2017.
//
//

#include "neuron.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include "constants.hpp"
#include <cassert>
#include <vector>
#include <random>

//unsigned long NbrNeuron(12500);//!< total number of neurons 
//====================Constructor==================
Neuron:: Neuron(bool background_noise):MembranePotential_(0.0),NbSpikes_(0.0),TimeSpikes_(0.0),refractory_(false), RefractoryStep_(0.0),tsim_(0.0),Iext_(0.0),J(JE),background_noise_(background_noise){
    
    for(size_t i(0);i<(DELAY+1);++i){
        Buffer_.push_back(0.0);
    }
       c1=exp(-h/TAU);
       c2=RESISTANCE*(1-c1);
}

//====================Setters//Getters==================

double Neuron:: getIext()const { return Iext_; }

long Neuron:: getTimeSpike()const { return TimeSpikes_; }

long Neuron:: getRefractoryStep()const { return RefractoryStep_; }

long Neuron:: getNbrSpikes()const { return NbSpikes_; }

double Neuron::getJ()const{ return J; }

double Neuron:: getMembranePotential()const { return MembranePotential_; }

void Neuron:: setMembranePotential(double MP){ MembranePotential_=MP; }

void Neuron:: setI_ext(double I){ Iext_=I; }

void Neuron::setJ( double j){ J=j; }
//====================Convertor==================

std::string Neuron::double_to_string(double c)const{
std::stringstream ss;
ss << c;
std::string str = ss.str();
    return str;
}

//====================Functions==================
void Neuron::receive(unsigned long arrival, double j){
    const size_t time = arrival%(DELAY+1);
    assert (time<Buffer_.size());
    Buffer_[time]+=j;
}

//====================Update==================
bool Neuron:: update(long steps){
	
    bool spike(false);
    double lambda (NU_ext* h);
    assert ((lambda <3) and (lambda >1));
    static std::poisson_distribution<> poisson(lambda); // to have NU_ext in ms/steps
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    if(steps<=0) return false;
    
    const long t_stop =tsim_+steps;
    const auto t_in= tsim_%(DELAY+1);
    
    while(tsim_<t_stop){
        if(MembranePotential_>THRESHOLD){
            
            ++NbSpikes_;
            TimeSpikes_= tsim_;
            refractory_= true;
            spike=true;
            
        }
        if(refractory_){
            MembranePotential_= 0.0;
            ++RefractoryStep_;
            
             if(RefractoryStep_ > REF_STEPS) {
               RefractoryStep_=0;
               refractory_=false;
               MembranePotential_=VRESET;
            }
  
        }else{
     MembranePotential_= ((c1* MembranePotential_)
                          + (Iext_*c2)
                          + Buffer_[t_in]);
            
            if(background_noise_){
                //  easier to do the tests
		MembranePotential_+= poisson(gen)*JE;
			}
            
     Buffer_[t_in]=0;
     }
      ++tsim_;
    }
    return spike;
}





