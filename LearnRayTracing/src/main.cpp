#include <iostream>

#include "color.h"
#include "Ray.h"
#include "vec3.h"
/**
像素是按行写入的。

每一行像素都是从左到右写入的。

这些行是从上到下书写的。

按照惯例，每个红色/绿色/蓝色分量在内部都由范围在 0.0 到 1.0 的实值变量表示。在打印之前，这些值必须被缩放到 0 到 255 之间的整数值。

红色从左到右从完全关闭（黑色）到完全开启（亮红色），绿色从顶部完全关闭（黑色）到底部完全开启（亮绿色）。红色和绿色光叠加在一起会形成黄色，因此我们预期右下角会是黄色。

*/


RT::vec3 ray_Color(const Ray& r)
{
    RT::vec3 unit_direction = RT::unit_vector(r.Direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * RT::vec3(1.0, 1.0, 1.0) + a * RT::vec3(0.5, 0.7, 1.0);
}

int main() {

    // Image

    auto aspectRatio = 16.0 / 9.0;
    int image_width = 400;
    //计算图像高度，并确保至少为1

    int image_height = int(image_width / aspectRatio);
    image_height = (image_height < 1) ? 1 : image_height;

    //camera
    auto focal_length= 1.0;//焦距：相机镜头到成像平面的距离值 1.0 表示在虚拟世界单位中决定了视野范围（FOV），焦距越小视野越广
    auto viewport_height = 2.0;//视口高度：成像平面的垂直尺寸值 2.0 表示2个世界单位高度与焦距共同决定视野角度
    auto viewport_width = viewport_height * (float(image_width / image_height));//视口宽度：成像平面的水平尺寸根据图像宽高比动态计算：宽度 = 高度 × (图像宽度/图像高度)保持画面比例不变，避免拉伸变形
    auto camera_center = RT::vec3(0, 0, 0);

    //计算水平方向和垂直方向视口边缘上的向量。
    auto viewport_u = RT::vec3(viewport_width, 0, 0);
    auto viewport_v = RT::vec3(0, -viewport_height, 0);
    //计算像素到像素的水平和垂直差分向量。
    auto pixel_delta_u = viewport_u / (float)image_width;
    auto pixel_delta_v = viewport_v / (float)image_height;

    // 计算左上角像素的位置。
    auto viewport_upper_left = camera_center
        - RT::vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + (float)0.5 * (pixel_delta_u + pixel_delta_v);
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (uint32_t j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining :" << (image_height - j) << ' ' << std::flush;
        for (uint32_t i = 0; i < image_width; i++) {

            auto pixel_center = pixel00_loc + ((float)i * pixel_delta_u) + ((float)j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            Ray r(camera_center, ray_direction);
            RT::vec3 pixel_color = ray_Color(r);

            WirteColor(std::cout, pixel_color);

        }
    }

    std::clog << "\rDone:                        \n";
}