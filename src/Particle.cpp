//
//  Particle.cpp
//  particlesAdvanced
//
//  Created by Jonathan Beilin on 11/6/17.
//

#include "Particle.hpp"

void Particle::reset() {
	position.x = ofRandomWidth();
	position.y = ofRandomHeight();

	velocity.x = ofRandom(-1.9, 1);
	velocity.y = ofRandom(-1.9, 1.9);

	drag = ofRandom(0.1, 0.01);

	force = ofPoint(0, 0);
}

void Particle::update() {
	if (isAttracting) {
		// Get mouse coords, save to
		// attractPoint
		ofPoint attractPoint = ofPoint(ofGetMouseX(), ofGetMouseY());

		// calculate force
		// then normalize it
		force = attractPoint - position;
		force.normalize();

		// apply drag to velocity
		// apply force to velocity
		velocity *= drag;
		velocity += force * 0.9;
	} else {
		ofPoint repulsePoint = ofPoint(ofGetMouseX(), ofGetMouseY());
		force = repulsePoint - position;

		float distance = force.length();
		force.normalize();

		if (distance < 25) {
            
            //RIGHT
            if(position.x >= ofGetWidth() || position.x < 0 ||
               position.y >= ofGetHeight() || position.y < 0)
            {
                velocity += force * 0.6;
            }
            else
            {
                velocity -= force * 0.6;
            }
		}
        
	}

    if(position.x < 0) position.x = 0;
    else if(position.x >= ofGetWidth()) position.x = ofGetWidth();
    else if(position.y < 0) position.y = 0;
    else if(position.y >= ofGetHeight()) position.y = ofGetHeight();
    
	// update position
    velocity += force / 0.6;
    position += velocity;
    

}

void Particle::draw() {
	if (isAttracting) {
		ofSetColor(252, 225, ofRandom(250));
	} else {
		ofSetColor(214, 251, 252);
	}

	ofDrawCircle(position.x, position.y, ofRandom(1.0,2.0));
}

void Particle::toggleMode() {
	isAttracting = !isAttracting;
	reset();
}
