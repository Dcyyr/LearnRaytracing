#include <iostream>
#include <glm/glm.hpp>
/**
像素是按行写入的。

每一行像素都是从左到右写入的。

这些行是从上到下书写的。

按照惯例，每个红色/绿色/蓝色分量在内部都由范围在 0.0 到 1.0 的实值变量表示。在打印之前，这些值必须被缩放到 0 到 255 之间的整数值。

红色从左到右从完全关闭（黑色）到完全开启（亮红色），绿色从顶部完全关闭（黑色）到底部完全开启（亮绿色）。红色和绿色光叠加在一起会形成黄色，因此我们预期右下角会是黄色。

*/
int main() {

    // Image

    const uint32_t image_width  = 256;
    const uint32_t image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (uint32_t j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining :" << (image_height - j) << ' ' << std::flush;
        for (uint32_t i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width  - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\rDone:                        \n";
}