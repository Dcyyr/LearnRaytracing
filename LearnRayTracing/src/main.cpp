#include <iostream>
#include <glm/glm.hpp>
/**
�����ǰ���д��ġ�

ÿһ�����ض��Ǵ�����д��ġ�

��Щ���Ǵ��ϵ�����д�ġ�

���չ�����ÿ����ɫ/��ɫ/��ɫ�������ڲ����ɷ�Χ�� 0.0 �� 1.0 ��ʵֵ������ʾ���ڴ�ӡ֮ǰ����Щֵ���뱻���ŵ� 0 �� 255 ֮�������ֵ��

��ɫ�����Ҵ���ȫ�رգ���ɫ������ȫ����������ɫ������ɫ�Ӷ�����ȫ�رգ���ɫ�����ײ���ȫ����������ɫ������ɫ����ɫ�������һ����γɻ�ɫ���������Ԥ�����½ǻ��ǻ�ɫ��

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