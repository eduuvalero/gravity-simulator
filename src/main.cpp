#include <iostream>

#include "engine/Physics.h"
#include "engine/Body.h"


void printBody(const std::string& name, const Body& b)
{
    std::cout
        << name
        << " | id: " << b.id
        << " | alive: " << b.alive
        << " | mass: " << b.mass
        << " | radius: " << b.radius
        << " | pos: " << b.position
        << " | vel: " << b.velocity
        << "\n";
}


Body createBody(
    BodyType type,
    double mass,
    double radius,
    Vector3d position,
    Vector3d velocity
)
{
    Body b;

    b.type = type;
    b.mass = mass;
    b.radius = radius;

    b.position = position;
    b.velocity = velocity;
    b.acceleration = {0,0,0};

    return b;
}


void simulate(
    Physics& physics,
    int steps,
    double dt
)
{
    for(int i = 0; i < steps; i++)
    {
        physics.step(dt);
    }
}



int main()
{
    constexpr double dt = 0.01;



    // ==============================
    // PLANET + PLANET
    // ==============================

    std::cout << "\n=== PLANET COLLISION ===\n";

    {
        Physics physics;


        Body planet1 = createBody(
            BodyType::Planet,
            10,
            2,
            {-5,0,0},
            {5,0,0}
        );


        Body planet2 = createBody(
            BodyType::Planet,
            10,
            2,
            {5,0,0},
            {-5,0,0}
        );


        physics.addBody(&planet1);
        physics.addBody(&planet2);


        simulate(physics, 200, dt);


        printBody("Planet 1", planet1);
        printBody("Planet 2", planet2);
    }




    // ==============================
    // ASTEROID + ASTEROID
    // ==============================

    std::cout << "\n=== ASTEROID BOUNCE ===\n";

    {
        Physics physics;


        Body asteroid1 = createBody(
            BodyType::Asteroid,
            1,
            1,
            {-3,0,0},
            {5,0,0}
        );


        Body asteroid2 = createBody(
            BodyType::Asteroid,
            1,
            1,
            {3,0,0},
            {-5,0,0}
        );


        physics.addBody(&asteroid1);
        physics.addBody(&asteroid2);


        simulate(physics, 150, dt);


        printBody("Asteroid 1", asteroid1);
        printBody("Asteroid 2", asteroid2);
    }




    // ==============================
    // STAR + PLANET
    // ==============================

    std::cout << "\n=== STAR ABSORB PLANET ===\n";

    {
        Physics physics;


        Body star = createBody(
            BodyType::Star,
            1000,
            5,
            {0,0,0},
            {0,0,0}
        );


        Body planet = createBody(
            BodyType::Planet,
            10,
            2,
            {8,0,0},
            {-10,0,0}
        );


        physics.addBody(&star);
        physics.addBody(&planet);


        simulate(physics, 100, dt);


        printBody("Star", star);
        printBody("Planet", planet);
    }




    // ==============================
    // STAR + STAR
    // ==============================

    std::cout << "\n=== STAR MERGE ===\n";

    {
        Physics physics;


        Body star1 = createBody(
            BodyType::Star,
            500,
            3,
            {-5,0,0},
            {5,0,0}
        );


        Body star2 = createBody(
            BodyType::Star,
            1500,
            3,
            {5,0,0},
            {-5,0,0}
        );


        physics.addBody(&star1);
        physics.addBody(&star2);


        simulate(physics, 150, dt);


        printBody("Star 1", star1);
        printBody("Star 2", star2);
    }


    return 0;
}