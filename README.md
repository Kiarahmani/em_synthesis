# EM Synthesis Project

Our goal is to synthesize a programmatic state machine policy from time-series data while simultaneously inferring a set of high-level labels.

Our system is a *discrete-time Markov process* defined by:
   - a **high-level label space** $H$ = a set of discrete high-level labels $h \in H$
     - Ex: $h \in$ {ACC, DEC, CON}
   - a **low-level action space** $L$ = a continuous domain of low-level actions $l \in L$: controlled joystick directives, motor inputs, etc.
     - Ex: $l = a \in \mathbb{R}$, where $a$ is the acceleration
   - a **observed state space** $O$ = a continuous domain of observed variables $o \in O$
     - Ex: $o = (x, v) \in \mathbb{R}^2$, where $x$ is the position and $v$ is the velocity
   - an **action-selection policy (ASP)** $\pi: H \times O \rightarrow H$ that maps the current high-level label and the current observed variables to the next high-level label
   - a **motor model** $\phi: H \rightarrow L$ that maps the current high-level action to the current low-level action
   - an extra set of domain-specific constants $C$
     - Ex: $C$ = {max_velocity, deceleration_value, acceleration_value, target_position}

---
## Overall problem formulation:
### Inputs
We define a trajectory $\tau$ over a time period $T$ as a function $\tau : T \rightarrow H \times L \times O$, which can be thought of as giving the value of the system's state $(h, l, o)$ at each time step $t=0...T$.

We know the problem domain $H, L, O$, as well as $C$ and the motor model $\phi$. We are given a set of **demonstrations**, which are defined simply as trajectories with the high-level labels missing, i.e. $(l, o)$ for all time steps.

### Outputs
We would like to:
1. Infer the values of the high-level labels in the demonstrations
2. Synthesize an ASP that is maximally consistent with the demonstrations ($\pi^*$)

---

## Project Organization
This project is roughly split into the following components:
- **data_gen** - using simulations to generate demonstrations
- expectation (particle filter)
- maximization (program synthesis)