#include "raylib.h"
#include <iostream>

int main()
{
    const Color darkBlue = { 10, 10, 43, 255 };
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //ball.update
        BeginDrawing();
        ClearBackground(darkBlue);
        //ball.Draw();
        EndDrawing();
    }

    CloseWindow();
}

//SOURCES(papers)
// Particle-Based Fluid Simulation for Interactive Applications
//          Matthias Müller, David Charypar and Markus Gross
//          Department of Computer Science, Federal Institute of Technology Zürich(ETHZ), Switzerland

// Particle-based Viscoelastic Fluid Simulation
//          Simon Clavet, Philippe Beaudoin, and Pierre Poulin
//          LIGUM, Dept.IRO, Université de Montréal

// Smoothed Particle Hydrodynamics Techniques for the Physics Based Simulation of Fluids and Solids
//          Dan Koschier1, Jan Bender2, Barbara Solenthaler3, and Matthias Teschner4
//          University College London, UK
