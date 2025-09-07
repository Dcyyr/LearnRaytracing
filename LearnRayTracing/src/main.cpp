#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "camera.h"
#include "Material.h"

int main() {

	// World
	HittableList world;


	auto materialGround = std::make_shared<Lambertian>(RT::vec3(0.8, 0.8, 0.0));
	auto materialCenter = std::make_shared<Lambertian>(RT::vec3(0.1, 0.2, 0.5));
	auto materialLeft   = std::make_shared<Metal>(RT::vec3(0.8, 0.8, 0.8),0.3);
	auto materialRight  = std::make_shared<Metal>(RT::vec3(0.8, 0.6, 0.2),1.0);



    world.Add(std::make_shared<Sphere>(RT::vec3(0, -100.5, -1),100, materialGround));
	world.Add(std::make_shared<Sphere>(RT::vec3(0, 0, -1.2), 0.5, materialCenter));
	world.Add(std::make_shared<Sphere>(RT::vec3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	world.Add(std::make_shared<Sphere>(RT::vec3(1.0, 0.0, -1.0), 0.5, materialRight));

	Camera m_Cam;
	m_Cam.m_AspectRatio = 16.0/9.0;
	m_Cam.m_ImageWidth = 400;
	m_Cam.m_SamplesPerPixel = 100;
	m_Cam.m_MaxDepth = 50;


	m_Cam.render(world);
   
}