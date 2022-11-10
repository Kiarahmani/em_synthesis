#include "generate.h"

#include <iostream>

using namespace constants;

/*
 * User-defined, simulation-specific
 */

Label Generator::true_asp(SystemState prev_ss) {
    Obs obs = prev_ss.obs;

    double expression1 = obs.v - max_velocity;                                  // is at max velocity (can no longer accelerate)
    double expression2 = target - obs.x - dist_traveled(obs.v, deceleration);   // needs to decelerate or else it will pass target

    // Deterministic
    // bool cond1 = expression1 >= 0;
    // bool cond2 = expression2 < zero;

    // Probabilistic
    bool cond1 = flip(logistic(0, 0.4, expression1));
    bool cond2 = flip(logistic(0, -0.3, expression2));

    if(prev_ss.label == ACC){
        if(cond1 && !cond2) return CON;
        else if(cond2) return DEC;
        else return ACC;
    }
    else if(prev_ss.label == CON){
        if(false) return ACC;
        else if(cond2) return DEC;
        else return CON;
    }
    else if(prev_ss.label == DEC){
        if(false) return ACC;
        else if(false) return CON;
        else return DEC;
    }

    printf("Impossible state reached\n");
    return (Label) -1;
}

Obs Generator::world_model(SystemState state) {
    double new_a;
    if (state.label == ACC)
        new_a = acceleration;
    else if (state.label == DEC)
        new_a = deceleration;
    else
        new_a = 0;

    Obs obs = state.obs;

    double new_v = obs.v + obs.a * t_step;
    double new_x = obs.x + (obs.v + new_v) / 2 * t_step;
    
    // Deal with decimal precision problems
    if(abs(new_v) < zero) new_v = zero;
    if(abs(new_v - max_velocity) < zero) new_v = max_velocity;
    if(abs(new_x - target) < zero) new_x = target;

    return { new_x, new_v, new_a };
}

// Helper method: robot has reached target and is at rest. End simulation.
bool finished(Obs obs){
    return obs.x >= target || obs.v < 0;
}


void Generator::print(Trajectory traj) {
    
    for (int i = 1; i < traj.T; i++) {
        if(traj.label_seq[i] != traj.label_seq[i-1]){
            cout << str(traj.label_seq[i-1]) << " --> " << str(traj.label_seq[i]) << " at time " << i * t_step << "\n";
        }
    }
    cout << "\n";
}

void Generator::save_to_file(Trajectory traj, string fn) {
    ofstream csvFile;
    csvFile.open(fn);
    csvFile << fixed << setprecision(4) << setfill(' ') << setw(10);
    csvFile << "t, x, v, a, label\n" << "\n";

    for (int i = 0; i < traj.T; i++) {
        csvFile << i * t_step << ", ";
        csvFile << traj.obs_seq[i].x << ", ";
        csvFile << traj.obs_seq[i].v << ", ";
        csvFile << traj.obs_seq[i].a << ", ";
        csvFile << str(traj.label_seq[i]) << "\n";
    }

    csvFile.close();
}




/*
 * Simulation: all implementation-specific details abstracted away
 */

Trajectory Generator::gen_trajectory(SystemState init_state, int T) {
    SystemState state = init_state;
    Trajectory traj {};

    for (int i = 0; i < T; i++) {
        state.label = true_asp(state);
        state.obs = world_model(state);

        traj.label_seq.push_back(state.label);
        traj.obs_seq.push_back(state.obs);

        traj.T = i;

        if(finished(state.obs))
            break;
    }

    return traj;
}

int main() {
    Label init_label{};
    Obs init_obs{};
    SystemState init_ss = {init_label, init_obs};
    int T = 100;

    Generator gen;

    cout << "--------------Simulation---------------\n";
    cout << "Running 1-D kinematic car simulation:\n";
    for(int i = 0; i < 10; i++){
        Trajectory traj = gen.gen_trajectory(init_ss, T);
        gen.print(traj);
        gen.save_to_file(traj, "out/gen" + to_string(i) + ".csv");
    }

    return 0;
}
