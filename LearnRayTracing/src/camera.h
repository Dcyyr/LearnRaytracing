#pragma once

#include "hittable.h"

/**
�����ǰ���д��ġ�

ÿһ�����ض��Ǵ�����д��ġ�

��Щ���Ǵ��ϵ�����д�ġ�

���չ�����ÿ����ɫ/��ɫ/��ɫ�������ڲ����ɷ�Χ�� 0.0 �� 1.0 ��ʵֵ������ʾ���ڴ�ӡ֮ǰ����Щֵ���뱻���ŵ� 0 �� 255 ֮�������ֵ��

��ɫ�����Ҵ���ȫ�رգ���ɫ������ȫ����������ɫ������ɫ�Ӷ�����ȫ�رգ���ɫ�����ײ���ȫ����������ɫ������ɫ����ɫ�������һ����γɻ�ɫ���������Ԥ�����½ǻ��ǻ�ɫ��

*/
class Camera
{
public:
    void render(const Hittable& world) 
    {
        initialize();

        std::cout << "P3\n" << m_ImageWidth << ' ' << m_ImageHeight << "\n255\n";

        for (int j = 0; j < m_ImageHeight; j++)
        {
            std::clog << "\rScanlines remaining: " << (m_ImageHeight - j) << ' ' << std::flush;
            for (int i = 0; i < m_ImageWidth; i++) 
            {
                auto pixel_center = m_PixelLocation00 + (i * m_PixelDeltaU) + (j * m_PixelDeltaV);
                auto ray_direction = pixel_center - m_Center;
                Ray r(m_Center, ray_direction);

                RT::vec3 pixel_color = RayColor(r, world);
                WirteColor(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }


    void initialize() {
        m_ImageHeight = int(m_ImageWidth / m_AspectRatio);
        m_ImageHeight = (m_ImageHeight < 1) ? 1 : m_ImageHeight;

        m_Center = RT::vec3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(m_ImageWidth) / m_ImageHeight);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = RT::vec3(viewport_width, 0, 0);
        auto viewport_v = RT::vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        m_PixelDeltaU = viewport_u / m_ImageWidth;
        m_PixelDeltaV = viewport_v / m_ImageHeight;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            m_Center - RT::vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        m_PixelLocation00 = viewport_upper_left + 0.5 * (m_PixelDeltaU + m_PixelDeltaV);
    }

    RT::vec3 RayColor(const Ray& r, const Hittable& world) const {
        HitRecord rec;

        if (world.hit(r, interval(0, Infinity), rec)) {
            return 0.5 * (rec.normal + RT::vec3(1, 1, 1));
        }

        RT::vec3 unit_direction = RT::unit_vector(r.Direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * RT::vec3(1.0, 1.0, 1.0) + a * RT::vec3(0.5, 0.7, 1.0);
    }

public:
    double   m_AspectRatio = 1.0;  // Ratio of image width over height
    int      m_ImageWidth = 100;  // Rendered image width in pixel count
private:
    int      m_ImageHeight;   // Rendered image height
    RT::vec3 m_Center;        // Camera center
    RT::vec3 m_PixelLocation00;     // Location of pixel 0, 0
    RT::vec3 m_PixelDeltaU;   // Offset to pixel to the right
    RT::vec3 m_PixelDeltaV;   // Offset to pixel below

};