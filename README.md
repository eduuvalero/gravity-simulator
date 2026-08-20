# Gravity Simulator

<p>
  <img src="https://img.shields.io/badge/C%2B%2B-20-555555?logo=cplusplus&logoColor=white&labelColor=00599C">
  <img src="https://img.shields.io/badge/OpenGL-3.3-555555?logo=opengl&logoColor=white&labelColor=5586A4">
  <img src="https://img.shields.io/badge/GLAD-0.1.36-555555?logo=opengl&logoColor=white&labelColor=000000">
  <img src="https://img.shields.io/badge/GLFW-3.4-555555?labelColor=000000">
  <img src="https://img.shields.io/badge/GLM-1.0.1-555555?labelColor=000000">
  <img src="https://img.shields.io/badge/CMake-3.60-555555?logo=cmake&logoColor=white&labelColor=064F8C">
  <img src="https://img.shields.io/badge/Emscripten-6.0.6-555555?logo=webassembly&logoColor=white&labelColor=654FF0">
</p>

This project is a simple 3D N-body Newtonian gravity simulation engine built entirely in C++ and rendered using OpenGL.

The project includes:
* A **C++ physics engine** for simulating gravitational interactions between multiple bodies in three-dimensional space
* A **real-time 3D renderer** using OpenGL
* A **WebAssembly build** compiled with Emscripten for running the simulation in a web browser

The purpose of this project was to learn new data structures and algorithms, understand how OpenGL works in C++, and gain a deeper understanding of real-time 3D graphics.

<p align="center">
  <a href="https://eduuvalero.github.io/gravity-simulator/">
    <img src="https://img.shields.io/badge/🌐%20Web%20Demo-View%20Demo-4CAF50?style=for-the-badge">
  </a>
</p>

### `Controls`

| Input | Action |
|---|---|
| `W A S D` | Move |
| `Space` | Move up |
| `Ctrl` | Move down |
| `Mouse` | Look around |
| `Left Mouse Button` | Enable camera control |
| `Esc` | Disable camera control `hold in Web version` |

---

## Requirements

### System
- **C++20** compiler (e.g. `g++`, `Clang++`, ...)
- **CMake 3.60+**
- **Ninja**
- **OpenMP**

### Dependencies
- **OpenGL 3.3 Core**
- **GLAD 0.1.36**
- **GLFW 3.4**
- **GLM 1.0.1**

### Web Build `(optional)`
- **Emscripten 6.0.6**

---

## Input Files

#### [`config.json`](https://github.com/eduuvalero/gravity-simulation/tree/main/configuration/config.json)

`config.json` contains the main parameters for the simulation and renderer.

The configuration is divided into the following sections:

- **Simulation**
  - `dt`: Simulation time step.
  - `inputData`: Path to the CSV file containing the initial state of the bodies.

- **Physics**
  - `gravitationalConstant`: Gravitational constant (`G`) used in force calculations.
  - `softening`: Softening parameter used to avoid numerical singularities at very small distances.
  - `barnesHutTheta`: Controls the accuracy of the Barnes-Hut approximation.

- **Octree**
  - `capacity`: Maximum number of bodies a node can contain before being subdivided.
  - `minimumHalfWidth`: Minimum half-width of an Octree node.

- **Window**
  - `width`: Window width in pixels.
  - `height`: Window height in pixels.
  - `title`: Window title.
  - `vsync`: Enables or disables vertical synchronization.

- **Camera**
  - `position`: Initial camera position.
  - `moveSpeed`: Camera movement speed.
  - `mouseSensitivity`: Mouse rotation sensitivity.
  - `renderDistance`: Maximum rendering distance.

- **Lighting**
  - `cellSize`: Size of each cell used by the lighting spatial grid.
  - `softening`: Softening parameter used for lighting calculations.
  - `threshold`: Minimum contribution required for a light to affect a body.
  - `intensityScale`: Scale factor applied to light intensity.

#### [`Datasets`](https://github.com/eduuvalero/gravity-simulation/tree/main/assets/data)

Gravity Simulator loads complete simulation scenarios from CSV datasets. Each row represents one body and follows this format:

```csv
name,type,mass,radius,x,y,z,vx,vy,vz,R,G,B
```

| Field | Description |
| --- | --- |
| `name` | Name of the body |
| `type` | Body type (`star` or `planet`) |
| `mass` | Mass of the body (`kg`) |
| `radius` | Radius of the body (`m`) |
| `x,y,z` | Initial position (`m`) |
| `vx,vy,vz` | Initial velocity (`m/s`) |
| `R,G,B` | RGB color of the body (only values between 0 and 1) |

##### Creating a Dataset

Create a new `.csv` file using the format above and add one row for each body. Select the dataset as the simulation input through `inputData` in `config.json`.

##### Web Dataset

> The Web version uses a dedicated dataset as its default input.

---

## How to run the project

If you want to compile the project locally and use your own data instead of the web demo, follow these steps.

### 1. Clone the repository

```bash
git clone https://github.com/eduuvalero/gravity-simulation.git
cd gravity-simulation
```

### 2. Configure the project

The project provides CMake presets for different platforms and build configurations:

| Preset | Platform | Configuration |
| --- | --- | --- |
| `mac` | macOS | Release |
| `mac-debug` | macOS | Debug |
| `linux` | Linux | Release |
| `linux-debug` | Linux | Debug |
| `windows` | Windows | Release |
| `windows-debug` | Windows | Debug |
| `web` | WebAssembly / WebGL | Release |

Choose the preset corresponding to your platform:

```bash
cmake --preset <preset>
```

### 3. Build

**Release**
```bash
cmake --build build --parallel
```

**Debug**
```bash
cmake --build build/debug --parallel
```

**Web**
```bash
cmake --build build/web --parallel
```

### 4. Run the project

**Release**
```bash
./build/bin/GravitySimulator
```

**Debug**
```bash
./build/debug/bin/GravitySimulator
```

**Web**

The WebAssembly build generates the files required to run the simulation in a web browser. The generated `.html`, `.js`, `.wasm`, and `.data` files must be served together from a web server and should remain in the same directory.

> The WebAssembly version should be served over HTTP rather than opened directly using `file://`, as browsers restrict some WebAssembly resources when loaded from the local filesystem.

---

## How the program works

### Physics Engine

The **Physics Engine** stores the state of each body and calculates its gravitational acceleration before advancing the simulation with the configured time step. Each body contains its **position, velocity, acceleration, mass, radius, and type**, together with renderer-specific information such as its color.

Gravitational interactions follow [Newton's law of universal gravitation](#newtons-law-of-universal-gravitation). For small systems, every pair can be evaluated directly, but this requires **$O(n^2)$ operations per simulation step**. Gravity Simulator uses the [Barnes-Hut algorithm](#barnes-hut-algorithm) with a three-dimensional [Octree](#octree-spatial-partitioning) to approximate sufficiently distant groups of bodies using their total mass and center of mass, reducing the typical complexity to approximately **$O(n \log n)$**. 

The simulation then advances using [Leapfrog integration](#leapfrog-integration). Since acceleration depends on position, the Octree and accelerations are updated after the bodies move.

[Collisions](#collision-response) are handled separately from the gravitational approximation. Two bodies are considered to be colliding when the distance between their centers is smaller or smaller than the sum of their radio. When this happens, the engine resolves the contact by changing the velocity components along the collision normal.

Conceptually, one simulation step follows:

```text
Build Octree
     ↓
Compute accelerations
     ↓
Kick velocities
     ↓
Drift positions
     ↓
Detect and resolve collisions
     ↓
Rebuild Octree
     ↓
Compute new accelerations
     ↓
Kick velocities
     ↓
Next step
```

This keeps the numerical simulation independent from the rendering code.

---

### Graphics

The **Graphics system** turns the current physical state into a real-time 3D visualization.

The renderer uses **OpenGL 3.3 Core**, with **GLFW** for the window and input, **GLAD** for loading OpenGL functions, **GLM** for graphics mathematics, and **GLSL shaders** for the visual appearance of the scene.

The central **Renderer** draws the bodies in three-dimensional space and coordinates the camera, shaders, adn lightning. Stars are rendered as **light-emitting objects**, while planets and other bodies use their configured colorss.

The **camera system** supports three-dimensional movement and mouse-based rotation. Movement speed, mouse sensitivity, initial position, and render distance are configurable through `config.json`.

The **lighting system** uses a spatial grid to find relevant nearby stars instead of evaluating every light against every rendered body. It supports effects such as **distance attenuation, emissive stars, and ambient lighting**. These calculations are intended to provide a convincing real-time visualization rather than a physically exact model of stellar radiation.

---

### Main Application

The **application layer** coordinates configuration, data loading, physics, graphics, input, and the main loop.

At startup, it loads `config.json` and the selected CSV dataset, creates the simulation bodies, initializes the physics and graphics systems, and then enters the main loop:

```text
Start application
      ↓
Load config.json
      ↓
Load CSV dataset
      ↓
Create simulation bodies
      ↓
Initialize physics
      ↓
Initialize window and renderer
      ↓
┌───────────────────────────┐
│         Main loop         │
│                           │
│  Process input            │
│        ↓                  │
│  Advance physics          │
│        ↓                  │
│  Render current state     │
└───────────────────────────┘
      ↓
End of the simulation
```

Main acts primarily as a **coordinator**: the physics system handles the simulation, while the graphics system handles rendering.

---

### Native and Web versions

The native and web versions share the same **C++ simulation code and overall architecture**. The main difference is the platform layer used to execute and render the application.

The native version uses **OpenGL** through the desktop graphics stack. The web version is compiled with **Emscripten** into **WebAssembly**, with the rendering layer running through **WebGL**.

The web version does not require a separate physics implementation: the same gravitational calculations, Barnes-Hut structure, numerical integration, collision handling, body representation, and application logic remain in C++.



## Physical laws and methods
The simulation is based on:

1. [Newton's laws of motion](#newtons-laws-of-motion)
2. [Newton's law of universal gravitation](#newtons-law-of-universal-gravitation)
3. [Gravitational softening](#gravitational-softening)
4. [Superposition principle](#superposition-principle)
5. [Barnes-Hut algorithm](#barnes-hut-algorithm)
6. [Octree spatial partitioning](#octree-spatial-partitioning)
7. [Leapfrog integration](#leapfrog-integration)
8. [Collision response](#collision-response)

---

### Newton's laws of motion

The motion of each body is described by Newton's second law:

$$
\vec{F} = m\vec{a}
$$

Therefore:

$$
\vec{a} = \frac{\vec{F}}{m}
$$

Newton's third law states that the forces between two interacting bodies are equal and opposite:

$$
\vec{F}_{a\rightarrow b} = -\vec{F}_{b\rightarrow a}
$$

---

### Newton's law of universal gravitation

Two bodies with masses $m_a$ and $m_b$ separated by a distance $r$ exert a gravitational force:

$$
F = G\frac{m_a m_b}{r^2}
$$

where $G$ is the gravitational constant.

The position of a body is represented by:

$$
\vec{r}_i = (x_i, y_i, z_i)
$$

For two bodies $a$ and $b$, the relative position is:

$$
\vec{r}_{ab} = \vec{r}_b-\vec{r}_a
$$

The distance between them is:

$$
r_{ab} = \sqrt{(x_b-x_a)^2+(y_b-y_a)^2+(z_b-z_a)^2}
$$

The corresponding unit vector is:

$$
\hat{r}_{ab} = \frac{\vec{r}_{ab}}{r_{ab}}
$$

The gravitational force acting on body $a$ due to body $b$ is:

$$
\vec{F}_{a\leftarrow b} = G\frac{m_a m_b}{r_{ab}^2}\hat{r}_{ab}
$$

Using $\vec{F}=m\vec{a}$, the resulting acceleration is:

$$
\vec{a}_{a\leftarrow b} = G\frac{m_b}{r_{ab}^2}\hat{r}_{ab}
$$

### Gravitational softening

When two bodies become extremely close, the inverse-square law can produce very large accelerations.

Gravity Simulator introduces a softening parameter $\epsilon$ to improve numerical stability:

$$
\vec{a}_{a\leftarrow b} = Gm_b\frac{\vec{r}_{ab}}{\left(|\vec{r}_{ab}|^2+\epsilon^2\right)^{3/2}}
$$

where $\epsilon$ is the `softening` parameter from `config.json`.

Softening is a **numerical regularization** and does not represent an additional physical force.

---

### Superposition principle

The acceleration acting on a body is the sum of the gravitational contributions from every other body:

$$
\vec{a}_i = \sum_{j\neq i}\vec{a}_{i\leftarrow j}
$$

Using the softened formulation, the total acceleration is:

$$
\vec{a}_i = \sum_{j\neq i} Gm_j\frac{\vec{r}_j-\vec{r}_i}{\left(|\vec{r}_j-\vec{r}_i|^2+\epsilon^2\right)^{3/2}}
$$

---

### Barnes-Hut algorithm

The **Barnes-Hut algorithm** approximates the gravitational influence of sufficiently distant groups of bodies. Instead of calculating every individual interaction, a distant group can be represented by its total mass and center of mass.

The total mass of a group is:

$$
M = \sum_i m_i
$$

Its center of mass is:

$$
\vec{r}_{CM} = \frac{1}{M}\sum_i m_i\vec{r}_i
$$

A sufficiently distant group can then be treated as a single effective body:

$$
(M,\vec{r}_{CM})
$$

The approximate acceleration produced by the group is:

$$
\vec{a} \approx GM\frac{\vec{r}_{CM}-\vec{r}}{\left(|\vec{r}_{CM}-\vec{r}|^2+\epsilon^2\right)^{3/2}}
$$

This replaces many individual calculations with one approximation.

---

### Octree spatial partitioning

Because the simulation is three-dimensional, Barnes-Hut is implemented using an **Octree**. An Octree recursively divides a cubic region of space into **eight child regions**.

Each node stores the aggregated mass and center of mass of the bodies contained within it. A node is subdivided when the number of bodies it contains exceeds the configured `capacity`, unless it reaches the configured `minimumHalfWidth`.

This gives dense regions greater spatial resolution while allowing distant regions to remain grouped.

---

### Barnes-Hut opening criterion

When traversing the Octree, a node can be approximated if it is sufficiently far from the body being evaluated.

The Barnes-Hut criterion is:

$$
\frac{s}{d}<\theta
$$

where:

- $s$ is the size of the node.
- $d$ is the distance between the body and the node's center of mass.
- $\theta$ is the Barnes-Hut opening parameter.

A smaller $\theta$ generally produces greater accuracy at the cost of more computation:

$$
\theta\downarrow \quad\Rightarrow\quad \text{accuracy}\uparrow \quad\text{computation}\uparrow
$$

A larger $\theta$ produces more aggressive approximations:

$$
\theta\uparrow \quad\Rightarrow\quad \text{computation}\downarrow \quad\text{accuracy}\downarrow
$$

---

### Leapfrog integration

The gravitational equations determine the acceleration, while numerical integration determines the next position and velocity.

Gravity Simulator uses a **Leapfrog integrator** in **kick-drift-kick** form.

The equations of motion are:

$$
\frac{d\vec{r}}{dt}=\vec{v}
$$

$$
\frac{d\vec{v}}{dt}=\vec{a}
$$

with simulation time step $\Delta t$.

#### 1. First kick

$$
\vec{v}\left(t+\frac{\Delta t}{2}\right) = \vec{v}(t) + \frac{\Delta t}{2}\vec{a}(t)
$$

#### 2. Drift

$$
\vec{r}(t+\Delta t) = \vec{r}(t) + \Delta t\vec{v}\left(t+\frac{\Delta t}{2}\right)
$$

#### 3. Recalculate acceleration

After the bodies move, the Octree is rebuilt and the new accelerations are calculated:

$$
\vec{a}(t+\Delta t) = \frac{\vec{F}(t+\Delta t)}{m}
$$

#### 4. Second kick

$$
\vec{v}(t+\Delta t) = \vec{v}\left(t+\frac{\Delta t}{2}\right) + \frac{\Delta t}{2}\vec{a}(t+\Delta t)
$$

Leapfrog is a **second-order symplectic integrator**, making it suitable for long-running gravitational simulations.

---

### Collision response

Collisions are detected from the physical size assigned to each body. Two spherical bodies are considered to be in contact when the distance between their centers is less than or equal to the sum of their radio:

$$
r_{ab} \leq R_a + R_b
$$

The collision normal points from body $a$ to body $b$:

$$
\hat{n} = \frac{\vec{r}_b-\vec{r}_a}{|\vec{r}_b-\vec{r}_a|}
$$

The relative velocity along this normal determines whether the bodies are moving towards each other. The normal component is the part that is reversed by the collision, while the tangential component remains unchanged in an ideal frictionless collision.

For a perfectly elastic collision, the normal impulse is:

$$
J = -\frac{2(\vec{v}_b-\vec{v}_a)\cdot\hat{n}}{\frac{1}{m_a}+\frac{1}{m_b}}
$$

The resulting velocities are:

$$
\vec{v}_a' = \vec{v}_a - \frac{J}{m_a}\hat{n}
$$

$$
\vec{v}_b' = \vec{v}_b + \frac{J}{m_b}\hat{n}
$$

This produces the rebound: the bodies exchange momentum along the collision normal according to their masses. A heavier body changes its velocity less, while a lighter body receives a larger change.

This collision model is an idealized spherical, frictionless response. It provides a physically meaningful rebound without attempting to model deformation, heat, fragmentation, or other complex material effects.

---

### Complete simulation step

The complete numerical process combines gravitational acceleration, Barnes-Hut, collision detection, and Leapfrog integration:

$$
\vec{a}_i = \sum_{j\neq i} Gm_j\frac{\vec{r}_j-\vec{r}_i}{\left(|\vec{r}_j-\vec{r}_i|^2+\epsilon^2\right)^{3/2}}
$$

followed by:

$$
\vec{v}_{i,\frac12} = \vec{v}_i+\frac{\Delta t}{2}\vec{a}_i
$$

$$
\vec{r}_i' = \vec{r}_i+\Delta t\vec{v}_{i,\frac12}
$$

After the positions are updated, collisions are detected and resolved using the collision response described above. The new accelerations are then calculated from the updated positions:

$$
\vec{a}_i' = \vec{a}(\vec{r}_i')
$$

Finally, the second Leapfrog kick updates the velocity:

$$
\vec{v}_i' = \vec{v}_{i,\frac12}+\frac{\Delta t}{2}\vec{a}_i'
$$

The acceleration calculation uses the Barnes-Hut Octree instead of evaluating every pair directly.

---

### Physical model summary

The **physical equations** determine how bodies interact, **Barnes-Hut** approximates those interactions efficiently, **Leapfrog** advances the system through time, and the collision response handles contact between bodies.

#### Limitations of the physical model

- Gravity Simulator models a simplified classical Newtonian gravitational system. It is intended primarily as an educational and real-time simulation rather than a precision astronomical simulator, so it doesn't include detailed astrophysical processes like relativity, quantum mehcnaics, electromagnetism, radiation, ...
- The collision model treats bodies as rigid spheres and uses an idealized frictionless rebound. It does not model deformation, heat, fragmentation, or material-specific collision behavior.
- The simulation uses configurable units and values, so the configured gravitational constant does not necessarily correspond to the physical international system value of $G$.
- The goal is to provide a clear and efficient implementation of the classical N-body gravitational problem while learning numerical simulation, spatial data structures, C++ programming, collision handling, and real-time 3D graphics.
