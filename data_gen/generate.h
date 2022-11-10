
#include <vector>
#include <string>
using namespace std;


// each Traj represents a demonstration that 
// describes a robot (HA x O) over T timesteps
// HA: high-level action
// LA: low-level action
// S: state
// O: observation = LA x S
// RS: robot state = HA x LA x S = HA x O



enum HA {
  ACC,
  CON,
  DEC
};

struct O {
  double x;
  double v;
  double a;
};

struct RS {
  HA ha;
  O o;
};


struct Traj {
  int T;
  vector<HA> ha_seq;
  vector<O> o_seq;
};



// set of physical constants used to describe the robot, 
// its goals, and its environment
struct Cons {
  double acc_val;
  double dec_val;
  double v_max;
  double x_target;
  int T;
  double t_step;
};



class Generator {

  public:

  HA gt_asp(RS rs_prev, Cons cons);
  O combined_model(RS rs_prev, Cons cons);    // motor model + physics model

  Traj gen_traj(RS rs_0, Cons cons);
  void pretty_print(Traj traj);
  void save_to_file(Traj traj, string fn);

};





