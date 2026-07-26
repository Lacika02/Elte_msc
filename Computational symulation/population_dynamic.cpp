#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <chrono>
#include "vector.hpp"
#include "odeint.hpp"
using namespace std;

static double p1;                        // Starting number of p_1 population
static double p2;                        // Starting number of p_2 population
static double p3;                        // Starting number of p_3 population
static double g1;                        // natural death or growth rate of species 1
static double g2;                        // natural death or growth rate of species 2
static double g3;                        // natural death or growth rate of species 3
static double d12;                       // the effect the 2. species has  on species 1
static double d13;                       // the effect the 3. species has on species 1
static double d21;                       // the effect the 1. species has on species 2
static double d23;                       // the effect the 3. species has on species 2
static double d31;                       // the effect the 1. species has on species 3
static double d32;                       // the effect the 2. species has on species 3


static double sim_time;                     // Simulated time [units]
static double dt;                           // Step size [units]

std::string odeint;
std::string filename;





cpl::Vector derivates(const cpl::Vector& x) {

    double t = x[0], n_p1 = x[1], n_p2 = x[2]; double  n_p3 = x[3] ;

    cpl::Vector f(4);
    f[0] = 1;
    f[1] =(g1 * p1) + (d12 * p1 * p2) + (d13 * p1 * p3); // dp1/dt
    f[2] = (d21 * p2 *p1)+ (g2 * p2) + (d23 * p2 *p3);  // dp2/dt
    f[3] = (d31 * p3 * p1) + (d32 * p3 * p2) + (g3 * p3); // dp3/dt
    return f;
}

void Euler( cpl::Vector&x , double& tau ,
cpl::Vector derivs(const cpl::Vector&)){
x += tau*derivs(x) ;
for (int index = 0; index < 4; index++)
{
    if (x[index] <0)
    {
        x[index] = 0;    // if its below zero rewrite its value to 0( they cant become more extint)
    }
    if (x[index] >10000)   // if  its more than 10.000 rewrite its value at 10.000, it just a number I came up with, like they dont have enough to eat and starve
    {
        x[index] = 10000;
    }
    
}

}

int main() {

cout << "Population dynamic simulation starting. \n"
        << " -----------------------------------------------------\n"
        << " Enter filename, p1, p2, p3, ,g1 ,g2,g3 ,d12, d13, d21, d23, d31, d32";
cin   >> filename>> p1 >> p2 >> p3 >>g1 >> g2>> g3>> d12 >>d13 >> d21 >> d23 >> d31 >> d32;


sim_time=100;
dt=10e-4;


 //  Initial parameters
    //  x0[0]: time; x0[1]: starting population of first animal; x0[2]: starting population of second animal and so on
    cpl::Vector x0(4);
    x0[0] = 0;  x0[1] = p1,  x0[2] = p2; x0[3] = p3;

    //  Changing variables
    cpl::Vector x;              // Storing orbit parameters for every step
    int steps;                  // Stepsize


ofstream dataFile(filename+".data");

    x = x0;
    steps = 0;


    do {
        for(int i = 0; i < 4; i++) {
                dataFile << x[i] << '\t';
            }
        Euler(x, dt, derivates);
    steps++;

        } while (x[0] < sim_time);



dataFile.close();
}