#include "stb_image_write.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"

using namespace ow;

#include <random>
#include <iostream>

const int WIDTH = 200;
const int HEIGHT = 100;
const int SAMPLES = 100;
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
	int s = SAMPLES;
	std::unique_ptr<byte> data = std::unique_ptr<byte>(new byte[w * h * RGBA]);

	HitableList scene;
	scene.add( std::unique_ptr<Sphere>(new Sphere(Vec3(0, 0, -1), 0.5)) );
	scene.add( std::unique_ptr<Sphere>(new Sphere(Vec3(0, -100.5, -1), 100)) );
	Camera camera;
	std::random_device rnd;
	std::mt19937_64 rne(rnd());
	std::uniform_real_distribution<real> rng(0, 1);
	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
		{
			Vec3 col(0, 0, 0);
			for (int n = 0; n < s; ++n)
			{
				real u = real(i + rng(rne)) / real(w);
				real v = real(j + rng(rne)) / real(h);
				Ray ray = camera.getRay(u, v);
				Vec3 p = ray.pointAtParameter(2.0);
				col += color(ray, scene);
			}
			col /= real(s);
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