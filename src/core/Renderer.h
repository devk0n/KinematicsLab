#ifndef RENDERER_H
#define RENDERER_H


#include <src/physics/PhysicsEngine.h>

class Renderer {
public:
	bool initialize();

	void beginFrame() const;

	void drawAxes(float x, float y, float angle, float scale) const;

private:
	float m_clearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	bool m_initialized = false;
};


#endif // RENDERER_H
