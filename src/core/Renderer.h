#ifndef RENDERER_H
#define RENDERER_H

#include "../shader/Shader.h"
#include <src/physics/PhysicsEngine.h>
#include <glm/glm.hpp>

class Renderer {
public:
	bool initialize();

	void beginFrame() const;

	void render(const PhysicsEngine &physicsEngine);

private:
	float m_clearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	bool m_initialized = false;
	Shader *m_shader = nullptr;
};

#endif // RENDERER_H
