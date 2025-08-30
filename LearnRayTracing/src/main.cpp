#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "camera.h"


int main() {

	// World
	HittableList world;
    world.Add(std::make_shared<Sphere>(RT::vec3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(RT::vec3(0, -100.5, -1),100));

	Camera m_Cam;
	m_Cam.m_AspectRatio = 16.0/9.0;
	m_Cam.m_ImageWidth = 400;
	m_Cam.m_SamplesPerPixel = 100;

	m_Cam.render(world);
   
}