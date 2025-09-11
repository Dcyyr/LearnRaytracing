#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "camera.h"
#include "Material.h"

int main() {

	// World
	HittableList world;

	auto groundMaterial = std::make_shared<Lambertian>(RT::vec3(0.5, 0.5, 0.5));
	world.Add(std::make_shared<Sphere>(RT::vec3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto chooseMaterial = RandomDouble();
			RT::vec3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

			if ((center - RT::vec3(4, 0.2, 0)).length() > 0.9)
			{
				std::shared_ptr<Material> sphereMaterial;

				if (chooseMaterial < 0.8)
				{
					auto albedo = RT::vec3::Random() * RT::vec3::Random();
					sphereMaterial = std::make_shared<Lambertian>(albedo);
					world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else if (chooseMaterial < 0.95) {

					auto albedo = RT::vec3::Random(0.5, 1);
					auto fuzz = RandomDouble(0, 0.5);
					sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
					world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));

				}
				else {
					sphereMaterial = std::make_shared<Dielectric>(1.5);
					world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}

			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.Add(std::make_shared<Sphere>(RT::vec3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(RT::vec3(0.4, 0.2, 0.1));
	world.Add(std::make_shared<Sphere>(RT::vec3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(RT::vec3(0.7, 0.6, 0.5), 0.0);
	world.Add(std::make_shared<Sphere>(RT::vec3(4, 1, 0), 1.0, material3));
	

	Camera m_Cam;
	m_Cam.m_AspectRatio = 16.0/9.0;
	m_Cam.m_ImageWidth = 1200;
	m_Cam.m_SamplesPerPixel = 500;
	m_Cam.m_MaxDepth = 50;

	m_Cam.m_Vfov = 20.0;
	m_Cam.m_LookFrom = RT::vec3(13,2, 3);
	m_Cam.m_LookAt	 = RT::vec3(0, 0, 0);
	m_Cam.m_ViewUp	 = RT::vec3(0, 1, 0);

	m_Cam.m_DefocusAngle = 0.6;
	m_Cam.m_FocusDist    = 10.0;

	m_Cam.render(world);
   
}