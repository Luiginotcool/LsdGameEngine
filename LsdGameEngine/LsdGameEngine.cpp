// LsdGameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LsdGameEngine.h"
#include "LsdMath.h"
#undef main
#define PI 3.141592653

namespace LsdGameEngine {

	Camera::Camera() {
		pos = Vector3(0, 0, 0);
		heading = 0;
		pitch = 0;
		focalLen = 1;
	}

	Camera::Camera(Vector3 _pos) {
		pos = _pos;
		heading = 0;
		pitch = 0;
		focalLen = 0;
	}

	Vector3 Camera::focalPoint() {
		return pos + focalLen * Vector3(sin(PI/2 - pitch) * sin(heading), cos(PI/2 - pitch), sin(PI/2 - pitch) * cos(heading));
	}

	int Colour::toInt(Colour colour) {
		return colour.r * 255 * 255 + colour.g * 255 + colour.b;
	}

	Colour Colour::toColour(int colour) {
		return Colour(colour & 0xFF0000 >> 16, colour & 0x00FF00 >> 8, colour & 0x0000FF);
	}

	Colour Colour::BLACK = Colour(0, 0, 0);
	Colour Colour::WHITE = Colour(255, 255, 255);
	Colour Colour::RED = Colour(255, 0, 0);
	Colour Colour::GREEN = Colour(0, 255, 0);
	Colour Colour::BLUE = Colour(0, 0, 255);
	Colour Colour::YELLOW = Colour(255, 255, 0);
	Colour Colour::MAGENTA = Colour(255, 0, 255);
	Colour Colour::CYAN = Colour(0, 255, 255);

	Colour::Colour() {
		r = 0;
		g = 0;
		b = 0;
	}

	Colour::Colour(int _r, int _g, int _b) {
		r = _r;
		g = _g;
		b = _b;
	}


	Polygon::Polygon() {
		numSides = 0;
		colour = Colour::WHITE;
	}

	Polygon::Polygon(std::vector<Vector3> _vertexArrray) {
		numSides = _vertexArrray.size();
		vertexArray = _vertexArrray;
		colour = Colour::WHITE;
	}

	Polygon::Polygon(Vector3 v1, Vector3 v2, Vector3 v3) {
		numSides = 3;
		vertexArray.push_back(v1);
		vertexArray.push_back(v2);
		vertexArray.push_back(v3);
		colour = Colour::WHITE;
	}

	Polygon::Polygon(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) {
		numSides = 4;
		vertexArray.push_back(v1);
		vertexArray.push_back(v2);
		vertexArray.push_back(v3);
		vertexArray.push_back(v4);
		colour = Colour::WHITE;
	}

	Polygon Polygon::translate(Vector3 vector) {
		Polygon newPolygon = *this;
		for (int i = 0; i < newPolygon.vertexArray.size(); i++) {
			newPolygon.vertexArray[i] = newPolygon.vertexArray[i] + vector;
		}
		return newPolygon;
	}

	Polygon Polygon::scale(float factor) {
		Polygon newPolygon = *this;
		for (int i = 0; i < newPolygon.vertexArray.size(); i++) {
			newPolygon.vertexArray[i] = newPolygon.vertexArray[i] * factor;
		}
		return newPolygon;
	}

	std::string Polygon::toString() {
		std::string output = "Number of sides: " + numSides;
		output.append("\n");
		for (int i = 0; i < numSides; i++) {
			output.append(vertexArray[i].toString());
			output.append("\n");
		}
		return output;
	}


	Polygon2d::Polygon2d() {
		numSides = 0;
	}

	Polygon2d::Polygon2d(std::vector<Vector2> _vertexArray) {
		numSides = _vertexArray.size();
		vertexArray = _vertexArray;
	}

	Polygon2d::Polygon2d(Vector2 v1, Vector2 v2, Vector2 v3) {
		numSides = 3;
		vertexArray.push_back(v1);
		vertexArray.push_back(v2);
		vertexArray.push_back(v3);
	}

	Polygon2d::Polygon2d(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4) {
		numSides = 4;
		vertexArray.push_back(v1);
		vertexArray.push_back(v2);
		vertexArray.push_back(v3);
		vertexArray.push_back(v4);
	}

	std::vector<Polygon2d> Polygon2d::toTriangles() {
		std::vector<Polygon2d> polygons;
		if (vertexArray.size() > 2) {
			for (int i = 0; i < vertexArray.size() - 2; i++) {
				polygons.push_back(Polygon2d(vertexArray[0], vertexArray[i + 1], vertexArray[i + 2]));
			}
		}
		return polygons;
	}

	Polygon2d Polygon2d::translate(Vector2 vector) {
		Polygon2d newPolygon = *this;
		for (int i = 0; i < newPolygon.vertexArray.size(); i++) {
			newPolygon.vertexArray[i] = newPolygon.vertexArray[i] + vector;
		}
		return newPolygon;
	}

	Polygon2d Polygon2d::scale(float factor) {
		Polygon2d newPolygon = *this;
		for (int i = 0; i < newPolygon.vertexArray.size(); i++) {
			newPolygon.vertexArray[i] = newPolygon.vertexArray[i] * factor;
		}
		return newPolygon;
	}

	std::string Polygon2d::toString() {
		std::string output = "Number of sides: " + numSides;
		output.append("\n");
		for (int i = 0; i < numSides; i++) {
			output.append(vertexArray[i].toString());
			output.append("\n");
		}
		return output;
	}


	Graphics::Graphics(int _width, int _height, float _scale) {
		width = _width;
		height = _height;
		scale = _scale;
		window = SDL_CreateWindow("LsdGameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, 0);
	}

	Graphics::Graphics() {
		Graphics(500, 500, 1);
	}

	void Graphics::putPixel(int x, int y, Colour colour) {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		SDL_RenderDrawPoint(renderer, x, y);
	}

	void Graphics::putPixel(int x, int y) {
		Colour colour = Colour::WHITE;
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		SDL_RenderDrawPoint(renderer, x, y);
	}

	void Graphics::line(int x1, int y1, int x2, int y2, Colour colour) {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}

	void Graphics::line(int x1, int y1, int x2, int y2) {
		Colour colour = Colour::WHITE;
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}

	void Graphics::drawPoly(Polygon2d polygon, Colour colour) {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		for (int i = 0; i < polygon.vertexArray.size()-1; i++) {
			SDL_RenderDrawLine(renderer, polygon.vertexArray[i].x, polygon.vertexArray[i].y, polygon.vertexArray[i + 1].x, polygon.vertexArray[i + 1].y);
		}
		SDL_RenderDrawLine(renderer, polygon.vertexArray.back().x, polygon.vertexArray.back().y, polygon.vertexArray[0].x, polygon.vertexArray[0].y);
	}

	void Graphics::drawPoly(Polygon2d polygon) {
		Colour colour = Colour::WHITE;
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		for (int i = 0; i < polygon.vertexArray.size() - 1; i++) {
			SDL_RenderDrawLine(renderer, polygon.vertexArray[i].x, polygon.vertexArray[i].y, polygon.vertexArray[i + 1].x, polygon.vertexArray[i + 1].y);
		}
		SDL_RenderDrawLine(renderer, polygon.vertexArray.back().x, polygon.vertexArray.back().y, polygon.vertexArray[0].x, polygon.vertexArray[0].y);
	}

	void Graphics::fillPoly(Polygon2d polygon, Colour colour) {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);

		// Split polygon into triangles and then fill each one separately
		std::vector<Polygon2d> triangles = polygon.toTriangles();

		for (int i = 0; i < triangles.size(); i++) {
			fillTriangle(triangles[i]);
		}
	}

	void Graphics::fillPoly(Polygon2d polygon) {
		Colour colour = Colour::WHITE;
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);

		// Split polygon into triangles and then fill each one separately
		std::vector<Polygon2d> triangles = polygon.toTriangles();

		for (int i = 0; i < triangles.size(); i++) {
			fillTriangle(triangles[i]);
		}
	}
	
	void Graphics::fillTriangle(Polygon2d polygon) {
		Vector2 v1 = polygon.vertexArray[0].round();
		Vector2 v2 = polygon.vertexArray[1].round();
		Vector2 v3 = polygon.vertexArray[2].round();

		// Check if triangle has a flat top or bottom
		if (v1.y == v2.y || v1.y == v3.y || v2.y == v3.y) {

			if (v1.y == v2.y) {
				if (v1.y < v3.y) { // flat top
					fillFlatTop(v3, v1, v2);
				}
				else { // flat bottom
					fillFlatBottom(v3, v1, v2);
				}
			}

			if (v1.y == v3.y) {
				if (v1.y < v2.y) { // flat top
					fillFlatTop(v2, v1, v3);
				}
				else { // flat bottom
					fillFlatBottom(v2, v1, v3);
				}
			}

			if (v2.y == v3.y) {
				if (v2.y < v1.y) { // flat top
					fillFlatTop(v1, v2, v3);
				}
				else { // flat bottom
					fillFlatBottom(v1, v2, v3);
				}
			}
		}
		else {
			// Split triangles
			// Find top middle and bottom vertex
			Vector2 temp;
			if (v1.y > v2.y) {
				temp = v1;
				v1 = v2;
				v2 = temp;
			}
			if (v2.y > v3.y) {
				temp = v2;
				v2 = v3;
				v3 = temp;
			}
			if (v1.y > v2.y) {
				temp = v1;
				v1 = v2;
				v2 = temp;
			}
			// v1 = top, v3 = bottom
			Vector2 v4 = Vector2((v1 - v3).x / (v1 - v3).y * (v2.y - v1.y) + v1.x, v2.y);

			// Fill new triangles
			fillTriangle(Polygon2d(v1, v2, v4));
			fillTriangle(Polygon2d(v2, v3, v4));
		}
	}

	void Graphics::fillFlatTop(Vector2 v1, Vector2 v2, Vector2 v3) {
		float s1 = (v2 - v1).x / (v2 - v1).y;
		float s2 = (v3 - v1).x / (v3 - v1).y;
		int x1 = v2.x;
		int x2 = v3.x;
		for (int y = v2.y; y < v1.y; y++) {
			SDL_RenderDrawLine(renderer, x1, y, x2, y);
			x1 += s1;
			x2 += s2;
		}
	}

	void Graphics::fillFlatBottom(Vector2 v1, Vector2 v2, Vector2 v3) {
		float s1 = (v2 - v1).x / (v2 - v1).y;
		float s2 = (v3 - v1).x / (v3 - v1).y;
		int x1 = v2.x;
		int x2 = v3.x;
		for (int y = v2.y; y > v1.y; y--) {
			SDL_RenderDrawLine(renderer, x1, y, x2, y);
			x1 -= s1;
			x2 -= s2;
		}
	}

	void Graphics::update() {
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	Vector3 Renderer::projectVertex(Vector3 vertex, Camera camera) {
		//// Voodoo maths magic, see notes in sharon's book
		//// xz plane
		//Vector2 vertexXZ = Vector2(vertex.x, vertex.z);
		//Vector2 cameraXZ = Vector2(camera.pos.x, camera.pos.z);
		//float phi = atan((vertexXZ - cameraXZ).y / (vertexXZ - cameraXZ).x); // angle between x-axis and line of sight
		//if (phi < 0) {
		//	phi += 3.1415926;
		//}
		//float d = (vertexXZ - cameraXZ).mag(); // distance between the vertex and the camera
		//float h = d * cos(camera.heading - phi); // len of line along heading that makes r angle tri with Cam-Vertx as hyp
		//Vector2 Ixz = cameraXZ + (camera.focalLen / h) * (vertexXZ - cameraXZ); // Projection coords using similar triangles
		//
		//// xy plane
		//Vector2 vertexXY = Vector2(vertex.x, vertex.y);
		//Vector2 cameraXY = Vector2(camera.pos.x, camera.pos.y);
		//phi = atan((vertexXY - cameraXY).y / (vertexXY - cameraXY).x); // angle between x-axis and line of sight
		//if (phi < 0) {
		//	phi += 3.1415926;
		//}
		//d = (vertexXY - cameraXY).mag(); // distance between the vertex and the camera
		//h = d * cos(camera.pitch - phi); // len of line along pitch that makes r angle tri with Cam-Vertx as hyp
		//Vector2 Ixy = cameraXY + (camera.focalLen / h) * (vertexXY - cameraXY); // Projection coords using similar triangles
		////return camera.pos + (camera.focalLen / ((vertex - camera.pos).mag() * cos(camera.heading - atan((vertex - camera.pos).y / (vertex - camera.pos).x)))) * (vertex - camera.pos);
		////return Vector3(Ixy.x, Ixy.y, Ixz.y);


		//Vector3 vertexYZ = Vector3(0, vertex.y, vertex.x);
		//Vector3 cameraYZ = Vector3(0, camera.pos.y, camera.pos.x);
		//phi = atan((vertexYZ - cameraYZ).y / (vertexYZ - cameraYZ).z);
		//d = (vertexYZ - cameraYZ).mag();
		//h = d * cos(camera.pitch - phi);
		//Vector3 Iyz = cameraYZ + (camera.focalLen / h) * (vertexYZ - cameraYZ);
		//return Vector3(Ixy.x, Iyz.y, Iyz.z);
		Vector3 focalPoint = camera.pos + camera.focalLen * Vector3(sin(PI/2 - camera.pitch) * sin(camera.heading), cos(PI/2 - camera.pitch), sin(PI/2 - camera.pitch) * cos(camera.heading));
		std::cout << focalPoint.toString();
		std::cout << camera.heading;
		Vector3 normal = (focalPoint - camera.pos).normalize();
		float t = (camera.pos - focalPoint).dot(normal) / (vertex - camera.pos).dot(normal);
		if (t < 0) {
			std::cout << "Behind";
			t = 0;
		}
		Vector3 projectedVertex = camera.pos + t * (vertex - camera.pos);
		return projectedVertex;
	}

	Polygon2d Renderer::transformVertexPlane(std::vector<Vector3> vertecies, Camera camera) {
		Vector3 focalPoint = camera.pos + camera.focalLen * Vector3(sin(PI / 2 - camera.pitch) * sin(camera.heading), cos(PI / 2 - camera.pitch), sin(PI / 2 - camera.pitch) * cos(camera.heading));
		Vector3 normal = focalPoint - camera.pos;
		std::vector<Vector2> newVertecies;
		Vector3 a = vertecies[0];
		Vector3 n = normal.normalize();
		Vector3 xAxis = a - focalPoint;
		Vector3 yAxis = normal.cross(xAxis);
		//Vector3 Z = Vector3(u.z, v.z, n.z);
		for (int i = 0; i < vertecies.size(); i++) {
			Vector3 v = vertecies[i];
			Vector2 newV = Vector2((v - focalPoint).dot(xAxis), (v - focalPoint).dot(yAxis));
			newVertecies.push_back(newV);
		}
		return Polygon2d(newVertecies);
	}

	void Renderer::renderPolygon(Graphics graphics, Polygon polygon, Camera camera) {
		std::vector<Vector3> projectedVertecies;
		for (int i = 0; i < polygon.numSides; i++) {
			projectedVertecies.push_back(projectVertex(polygon.vertexArray[i], camera));
		}
		Polygon2d transformedPoly = transformVertexPlane(projectedVertecies, camera);
		transformedPoly = transformedPoly.scale(graphics.scale).translate(Vector2(graphics.width / 2, graphics.height / 2));
		std::cout << transformedPoly.toString();
		graphics.fillPoly(transformedPoly, polygon.colour);
	}

	void Renderer::renderWireframe(Graphics graphics, Polygon polygon, Camera camera) {
		std::vector<Vector3> projectedVertecies;
		for (int i = 0; i < polygon.numSides; i++) {
			projectedVertecies.push_back(projectVertex(polygon.vertexArray[i], camera));
		}
		Polygon2d transformedPoly = transformVertexPlane(projectedVertecies, camera);
		transformedPoly = transformedPoly.scale(graphics.scale).translate(Vector2(graphics.width / 2, graphics.height / 2));
		std::cout << transformedPoly.toString();
		graphics.drawPoly(transformedPoly, polygon.colour);
	}
}

int main() {
	LsdGameEngine::Graphics graphics(500, 500, 20);
	LsdGameEngine::Polygon poly = LsdGameEngine::Polygon(Vector3(-1, -1, -1)*1, Vector3(-1, 1, -1)*1, Vector3(1, 1, -1)*1, Vector3(1, -1, -1)*1);
	LsdGameEngine::Polygon floor = LsdGameEngine::Polygon(Vector3(-1, 1, -1) * 1, Vector3(-1, 1, 1) * 1, Vector3(1, 1, 1) * 1, Vector3(1, 1, -1) * 1);
	poly.colour = LsdGameEngine::Colour::RED;
	floor.colour = LsdGameEngine::Colour::BLUE;
	LsdGameEngine::Camera camera = LsdGameEngine::Camera();
	camera.pos = Vector3(0, 0, 1);
	camera.heading = 3.14159265/2;
	LsdGameEngine::Polygon2d poly2d = LsdGameEngine::Polygon2d(Vector2(270, 230), Vector2(230, 230), Vector2(230, 270), Vector2(270, 270));
	//graphics.fillPoly(poly2d);
	//graphics.fillPoly(LsdGameEngine::Polygon2d(Vector2(230, 270), Vector2(270, 270), Vector2(270, 230)));

	bool quit = false;
	SDL_Event event;
	

	while (!quit) {
		LsdGameEngine::Renderer::renderWireframe(graphics, poly, camera);
		//LsdGameEngine::Renderer::renderWireframe(graphics, floor, camera);

		Vector3 focalPoint = (camera.focalPoint() * graphics.scale + Vector3(graphics.width/2, graphics.height/2, 0));
		Vector3 camPos = (camera.pos * graphics.scale + Vector3(graphics.width / 2, graphics.height / 2, 0));

		graphics.line(camPos.x, camPos.z, focalPoint.x, focalPoint.z);
		graphics.line(camPos.x, camPos.y, focalPoint.x, focalPoint.y);
		std::cout << camPos.toString();
		graphics.update();

		SDL_WaitEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT: camera.heading -= 0.1; break;
			case SDLK_RIGHT: camera.heading += 0.1; break;
			case SDLK_UP: camera.pos += Vector3(0, 0, 0.1); break;
			case SDLK_DOWN: camera.pos += Vector3(0, 0, -0.1); break;
			default:
				break;
			}
		default:
			break;
		}
	}
}