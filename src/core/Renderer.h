#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

class Renderer {
public:
	bool initialize();

	void beginFrame() const;

private:
	float m_clearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	bool m_initialized = false;
};


#endif // RENDERER_H
