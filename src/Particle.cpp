#include <ElectroSim/Particle.hpp>




// Constructor
Particle::Particle(float x, float y, float radius) {
	mHeld = 0;
	mX = x;
	mY = y;
	mVelX = 0;
	mVelY = 0;
	mAccX = 0;
	mAccY = 0;
	mRadius = radius;
	mMass = PI * radius * radius * DENSITY;
	calcIndices();
	calcPoints();
}

// Copy constructor
Particle::Particle(const Particle& p) {
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

	if (!mCharge) return;

	// Figure out the distance between the particles
	float dx = mX - p.mX;
	float dy = mY - p.mY;
	double dist = sqrt(dx * dx + dy * dy);

	// Particles are inside of eachother
	if (dist <= (mRadius + p.mRadius)) return;

	double force = K * mCharge * p.mCharge / (dist * dist);

	// Apply force to self and target particle
	mAccX += dx / dist * (force / mMass);
	mAccY += dy / dist * (force / mMass);
	p.mAccX += dx / dist * (force / p.mMass);
	p.mAccY += dy / dist * (force / p.mMass);
}

// Calculate and apply collisions between self and another Particle
void Particle::collide(Particle& p) {
	// Figure out distance between particles
	float dx = mX - p.mX;
	float dy = mY - p.mY;
	double dist = sqrt(dx * dx + dy * dy);

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

	// Do dynamic collisions

	// Yes math... indeed...
	float nx = -dx / dist;
	float ny = -dy / dist;

	float tx = -ny;
	float ty = nx;

	float dpTan1 = mVelX * tx + mVelY * ty;
	float dpTan2 = p.mVelX * tx + p.mVelY * ty;
	float dpNorm1 = mVelX * nx + mVelY * ny;
	float dpNorm2 = p.mVelX * nx + p.mVelY * ny;

	// Calculate momentums
	float m1 = (dpNorm1 * (mMass - p.mMass) + 2.0 * p.mMass * dpNorm2) / (mMass + p.mMass);
	float m2 = (dpNorm2 * (p.mMass - mMass) + 2.0 * mMass * dpNorm1) / (mMass + p.mMass);

	// Apply the collision
	mVelX = ELASTICITY * (tx * dpTan1 + nx * m1);
	mVelY = ELASTICITY * (ty * dpTan1 + ny * m1);
	p.mVelX = ELASTICITY * (tx * dpTan2 + nx * m2);
	p.mVelY = ELASTICITY * (ty * dpTan2 + ny * m2);
}

//
void Particle::calcPoints(){
	if (mRadius == 0) return;
	int index = 0;
	float step = 2*PI / CIRCLERESOLUTION;
	for(float i = 0; i < 2*PI; i += step) {
		mPoints[index] = mRadius * cos(i) + mX;
		mPoints[index + 1] = mRadius * sin(i) + mY;
		index += 2;
	}
}

void Particle::calcIndices(){
	for(int i = 0; i < CIRCLERESOLUTION - 2; i++) {
		mIndices[i * 3] = 0;
		mIndices[i * 3 + 1] = i + 1;
		mIndices[i * 3 + 2] = i + 2;
	}
}

void Particle::tick() {
	mAccX -= mVelX * FRICTION;
	mAccY -= mVelY * FRICTION;
	mVelX += mAccX;
	mVelY += mAccY;
	mX += mVelX;
	mY += mVelY;
	for(int i = 0; i < CIRCLERESOLUTION / 2; i++) {
		mPoints[i * 2] += mVelX;
		mPoints[i * 2 + 1] += mVelY;
	}
	mAccX = 0;
	mAccY = 0;
}

// Test function until implementation of graphics
void Particle::test() {
	std::cout << "X: " << mX << " " << mVelX << " " << mAccX << "\n" << "Y: " << mY << " " << mVelY << " " << mAccY << "\n\n";
}
