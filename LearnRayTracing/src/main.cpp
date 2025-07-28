#include <iostream>

#include "color.h"
#include "Ray.h"
#include "vec3.h"
/**
�����ǰ���д��ġ�

ÿһ�����ض��Ǵ�����д��ġ�

��Щ���Ǵ��ϵ�����д�ġ�

���չ�����ÿ����ɫ/��ɫ/��ɫ�������ڲ����ɷ�Χ�� 0.0 �� 1.0 ��ʵֵ������ʾ���ڴ�ӡ֮ǰ����Щֵ���뱻���ŵ� 0 �� 255 ֮�������ֵ��

��ɫ�����Ҵ���ȫ�رգ���ɫ������ȫ����������ɫ������ɫ�Ӷ�����ȫ�رգ���ɫ�����ײ���ȫ����������ɫ������ɫ����ɫ�������һ����γɻ�ɫ���������Ԥ�����½ǻ��ǻ�ɫ��

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
    //����ͼ��߶ȣ���ȷ������Ϊ1

    int image_height = int(image_width / aspectRatio);
    image_height = (image_height < 1) ? 1 : image_height;

    //camera
    auto focal_length= 1.0;//���ࣺ�����ͷ������ƽ��ľ���ֵ 1.0 ��ʾ���������絥λ�о�������Ұ��Χ��FOV��������ԽС��ҰԽ��
    auto viewport_height = 2.0;//�ӿڸ߶ȣ�����ƽ��Ĵ�ֱ�ߴ�ֵ 2.0 ��ʾ2�����絥λ�߶��뽹�๲ͬ������Ұ�Ƕ�
    auto viewport_width = viewport_height * (float(image_width / image_height));//�ӿڿ�ȣ�����ƽ���ˮƽ�ߴ����ͼ���߱ȶ�̬���㣺��� = �߶� �� (ͼ����/ͼ��߶�)���ֻ���������䣬�����������
    auto camera_center = RT::vec3(0, 0, 0);

    //����ˮƽ����ʹ�ֱ�����ӿڱ�Ե�ϵ�������
    auto viewport_u = RT::vec3(viewport_width, 0, 0);
    auto viewport_v = RT::vec3(0, -viewport_height, 0);
    //�������ص����ص�ˮƽ�ʹ�ֱ���������
    auto pixel_delta_u = viewport_u / (float)image_width;
    auto pixel_delta_v = viewport_v / (float)image_height;

    // �������Ͻ����ص�λ�á�
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