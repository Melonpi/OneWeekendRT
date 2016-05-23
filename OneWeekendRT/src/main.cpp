#include "stb_image_write.h"
#include "Sphere.h"
#include "HitableList.h"

using namespace ow;

#include <iostream>

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int RGBA = 4;
typedef unsigned char byte;

Vec3 color(const Ray& ray, const Hitable& scene)
{
	HitInfo hit_info;
	if (scene.hit(ray, 0, REAL_MAX, hit_info))
	{
		return 0.5f * Vec3(hit_info.normal.x + 1, hit_info.normal.y + 1, hit_info.normal.z + 1);
	}else{
		Vec3 unit_direction = make_unit(ray.direction);
		real t = 0.5f * (unit_direction.y + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}

int main(int argc, const char* argv[])
{
	Vec3 v;
	int w = WIDTH;
	int h = HEIGHT;
	std::unique_ptr<byte> data = std::unique_ptr<byte>(new byte[w * h * RGBA]);

	Vec3 lower_left_corner(-8.0, -4.5, -1.0);
	Vec3 horizontal(16.0, 0.0, 0.0);
	Vec3 vertical(0.0, 9.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	HitableList scene;
	scene.add( std::unique_ptr<Sphere>(new Sphere(Vec3(0, 0, -1), 0.5)) );
	scene.add( std::unique_ptr<Sphere>(new Sphere(Vec3(0, -100.5, -1), 100)) );
	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
		{
			real u = real(i) / real(w);
			real v = real(j) / real(h);
			Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);

			Vec3 p = ray.pointAtParameter(2.0);
			Vec3 col = color(ray, scene);
			data.get()[(h-j-1)*w*RGBA + i*RGBA    ] = int(col.r * 255.99);
			data.get()[(h-j-1)*w*RGBA + i*RGBA + 1] = int(col.g * 255.99);
			data.get()[(h-j-1)*w*RGBA + i*RGBA + 2] = int(col.b * 255.99);
		}
	}
	if (stbi_write_png("output.png", WIDTH, HEIGHT, RGBA, data.get(), 0) == 0)
	{
		std::cout << "write png file failed.\n";
	}
	else {
		std::cout << "write png file as output.png\n";
	}

	return 0;
}