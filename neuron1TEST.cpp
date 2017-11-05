#include "neuron.hpp"
#include "Network.hpp"
#include <iostream>
#include <cmath>
#include "gtest/gtest.h"
#include "constants.hpp"

TEST(neuron1TEST, MembranePotential_){
    Neuron neuron(false);
    neuron.setI_ext(1.0);
    
    //First update test
    neuron.update(1);
    EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0))- neuron.getMembranePotential(),0.0);
    // Test after numerous updates
    neuron.update(10000);
    EXPECT_EQ(0,neuron.getNbrSpikes());
    EXPECT_GT(1E-3,std::fabs(19.999- neuron.getMembranePotential()));
    
    neuron.setI_ext(0.0);
    neuron.update(20000);
    EXPECT_NEAR(0, neuron.getMembranePotential(), 1E-4);
}

TEST(neuron1TEST, TimeSpikes_){
    Neuron neurone(false);
    neurone.setI_ext(1.01);
    neurone.update(924 );
    EXPECT_EQ(0, neurone.getNbrSpikes());
    neurone.update(1);
    EXPECT_EQ(1,neurone.getNbrSpikes());
    EXPECT_EQ(0.0, neurone.getMembranePotential());
    
    neurone.update(944);
    EXPECT_EQ(1, neurone.getNbrSpikes());
    neurone.update(1);
    EXPECT_EQ(2, neurone.getNbrSpikes());
}
TEST(neuron1TEST, NoPostSYnapticSpike){
    Neuron neuron1(false);
    Neuron neurone2(false);
    
    neuron1.setI_ext(1.01);
    for (unsigned int i(0); i<925+DELAY+1;++i){
        if (neuron1.update(1)){
			
            EXPECT_EQ(0.0, neuron1.getMembranePotential());
            neurone2.update(1);
            neurone2.receive(i,neuron1.getJ());
        }else{
        
        neurone2.update(1);
        }
        EXPECT_EQ(0, neurone2.getNbrSpikes());
    }
EXPECT_EQ(0.1, neurone2.getMembranePotential());
    
}
TEST(neuron1TEST, WITHPostSynapticSpike){
    Neuron neurone1(false);
    Neuron neurone2(false);
    
    neurone1.setI_ext(1.01);
    neurone2.setI_ext(1.0);
    
    for (unsigned int i(0); i<1870+DELAY+1;++i){
        if (neurone1.update(1)){
            EXPECT_EQ(0.0, neurone1.getMembranePotential());
            neurone2.update(1);
            neurone2.receive(i,neurone1.getJ());
        }else{
        neurone2.update(1);
    }
    }
    EXPECT_EQ(0, neurone2.getNbrSpikes());
    neurone2.update(1);
    EXPECT_EQ(0, neurone2.getMembranePotential());
    EXPECT_EQ(1,neurone2.getNbrSpikes());
    
}

TEST(neuron1TEST,right_J){
    Network net();
    for ( unsigned int i(0); i< net.getNeurons().size(); ++i ){
		assert(i<net.getNeurons().size());
		
        if(i<net.getNE()){
        EXPECT_EQ(JE, net.getNeurons()[i].getJ());
        }else{
        EXPECT_EQ(JI, net.getNeurons()[i].getJ());
        }
    }
}

TEST(neuron1TEST, Connections){
    Network net();
    for (unsigned i(0); i<net.getNeurons().size(); ++i){
    assert(i<net.getNeurons().size());
    unsigned int compteurCE(0);
    unsigned int compteurCI(0);
        for(unsigned j(0); j<net.getNeurons().size(); ++j){
            assert(j<net.getNeurons().size());
        for (unsigned k(0); k<net.getConnections()[j].size(); ++k ){
            assert(k<net.getConnections()[j].size());

            if((net.getConnections()[j][k])==i){
            if(j<net.NE){
                    ++compteurCE;
                }else{
                    ++compteurCI;
                }
        
            }
        }
        }
        EXPECT_EQ(net.CE, compteurCE);
        EXPECT_EQ(net.CI, compteurCI);
    }
}

int main(int argc, char **argv){
            ::testing::InitGoogleTest(&argc,argv);
            return RUN_ALL_TESTS();
            
        }

