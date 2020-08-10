#include <Particle.hpp>

// Constructor
Particle::Particle(float x, float y, float radius,float charge) {

	mCharge = charge;
	mHeld = 0;
	mX = x;
	mY = y;
	mVelX = 0;
	mVelY = 0;
	mAccX = 0;
	mAccY = 0;
	mRadius = radius;
	mMass = PI * radius * radius * DENSITY;
	//mMass = PI * 20 * 20 * DENSITY;
}



// Copy constructor
Particle::Particle(const Particle& p) {

	mCharge = p.mCharge;
	mHeld = p.mHeld;
	mX = p.mX;
	mY = p.mY;
	mVelX = p.mVelX;
	mVelY = p.mVelY;
	mAccX = p.mAccX;
	mAccY = p.mAccY;
	mRadius = p.mRadius;
	mMass = p.mMass;
	for(int i = 0; i < 3 * (CIRCLERESOLUTION - 2); i++) {
		mIndices[i] = p.mIndices[i];
	}
	for(int i = 0; i < 2 * CIRCLERESOLUTION; i++) {
		mPoints[i] = p.mPoints[i];
	}
}

// Calculate and apply forces between self and another Particle
void Particle::applyForces(Particle& p) {
	// If the particle doesnt have a charge there is no force

	if (mCharge == 0) return;

	// Figure out the distance between the particles
	float dx = mX - p.mX;
	float dy = mY - p.mY;
	double dist = sqrt(dx * dx + dy * dy);


	// Particles are inside of eachother
	//if (dist < (mRadius + p.mRadius)) return;
}

// Calculate and apply collisions between self and another Particle
void Particle::collide(Particle& p) {
	// Figure out distance between particles
	float dx = mX - p.mX;
	float dy = mY - p.mY;
	// 50% faster
	if(dx > mRadius + p.mRadius || dy > mRadius + p.mRadius) return;

	double dist = sqrt(dx * dx + dy * dy);

	// if not overlapping, dont collide
	if (dist > mRadius + p.mRadius) return;

	// Calculate how much the particles have to move
	double overlap = dist - (mRadius + p.mRadius);
	float xOff = overlap * 0.5 * dx / dist;
	float yOff = overlap * 0.5 * dy / dist;

	// Move particles to account for collision
	mX -= xOff;
	mY -= yOff;
	p.mX += xOff;
	p.mY += yOff;

	//Do dynamic collisions
	dx = mX - p.mX;
	dy = mY - p.mY;
	dist = sqrt(dx * dx + dy * dy);

	// Normal Vector
	float nx = -dx / dist;
	float ny = -dy / dist;

	// Dot Product of subtracted Vel. and normal
	float dProd = (mVelX - p.mVelX) * nx + (mVelY - p.mVelY) * ny;

	// Impulse
	float Jn = (mMass * p.mMass) / (mMass + p.mMass) * (1 + ELASTICITY) * (dProd);

	mVelX -= Jn / mMass * nx;
	mVelY -= Jn / mMass * ny;

	p.mVelX += Jn / p.mMass * nx;
	p.mVelY += Jn / p.mMass * ny;
}

bool Particle::contains(double x, double y){
	return ((mX-x) * (mX-x) + (mY-y) * (mY-y) < (mRadius * mRadius));
}

void Particle::tick(double deltaTimeS, double delX, double delY) {
	if(mHeld) {
		mX = delX + mGrabX;
		mY = delY + mGrabY;
		mVelX = 0;
		mVelY = 0;
		mAccX = 0;
		mAccY = 0;
		return;
	}
	mAccX -= mVelX * FRICTION;
	mAccY -= mVelY * FRICTION;
	mVelX += mAccX * deltaTimeS;
	mVelY += mAccY * deltaTimeS;
	mX += mVelX * deltaTimeS;
	mY += mVelY * deltaTimeS;
	mAccX = 0;
	mAccY = 0;
}
