
#include <string>
#include <vector>

using namespace std;

#define zero 1E-9

// flip a coin with probability p
bool flip(double p){
    double rv = ((double) rand())/RAND_MAX;
    return rv <= p;
}

// Return the distance traveled by a robot until it comes to rest, with some starting velocity and constant deceleration
double dist_traveled(double v, double dec) {
    return -v * v / (2 * dec);
}