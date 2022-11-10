#include <string>
#include <vector>

#include "library_functions.h"

using namespace std;

/*
 * User defined problem domain
 */


// High-level action labels
enum Label { ACC, CON, DEC };
vector<string> label_strings = { "ACC", "CON", "DEC" };


// Low-level robot action & state
struct Obs {
    double x; // position
    double v; // velocity
    double a; // acceleration
};


// Set of physical constants used to describe the robot, its goals, and its environment
namespace constants {
    double acceleration = 10; // Constant acceleration
    double deceleration = -20; // Constant deceleration
    double max_velocity = 20; // Maximum velocity
    double target = 100;       // Target distance
    double t_step = 0.1;
};




/*
 * Abstractions & Definitions
 */

// Defines the full system state
struct SystemState {
    Label label;
    Obs obs;
};

// Gives a sequence of labels accompanied by a sequence of observed state values
struct Trajectory {
    int T;
    vector<Label> label_seq;
    vector<Obs> obs_seq;
};








/*
 * Helper functions
 */

// Converting enums to strings and vice versa
Label label(string label){
    for(int i = 0; i < label_strings.size(); i++){
        if(label == label_strings[i])
            return (Label) i;
    }
    printf("Enum not set up correctly!\n");
    return (Label) -1;
}

string str(Label label){
    for(int i = 0; i < label_strings.size(); i++){
        if(label == (Label) i)
            return label_strings[i];
    }
    printf("Enum not set up correctly!\n");
    return "";
}