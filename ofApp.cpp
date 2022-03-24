#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 2;
	float theta_deg_step = 8;

	float R = 250;
	float base_r = R * 0.25;
	float r = 0;

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;
			
			r = ofMap(ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5) * 0.006, ofGetFrameNum() * 0.03)), 0, 1, base_r * 0.2, base_r * 2);
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));

			r = ofMap(ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5) * 0.006, ofGetFrameNum() * 0.03)), 0, 1, base_r * 0.2, base_r * 2);
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));

			r = ofMap(ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5) * 0.006, ofGetFrameNum() * 0.03)), 0, 1, base_r * 0.2, base_r * 2);
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			r = ofMap(ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5) * 0.006, ofGetFrameNum() * 0.03)), 0, 1, base_r * 0.2, base_r * 2);
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));


			this->face.addVertices(vertices);
			this->line.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			this->line.addIndex(index + 0); this->line.addIndex(index + 1);
			this->line.addIndex(index + 1); this->line.addIndex(index + 3);
			this->line.addIndex(index + 0); this->line.addIndex(index + 2);
			this->line.addIndex(index + 2); this->line.addIndex(index + 3);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(255);
	this->line.draw();

	ofSetColor(0);
	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}