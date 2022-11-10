#include <string>
#include <vector>

#include "../problem.h"

using namespace std;

class Generator {
   public:
    Label true_asp(SystemState prev_ss);  // Ground truth ASP
    Obs world_model(SystemState prev_ss);  // motor model + physics model

    Trajectory gen_trajectory(SystemState init_state, int T);
    void print(Trajectory traj);
    void save_to_file(Trajectory traj, string fn);
};
