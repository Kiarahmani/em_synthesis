
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;

#define zero 1E-9

// flip a coin with probability p
bool flip(double p){
    double rv = ((double) rand())/RAND_MAX;
    return rv <= p;
}

// evaluate a logistic function
double logistic(double midpoint, double spread, double input){
    return 1.0 / (1.0 + exp(-spread * (input - midpoint)));
}

// Return the distance traveled by a robot until it comes to rest, with some starting velocity and constant deceleration
double dist_traveled(double v, double dec) {
    return -v * v / (2 * dec);
}