#include "stb_image_write.h"
#include "Vec3.h"
#include "Ray.h"

using namespace ow;

#include <iostream>

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int RGBA = 4;
typedef unsigned char byte;

Vec3 color(const Ray& ray)
{
	Vec3 unit_direction = make_unit(ray.direction);
	float t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

int main(int argc, const char* argv[])
{
	Vec3 v;
	int w = WIDTH;
	int h = HEIGHT;
	byte* data = new byte[w * h * RGBA];

	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
		{
			real u = real(i) / real(w);
			real v = real(j) / real(h);
			Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);
			Vec3 col = color(ray);
			data[(h-j-1)*w*RGBA + i*RGBA    ] = int(col.r * 255.99);
			data[(h-j-1)*w*RGBA + i*RGBA + 1] = int(col.g * 255.99);
			data[(h-j-1)*w*RGBA + i*RGBA + 2] = int(col.b * 255.99);
		}
	}
	if (stbi_write_png("output.png", WIDTH, HEIGHT, RGBA, data, 0) == 0)
	{
		std::cout << "write png file failed.\n";
	}
	else {
		std::cout << "write png file as output.png\n";
	}

	delete data;
	return 0;
}