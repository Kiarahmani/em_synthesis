
#include <vector>
using namespace std;





enum HA {
  ACC,
  CON,
  DEC
};

struct LA {
  a;
}

struct S {
  x;
  v;
}

struct RS {
  HA ha;
  LA la;
  S s;
}


// each Traj represents a demonstration that 
// describes a robot (HA x O) over a period of time T
// HA: high-level action
// LA: low-level action
// S: state
// O: observation = LA x S
// RS: robot state = HA x LA x S
struct Traj {
  int T;
  vector<HA> ha_seq;
  vector<LA> la_seq;
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
}



class Generator {

  RS rs_0;      // initial values
  Cons cons;

  HA gt_asp(RS rs_prev, Cons cons);
  LA motor_model(RS rs_prev, Cons cons);
  S phys_model(RS rs_prev, Cons cons);

  Generator();
  Traj gen_traj();
  void pretty_print();

}





