Our robotic task is defined using the following parameters:
	- High-level Actions {ACC, DEC, CONS}
	- State Variables = {position, velocity, acceleration}: 

A trajectory (implemented as a stand alone object) is defined over time 
  - gives the value of state variables at each time-step, i.e. traj := T->(SV*HA) 
  - a trajectory is defined w.r.t. constants, where 
  	- constants := {max_velocity, deceleration_value, acceleration_value, target_position, max_time}
	- as the first step, we assume the above is fixed

	
We now define a function to generate trajectories. This generator function is defined using:
  1- A core function, which given the values for state variables and
     current high-level action, returns the next high-level action, i.e. F_core: (SV*HA)->HA'
  2- A motor model M is used to captures how a chosen HA affects the SV in the next time step 

The combination of F_core and M, allows us to start from initial SV values,
apply F_core and M successively, to generate new SV. The trajectory is just
the sequence of SV*HA values starting from time=0 to time=T (alternative, we
can think about it as function from time to SV*HA)

!! Assuming that F_core is deterministic, we only get one trajectory given
the values for constants. However, we need to generate, *a multiset* of
trajectories for each constant, where each traj in this mset, is slightly
different in when the HAs transition, i.e. there is noise in when
transitions occur. 

	solution: we use a probabilistic F_core, with the same signature, but
	outputs slightly different HAs around the decision boundaries. 
 


# COMMENTS:
# A trajectory object should have pretty_print() function and a save(file_name) function
# As an optional feature, we can plot each trajectory 
# we can call generate function iteratively, to generate different trajectories of the same robot. The trajectories will differ in the timing of HA transitions. 


# how to run:
todo


