#include "stb_image_write.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "RNG.h"
#include "Material.h"

#define __TBB_NO_IMPLICIT_LINKAGE 1
#include "tbb\tbb.h"
#pragma warning(disable: 588)

using namespace ow;

#include <random>
#include <iostream>
#include <chrono>

const int WIDTH = 400;
const int HEIGHT = 300;
const int SAMPLES = 1000;
const int DEPTH_MAX = 40;
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

std::unique_ptr<HitableList> make_random_scene()
{
	std::unique_ptr<HitableList> scene(new HitableList);
	std::unique_ptr<Texture> checker_texture = std::make_unique<CheckerTexture>(std::make_unique<ConstantTexture>(Vec3(0.2, 0.3, 0.1)), std::make_unique<ConstantTexture>(Vec3(0.9, 0.9, 0.9)));
	scene->add(std::make_unique<Sphere>(Vec3(0, -1000.f, 0), 1000.0f, std::make_unique<Lambertian>(std::move(checker_texture))));

	for (int i = -3; i < 3; ++i)
	{
		for (int j = -3; j < 3; ++j)
		{
			real material_seed = RNG::rng();
			Vec3 center(i + 0.9f*RNG::rng(), 0.2f, j + 0.9f*RNG::rng());
			if ((center - Vec3(4.0f, 0.2f, 0)).length() > 0.9)
			{
				if (material_seed < 0.8)//diffuse
				{
					std::unique_ptr<Texture> constant_texture = std::make_unique<ConstantTexture>(Vec3(RNG::rng()*RNG::rng(),RNG::rng()*RNG::rng(),RNG::rng()*RNG::rng()));
					scene->add(std::make_unique<MovingSphere>(center, center + Vec3(0, 0.5 * RNG::rng(), 0), 0.0, 1.0, 0.2f, std::make_unique<Lambertian>(std::move(constant_texture))));
				}
				else if (material_seed < 0.95)//metal
				{
					scene->add(std::make_unique<Sphere>(center, 0.2f, std::make_unique<Metal>(Vec3(0.5f*(1 + RNG::rng()), 0.5f*(1 + RNG::rng()), 0.5f*(1 + RNG::rng())), 0.5f*RNG::rng())));
				}
				else {//glass
					scene->add(std::make_unique<Sphere>(center, 0.2f, std::make_unique<Dielectric>(1.5f)));
				}
			}
		}
	}

	scene->add(std::make_unique<Sphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Dielectric>(1.5f)));
	scene->add(std::make_unique<Sphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Metal>(Vec3(0.7f, 0.6f, 0.5f), 0.0f)));
	std::unique_ptr<Texture> constant_texture = std::make_unique<ConstantTexture>(Vec3(0.4f, 0.2f, 0.1f));
	scene->add(std::make_unique<Sphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Lambertian>(std::move(constant_texture))));
	return std::move(scene);
}

inline void printProgress(int current, int total)
{
	static tbb::spin_mutex mutex;

	tbb::spin_mutex::scoped_lock lock(mutex);
	std::cout<< "\rpixels: " << current << "/" << total << std::flush;
}

int main(int argc, const char* argv[])
{
	Vec3 v;
	int w = WIDTH;
	int h = HEIGHT;
	int s = SAMPLES;
	std::unique_ptr<byte> data = std::unique_ptr<byte>(new byte[w * h * RGBA]);
	tbb::atomic<int> rendered_pixels = 0;

	std::unique_ptr<HitableList> scene = make_random_scene();

	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	real aperture = 0.0f;
	real focus_dist = 10.0f;
	Camera camera(lookfrom, lookat, Vec3(0, 1, 0), 20, real(w)/real(h), aperture, focus_dist, 0.0, 1.0);

	auto start_time = std::chrono::steady_clock::now();
	tbb::parallel_for(size_t(0), size_t(w*h),
		[w, h, s, &data, &scene, &camera, &rendered_pixels](size_t r) {
		Vec3 col(0, 0, 0);
		size_t j = r / w;
		size_t i = r % w;
		for (int n = 0; n < s; ++n)
		{
			real u = real(i + RNG::rng()) / real(w);
			real v = real(j + RNG::rng()) / real(h);
			Ray ray = camera.getRay(u, v);
			col += color(ray, *scene, 0);
		}
		col /= real(s);
		col = { sqrt(col.r), sqrt(col.g), sqrt(col.b) };//gamma 2
		data.get()[(h-j-1)*w*RGBA + i*RGBA    ] = int(col.r * 255.99);
		data.get()[(h-j-1)*w*RGBA + i*RGBA + 1] = int(col.g * 255.99);
		data.get()[(h-j-1)*w*RGBA + i*RGBA + 2] = int(col.b * 255.99);
		data.get()[(h-j-1)*w*RGBA + i*RGBA + 3] = 255;

		rendered_pixels++;
		printProgress(rendered_pixels, w*h);
	});
	auto time_span = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time);
	std::cout << "\ntime elapsed:" << time_span.count() << " seconds.\n";
	if (stbi_write_png("output.png", WIDTH, HEIGHT, RGBA, data.get(), 0) == 0)
	{
		std::cout << "write png file failed.\n";
	}
	else {
		std::cout << "write png file as output.png\n";
	}
	system("PAUSE");

	return 0;
}