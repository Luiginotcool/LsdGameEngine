#pragma once
#include "LsdMath.h"
#include <vector>
#include "SDL.h"
#undef main
using namespace LsdMath;

namespace LsdGameEngine {
	class Camera {
	public:
		Vector3 pos;
		float heading;
		float pitch;
		float focalLen;

		// Constructors
		Camera();
		Camera(Vector3 _pos);

		// Returns the point on the focal plane directly in front of the camera
		Vector3 focalPoint();
	};

	class Colour {
	public:

		// Converts a colour object to an int
		static int toInt(Colour colour);

		// Converts an int to a colour object
		static Colour toColour(int colour);

		static Colour BLACK;
		static Colour WHITE;
		static Colour RED;
		static Colour GREEN;
		static Colour BLUE;
		static Colour YELLOW;
		static Colour MAGENTA;
		static Colour CYAN;


		int r;
		int g;
		int b;

		// Constructors
		Colour();
		Colour(int _r, int _g, int _b);

	};

	class Polygon {
	public:
		int numSides;
		std::vector<Vector3> vertexArray;
		Colour colour;

		// Constructors
		Polygon();
		Polygon(std::vector<Vector3> _vertexArray);
		Polygon(Vector3 v1, Vector3 v2, Vector3 v3);
		Polygon(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4);

		// Translate all vertecies of a polygon by a given vector
		Polygon translate(Vector3 vector);

		// Scales all vertecies of a polygon by a given scale factor about the origin
		Polygon scale(float factor);

		// Returns the vector as a string
		std::string toString();
	};

	class Polygon2d {
	public:
		int numSides;
		std::vector<Vector2> vertexArray;

		//Constructors
		Polygon2d();
		Polygon2d(std::vector<Vector2> _vertexArray);
		Polygon2d(Vector2 v1, Vector2 v2, Vector2 v3);
		Polygon2d(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);

		// Converts a 2d polygon to triangles
		std::vector<Polygon2d> toTriangles();

		// Translates all vertecies of a polygon by a given vector
		Polygon2d translate(Vector2 vector);

		// Scales all vertecies of a polygon by a given scale factor about the origin
		Polygon2d scale(float scale);

		// Returns the vector as a string
		std::string toString();
	};

	class Graphics {
	public:

		int width;
		int height;
		float scale;

		// Constructor
		Graphics();
		Graphics(int _width, int _height, float _scale);

		// Puts a coloured pixel at (x,y)
		void putPixel(int x, int y, Colour colour);
		void putPixel(int x, int y);

		// Draws a coloured line from (x1,y1) to (x2,y2)
		void line(int x1, int y1, int x2, int y2, Colour colour);
		void line(int x1, int y1, int x2, int y2);

		// Draws a coloured outline of a 2d polygon
		void drawPoly(Polygon2d polygon, Colour colour);
		void drawPoly(Polygon2d polygon);

		// Fills a 2d polygon with a colour
		void fillPoly(Polygon2d polygon, Colour colour);
		void fillPoly(Polygon2d polygon);

		void update();

	private:
		SDL_Renderer* renderer;
		SDL_Window* window;

		void fillTriangle(Polygon2d polygon);
		void fillFlatTop(Vector2 v1, Vector2 v2, Vector2 v3);
		void fillFlatBottom(Vector2 v1, Vector2 v2, Vector2 v3);
	};

	class Renderer {
	public:
		static void renderPolygon(Graphics graphics, Polygon polygon, Camera camera);
		static void renderWireframe(Graphics graphics, Polygon polygon, Camera camera);
	private:
		static Vector3 projectVertex(Vector3 vertex, Camera camera);
		static Polygon2d transformVertexPlane(std::vector<Vector3> vertecies, Camera camera);
	};

	//class Input {
	//public:
	//	Input();
	//	bool KEYS[322];
	//	void keyboard();

	//};
}