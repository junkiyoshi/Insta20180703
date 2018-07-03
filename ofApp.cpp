#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
	this->font.loadFont("fonts/Kazesawa-Extrabold.ttf", 50, true, false, true);
	this->font_small.loadFont("fonts/Kazesawa-Extrabold.ttf", 25, true, false, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	this->draw_ocean();
	this->draw_beach();
	
	for (int i = 0; i < 18; i++) {

		this->draw_human(ofPoint(ofRandom(ofGetWidth() * -0.5, ofGetWidth() * 0.5), ofRandom(0, ofGetHeight() * 0.5), 80));
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_ocean() {

	ofSetColor(0, 0, 139);

	std::string words = "Ocean";
	ofPoint words_size = ofPoint(this->font.stringWidth(words), this->font.stringHeight(words));
	std::vector<ofPath> paths = this->font.getStringAsPoints(words, true, false);

	for (int x = ofGetWidth() * -0.8; x < ofGetWidth() * 0.8; x += words_size.x) {

		for (int y = 0; y < ofGetHeight(); y += words_size.y) {

			ofPoint words_center(x + words_size.x / 2, y - words_size.y / 2);
			for (int p_index = 0; p_index < paths.size(); p_index++) {

				vector<ofPolyline> outline = paths[p_index].getOutline();
				std::vector<ofPoint> points;
				for (int o_index = 0; o_index < outline.size(); o_index++) {

					if (o_index > 0) {

						ofNextContour(true);
					}

					outline[o_index] = outline[o_index].getResampledBySpacing(1);
					vector<glm::vec3> vertices = outline[o_index].getVertices();
					for (int v_index = 0; v_index < vertices.size(); v_index++) {

						ofPoint point = ofPoint(vertices[v_index].x, vertices[v_index].y, vertices[v_index].z) - words_center;
						float z = ofMap(ofNoise(point.x * 0.001, point.y * 0.005 - ofGetFrameNum() * 0.01), 0, 1, 0, 80);
						points.push_back(point + ofPoint(0, 0, z));
					}
				}

				if (points.size() > 0) {

					ofBeginShape();
					ofVertices(points);
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_beach() {

	ofSetColor(232, 202, 179);

	std::string words = "Beach";
	ofPoint words_size = ofPoint(this->font.stringWidth(words), this->font.stringHeight(words));
	std::vector<ofPath> paths = this->font.getStringAsPoints(words, true, false);

	for (int x = ofGetWidth() * -0.5; x < ofGetWidth() * 0.5; x += words_size.x) {

		for (int y = ofGetHeight() * -0.5; y < 0; y += words_size.y) {

			ofPoint words_center(x + words_size.x / 2, y - words_size.y / 2);
			for (int p_index = 0; p_index < paths.size(); p_index++) {

				vector<ofPolyline> outline = paths[p_index].getOutline();
				std::vector<ofPoint> points;
				for (int o_index = 0; o_index < outline.size(); o_index++) {

					if (o_index > 0) {

						ofNextContour(true);
					}

					outline[o_index] = outline[o_index].getResampledBySpacing(1);
					vector<glm::vec3> vertices = outline[o_index].getVertices();
					for (int v_index = 0; v_index < vertices.size(); v_index++) {

						ofPoint point = ofPoint(vertices[v_index].x, vertices[v_index].y, vertices[v_index].z) - words_center;
						points.push_back(point + ofPoint(0, 0, 80));
					}
				}

				if (points.size() > 0) {

					ofBeginShape();
					ofVertices(points);
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_human(ofPoint point) {

	ofColor color;
	color.setHsb(ofRandom(255), 200, 255);
	ofSetColor(color);

	vector<string> words = {"H", "u", "m", "a", "n" };

	ofPushMatrix();
	ofTranslate(point);
	ofRotateX(270);

	for (int i = words.size() - 1; i > -1; i--) {

		this->font_small.drawString(words[i], this->font_small.stringWidth(words[i]) * -0.5, 0);

		float noise_value = ofMap(ofNoise(point.x * 0.005, point.y * 0.005, ofGetFrameNum() * 0.005), 0, 1, -5, 5);
		ofTranslate(noise_value, this->font_small.stringHeight(words[i]));
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}