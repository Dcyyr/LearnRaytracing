#pragma once


#include "hittable.h"
#include "Material.h"
/**
像素是按行写入的。

每一行像素都是从左到右写入的。

这些行是从上到下书写的。

按照惯例，每个红色/绿色/蓝色分量在内部都由范围在 0.0 到 1.0 的实值变量表示。在打印之前，这些值必须被缩放到 0 到 255 之间的整数值。

红色从左到右从完全关闭（黑色）到完全开启（亮红色），绿色从顶部完全关闭（黑色）到底部完全开启（亮绿色）。红色和绿色光叠加在一起会形成黄色，因此我们预期右下角会是黄色。

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

                RT::vec3 pixelColor(0, 0, 0);

                for (int sample = 0; sample < m_SamplesPerPixel; sample++)
                {
                    Ray r = GetRay(i, j);
                    pixelColor += RayColor(r,m_MaxDepth, world);
                }
               

               
                WirteColor(std::cout, m_PixelSamplesScale* pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }
private:

    void initialize() {
        m_ImageHeight = int(m_ImageWidth / m_AspectRatio);
        m_ImageHeight = (m_ImageHeight < 1) ? 1 : m_ImageHeight;

        m_PixelSamplesScale = 1.0 / m_SamplesPerPixel;

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

    RT::vec3 RayColor(const Ray& r,int maxdepth, const Hittable& world) const 
    {

        if (maxdepth <= 0)
            return RT::vec3(0, 0, 0);

        HitRecord rec;
       
        if (world.hit(r, Interval(0.001, Infinity), rec)) {
            Ray scattered;
            RT::vec3 attenuation;
            if (rec.m_Mat->Scatter(r, rec, attenuation, scattered))
                return attenuation * RayColor(scattered, maxdepth - 1, world);
            return RT::vec3(0, 0, 0);

        }

        RT::vec3 unit_direction = RT::UnitVector(r.Direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * RT::vec3(1.0, 1.0, 1.0) + a * RT::vec3(0.5, 0.7, 1.0);//每次递归返回的颜色都乘以 0.5，表示每次弹射（反射/散射）后，光线能量减半，实现能量衰减
    }

    // // 构造一条从原点出发、指向像素位置 i, j 周围随机采样点的摄像机射线。
    Ray GetRay(int i, int j)const
    {
        auto offset = SampleSquare();
        auto pixelSample = m_PixelLocation00 + 
            ((i + offset.x()) * m_PixelDeltaU) + 
            ((j + offset.y()) * m_PixelDeltaV);

        auto RayOrigin = m_Center;
		auto Raydirection = pixelSample - RayOrigin;

        return Ray(m_Center, Raydirection);
    }

    RT::vec3 SampleSquare()const
    {
        // 将向量返回至单位正方形[-.5,-.5]-[+.5,+.5]内的随机点。
        return RT::vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
    }


public:
    double   m_AspectRatio = 1.0;  // 图像宽度与高度之比
    int      m_ImageWidth = 100;  // 渲染图像宽度（以像素计）
    int      m_SamplesPerPixel = 10; //每个像素的随机采样计数
	int      m_MaxDepth = 10; // 递归光线追踪的最大深度
private:
    int      m_ImageHeight;   // Rendered image height
    RT::vec3 m_Center;        // Camera center
    RT::vec3 m_PixelLocation00;     // Location of pixel 0, 0
    RT::vec3 m_PixelDeltaU;   // Offset to pixel to the right
    RT::vec3 m_PixelDeltaV;   // Offset to pixel below

    double   m_PixelSamplesScale;// 像素采样值之和的颜色比例因子

};