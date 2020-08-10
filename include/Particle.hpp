#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <cmath>
#include <Constants.hpp>


class Particle {

public:
float mCharge, mVelX, mVelY, mAccX, mAccY, mMass, mRadius, mX, mY, mGrabX, mGrabY;

unsigned int mIndices[3 * (CIRCLERESOLUTION - 2)];
float mPoints[2 * CIRCLERESOLUTION];
int mHeld;


Particle(float x, float y, float radius, float charge);
Particle(const Particle& p);
~Particle() {
};
void applyForces(Particle& p);
void collide(Particle& p);
bool contains(double x, double y);
void tick(double deltaTimeS, double delX, double delY);
};

#endif // ifndef PARTICLE_HPP
