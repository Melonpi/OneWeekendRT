#include "stb_image_write.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "RNG.h"
#include "Material.h"

using namespace ow;

#include <random>
#include <iostream>

const int WIDTH = 200;
const int HEIGHT = 100;
const int SAMPLES = 500;
const int DEPTH_MAX = 50;
const int RGBA = 4;
typedef unsigned char byte;

Vec3 color(const Ray& ray, const Hitable& scene, int depth)
{
	HitInfo hit_info;
	if (scene.hit(ray, REAL_EPS, REAL_MAX, hit_info))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < DEPTH_MAX && hit_info.material->scatter(ray, hit_info, attenuation, scattered))
		{
			return attenuation * color(scattered, scene, depth + 1);
		}else {
			return Vec3(0, 0, 0);
		}
	}else {
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
	scene.add(std::unique_ptr<Sphere>(new Sphere(Vec3(0, 0, -1), 0.5f, std::shared_ptr<Material>(new Lambertian(Vec3(0.1f, 0.2f, 0.5f))))));
	scene.add(std::unique_ptr<Sphere>(new Sphere(Vec3(0, -100.5, -1), 100.f, std::shared_ptr<Material>(new Lambertian(Vec3(0.8f, 0.8f, 0.0f))))));
	scene.add(std::unique_ptr<Sphere>(new Sphere(Vec3(1, 0, -1), 0.5f, std::shared_ptr<Material>(new Dielectric(1.5f)))));
	scene.add(std::unique_ptr<Sphere>(new Sphere(Vec3(-1, 0, -1), -0.45f, std::shared_ptr<Material>(new Dielectric(1.5f)))));

	Camera camera;
	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
		{
			Vec3 col(0, 0, 0);
			for (int n = 0; n < s; ++n)
			{
				real u = real(i + RNG::rng()) / real(w);
				real v = real(j + RNG::rng()) / real(h);
				Ray ray = camera.getRay(u, v);
				col += color(ray, scene, 0);
			}
			col /= real(s);
			col = { sqrt(col.r), sqrt(col.g), sqrt(col.b) };//gamma 2
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