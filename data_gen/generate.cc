#include "generate.h"
#include <iostream>


double dist_travel(double v_0, double dec_val){
  return -v_0*v_0 / (2*dec_val);
}


HA Generator::gt_asp(RS rs, Cons cons){
  bool cond1 = rs.o.v-cons.v_max >= 0;
  bool cond2 = (cons.x_target-rs.o.x) - dist_travel(rs.o.v, cons.dec_val) <= 0;

  if(cond2) return { DEC };
  else if(rs.ha == ACC && cond1) return { CON };
  else return rs.ha;
}

O Generator::combined_model(RS rs, Cons cons){
  double new_a;
  if(rs.ha==ACC) new_a=cons.acc_val;
  else if(rs.ha==DEC) new_a=cons.dec_val;
  else new_a=0;

  double new_v = rs.o.v + rs.o.a * cons.t_step;
  double new_x = rs.o.x + (rs.o.v+new_v)/2 * cons.t_step;
  return { new_x, new_v, new_a };
}



Traj Generator::gen_traj(RS rs_0, Cons cons){

  RS rs = rs_0;
  Traj traj;
  traj.T = cons.T;

  for(int i=0; i<cons.T; i++){
    HA ha = gt_asp(rs, cons);
    O o = combined_model(rs, cons);
    rs = {ha, o};
    traj.ha_seq.push_back(ha);
    traj.o_seq.push_back(o);
  }
  return traj;
}

void Generator::pretty_print(Traj traj){
  cout << "i HA x v a" << endl;
  for(int i=0; i<traj.T; i++){
    cout << i << " ";
    cout << traj.ha_seq[i] << " ";
    cout << traj.o_seq[i].x << " ";
    cout << traj.o_seq[i].v << " ";
    cout << traj.o_seq[i].a << " ";
    cout << endl;
  }
}

void Generator::save_to_file(Traj traj, string fn){

}


int main(){

  HA ha_0 = { ACC };
  O o_0 = { 0, 0, 0 };
  RS rs_0 = { ha_0, o_0 };
  Cons cons = { 10, -20, 20, 100, 100, .1 };


  Generator gen;
  Traj traj = gen.gen_traj(rs_0, cons);
  gen.pretty_print(traj);


  return 0;
}

