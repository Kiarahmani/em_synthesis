



HA Generator::gt_asp(RS rs, Cons cons){
  bool cond1 = rs.v-cons.v_max >= 0;
  bool cond2 = (cons.x_target-rs.x) - DT(rs.v, cons.dec_val) <= 0;

  if(cond2) return { DEC };
  else if(ha == ACC && cond1) return { CON };
  else return rs.ha;
}

LA Generator::motor_model(RS rs, Cons cons){
  if(rs.ha==ACC) return { cons.acc_val };
  if(rs.ha==DEC) return { cons.dec_val };
  if(rs.ha==CON) return { 0 };
}

S Generator::phys_model(RS rs, Cons cons){
  double new_v = rs.la.a * cons.t_step;
  double new_x = (rs.s.v+new_v)/2 * cons.t_step;
  return { new_x, new_v };
}



Traj Generator::gen_traj(){

  RS rs = rs_0;
  Traj traj;
  for(int i=0; i<cons.T; i++){
    HA ha = gt_asp(rs, cons);
    LA la = motor_model(rs, cons);
    S s = phys_model(rs, cons);
    rs = {ha, la, s};
    traj.ha_seq.push_back(ha);
    traj.la_seq.push_back(la);
    traj.s_seq.push_back(s);
  }

  return traj;

}


