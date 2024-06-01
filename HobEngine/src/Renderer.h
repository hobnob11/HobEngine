#pragma once
#include "Walnut/Image.h"
#include "Walnut/Random.h"

#include <memory>

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render(float offset, float range);
	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }

private:
	uint32_t PerPixel(glm::vec2 coord, float offset, float range);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;
};