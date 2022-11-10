#include "generate.h"

#include <iostream>

using namespace constants;

Label Generator::true_asp(SystemState prev_ss) {
    Obs obs = prev_ss.obs;

    bool cond1 = obs.v - max_velocity >= 0;
    bool cond2 = (target - obs.x) - dist_traveled(obs.v, deceleration) <= 0;

    if (cond2)
        return DEC;
    else if (prev_ss.label == ACC && cond1)
        return CON;
    else
        return prev_ss.label;
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


// Robot has reached target and is at rest. End simulation.
bool finished(Obs obs){
    return obs.v < 0 && obs.x >= target;
}

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

void Generator::print(Trajectory traj) {
    cout << "t\tHA\tx\tv\ta" << endl;
    for (int i = 0; i < traj.T; i++) {
        cout << i * t_step << "\t";
        cout << str(traj.label_seq[i]) << "\t";
        cout << traj.obs_seq[i].x << "\t";
        cout << traj.obs_seq[i].v << "\t";
        cout << traj.obs_seq[i].a << "\t";
        cout << endl;
    }
}

void Generator::save_to_file(Trajectory traj, string fn) {}

int main() {
    Label init_label = ACC;
    Obs init_obs = {0, 0, 0};
    SystemState init_ss = {init_label, init_obs};
    int T = 100;

    Generator gen;
    Trajectory traj = gen.gen_trajectory(init_ss, T);
    gen.print(traj);

    return 0;
}
