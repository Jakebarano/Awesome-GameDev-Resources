# Flocking agents behavior assignment

You are in charge to implement some functions to make some AI agents flock together in a game. After finishing it, uou will be one step further to render it in a game engine, and start making reactive NPCs and enemies. You will learn all the basics concepts needed to code and customize your own AI behaviors.

## What is flocking?

Flocking is a behavior that is observed in birds, fish and other animals that move in groups. It is a very simple behavior that can be implemented with a few lines of code. The idea is that each agent will try to move towards the center of mass of the group (cohesion), and will try to align its velocity with the average velocity of the group (AKA alignment). In addition, each agent will try to avoid collisions with other agents (AKA avoidance).

!!! note "Formal Notation Review"

    - $\overrightarrow{F}$ means a vector $F$ that has components. In a 2 dimensional vector it will hold $F_x$ and $F_y$. For example, if $F_x = 1$ and $F_y = 3$, then $\overrightarrow{F} = (1,3)$
    - Simple math operations between vectors are done component-wise. For example, if $\overrightarrow{F} = (1,1)$ and $\overrightarrow{G} = (2,2)$, then $\overrightarrow{F} + \overrightarrow{G} = (3,3)$
    - $\overrightarrow{P_1P_2}$ means the vector that goes from $P_1$ to $P_2$. It is the same as $P_2-P_1$
    - The modulus notation means the length (magnitude) of the vector. $|\overrightarrow{F}| = \sqrt{F_x^2+F_y^2}$ For example, if $\overrightarrow{F} = (1,1)$, then $|\overrightarrow{F}| = \sqrt{2}$
    - The hat ^ notation means the normalized vector(magnitude is 1) of the vector. $\hat{F} = \frac{\overrightarrow{F}}{|\overrightarrow{F}|}$ For example, if $\overrightarrow{F} = (1,1)$, then $\hat{F} = (\frac{1}{\sqrt{2}},\frac{1}{\sqrt{2}})$
    - The hat notation over 2 points means the normalized vector that goes from the first point to the second point. $\widehat{P_1P_2} = \frac{\overrightarrow{P_1P_2}}{|\overrightarrow{P_1P_2}|}$ For example, if $P_1 = (0,0)$ and $P_2 = (1,1)$, then $\widehat{P_1P_2} = (\frac{1}{\sqrt{2}},\frac{1}{\sqrt{2}})$
    - The sum $\sum$ notation means the sum of all elements in the list going from `0` to `n-1`. Ex. $\sum_{i=0}^{n-1} \overrightarrow{V_i} = \overrightarrow{V_0} + \overrightarrow{V_1} + \overrightarrow{V_2} + ... + \overrightarrow{V_{n-1}}$

It is your job to implement those 3 behaviors following the ruleset below:

### Cohesion

Apply a force towards the center of mass of the group.

1. The $n$ neighbors of an agent are all the other agents that are within a certain radius of the agent. It doesnt include the agent itself;
2. Compute the location of the center of mass of the group ($P_{CM}$);
3. Compute the force that will move the agent towards the center of mass($\overrightarrow{F_{c}}$); The farther the agent is from the center of mass, the force increases linearly up to the limit of the cohesion radius $r_c$.

$$ 
P_{CM} = \frac{\sum_{i=0}^{n-1} P_i}{n}
$$

$$
F_c = \begin{cases}
    \frac{ \overrightarrow{P_{a}P_{CM}} }{r_c} & \text{if } |\overrightarrow{P_{a}P_{CM}}| \leq r_c \\
    0 & \text{if } |\overrightarrow{P_{a}P_{CM}}| > r_c
\end{cases}
$$

!!! tip

    Note that the maximum magnitude of $F_c$ is 1. Inclusive. This value can be multiplied by a constant $K_c$ to increase or decrease the cohesion force to looks more appealing.

### Separation

It will move the agent away from other agents when they get too close.

1. The $n$ neighbors of an agent are all the other agents that are within the separation radius of the agent;
2. If the distance to a neighbor is less than the separation radius, then the agent will move away from it inversely proportionally to the distance between them.
3. Accumulate the forces that will move the agent away from each neighbor ($\overrightarrow{F_{s}}$). And then, clamp the force to a maximum value of $F_{Smax}$.
   
$$
\overrightarrow{F_s} = \sum_{i=0}^{n-1} \begin{cases}
      \frac{\widehat{AN_i}}{|\overrightarrow{AN_i}|} & \text{if } 0 < |\overrightarrow{AN_i}| \leq r_s \\
      0 & \text{if } |\overrightarrow{AN_i}| = 0  \lor |\overrightarrow{AN_i}| > r_s 
\end{cases}
$$

!!! tip

    Here you can see that if we have more than one neighbor and one of them is way too close, the force will be very high and make the influence of the other neighbors irrelevant. This is the expected behavior.

The force will go near infinite when the distance between the agent and the $n$ neighbor is 0. To avoid this, after accumulating all the influences from every neighbor, the force will be clamped to a maximum magnitude of $F_{Smax}$.

$$
\overrightarrow{F_{s}} = \begin{cases} 
    \overrightarrow{F_s} & \text{if } |\overrightarrow{F_s}| \leq F_{Smax} \\
    \widehat{F_s} \cdot F_{Smax} & \text{if } |\overrightarrow{F_s}| > F_{Smax}
\end{cases}
$$

!!! tip

    - You can implement those two math together, but it is better to isolate in two steps to make it easier to understand and debug.
    - This is not an averaged force like the cohesion force, it is a sum of forces. So, the maximum magnitude of the force can be higher than 1.

### Alignment

It is the force that will align the velocity of the agent with the average velocity of the group.

1. The $n$ neighbors of an agent are all the agents that are within the alignment radius of the agent, including itself;
2. Compute the average velocity of the group ($\overrightarrow{V_{avg}}$);
3. Compute the force that will move the agent towards the average velocity ($\overrightarrow{F_{a}}$);

$$
\overrightarrow{V_{avg}} = \frac{\sum_{i=0}^{n-1} \overrightarrow{V_i}}{n}
$$

## Behavior composition

The force composition is made by a weighted sum of the influences of those 3 behaviors. This is the way we are going to work, this is not the only way to do it, nor the more correct. It is just a way to do it. 

- \( \overrightarrow{F} = K_c \cdot \overrightarrow{F_c} + K_s \cdot \overrightarrow{F_s} + K_a \cdot \overrightarrow{F_a} \)  `This is a weighted sum!`
- \( \overrightarrow{V_{new}} = \overrightarrow{V_{cur}} + \overrightarrow{F} \cdot \Delta t \)  `This is a simplification!`
- \( P_{new} = P_{cur}+\overrightarrow{V_{new}} \cdot \Delta t \)  `This is an approximation!`

!!! warning

    A more precise way for representing the new position would be to use full equations of motion. But given timestep is usually very small and it even squared, it is acceptable to ignore it. But here they are anyway, just dont use them in this assignment:

    - \( \overrightarrow{V_{new}} = \overrightarrow{V_{cur}}+\frac{\overrightarrow{F}}{m} \cdot \Delta t \)
    - \( P_{new} = P_{cur}+\overrightarrow{V_{cur}} \cdot \Delta t + \frac{\overrightarrow{F}}{m} \cdot \frac{\Delta t^2}{2} \)

Where:

- $\overrightarrow{F}$ is the force applied to the agent;
- $\overrightarrow{V}$ is the velocity of the agent;
- $P$ is the position of the agent;
- $m$ is the mass of the agent, here it is always 1;
- $\Delta t$ is the time frame (1/FPS);
- $cur$ is the current value of the variable;
- $new$ is the new value of the variable to be used in the next frame.

The $\overrightarrow{V_{new}}$ and $P_{new}$ are the ones that will be used in the next frame and you will have to print to the console at the end of every single frame.

!!! note

    - For simplicity, we are going to assume that the mass of all agents is 1.
    - In a real game simulation, it would be nice to apply some friction to the velocity of the agent to make it stop eventually or just clamp it to prevent the velocity get too high. But, for simplicity, we are going to ignore it.

## Input

The input consists in a list of parameters followed by a list of agents. The parameters are:

- $r_c$ - Cohesion radius
- $r_s$ - Separation radius
- $F_{Smax}$ - Maximum separation force
- $r_a$ - Alignment radius
- $K_c$ - Cohesion constant
- $K_s$ - Separation constant
- $K_a$ - Alignment constant
- $N$ - Number of agents

Every agent is represented by 4 values in the same line, separated by a space:

- $x$ - X coordinate
- $y$ - Y coordinate
- $vx$ - X velocity
- $vy$ - Y velocity

After reading the agents data, the program should read the time frame ($\Delta t$), simulate the agents and then output the new position of the agents in the same sequence and format it was read. The program should keep reading the time frame and simulating the agents until the end of the input.

### Input Example

In this example we are going to test only the cohesion behavior. The input is composed by the parameters and 2 agents. 

```text
1.000 0.000 0.000 0.000 1.000 0.000 0.000 2
0.000 0.500 0.000 0.000
0.000 -0.500 0.000 0.000
0.010
EOF
```

## Output

The expected output are the position and velocity for each agent after the simulation step using the time frame. After printing each simulation step, the program should wait for the next time frame and then simulate the next step.

```text
0.000 0.490 0.000 -0.010
0.000 -0.490 0.000 0.010
```