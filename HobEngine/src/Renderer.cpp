#include "Renderer.h"


void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;
		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}


void Renderer::Render(float offset, float range)
{
	//bro if u dont know what this does
	//prayin for u bro
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			uint32_t i = y * m_FinalImage->GetWidth() + x;

			//float offsetx = m_FinalImage->GetWidth() * 0.5;
			//float offsety = m_FinalImage->GetHeight() * 0.5;
			//if (pow(x - offsetx, 2) + pow(y - offsety, 2) < pow(m_FinalImage->GetWidth() * 0.2, 2))
			//{
			//	m_ImageData[i] = Walnut::Random::UInt();
			//	m_ImageData[i] |= 0xffff00ff;
			//}
			//else
			//{
			//	m_ImageData[i] = 0xff000000;
			//}
			glm::vec2 coord = { glm::vec2(x / (float)m_FinalImage->GetWidth(), y / (float)m_FinalImage->GetHeight()) };
			coord = coord * 2.0f - 1.0f;
			m_ImageData[i] = PerPixel(coord, offset, range);
		}
	}
	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::PerPixel(glm::vec2 coord, float offset, float range)
{
	glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
	glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
	rayDirection = glm::normalize(rayDirection);
	float radius = 0.5f;

	// (bx^2 + by^2 + bz^2)t^2 + (2(axbx + ayby + azbz))t + (ax^2 + ay^2 + az^2 - r^2) = 0
	// a == ray origin (eyeball)
	// b == ray direction
	// r == radius of sphere
	// t == distance from a to sphere (if hit)

	//quadratic memes start here (-b +- sqrt(b^2-4ac) ) / 2a
	//bx^2 + by^2 + bz^2
	float a = glm::dot(rayDirection, rayDirection);
	//(2(axbx + ayby + azbz))
	float b = 2.0f * glm::dot(rayOrigin, rayDirection);
	//(ax^2 + ay^2 + az^2 - r^2)
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	//discriminant
	//b^2 - 4ac
	float discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f) //2 hits
	{
		float t = (-b + sqrt(discriminant)) / 2 * a;
		uint32_t d = (uint32_t)(((t-offset)/range)*255);
		return 0xffff00ff | (d << 8);
	}
	return 0xff000000;
}

