#ifndef I_GRAPHICDEFINES_H
#define I_GRAPHICDEFINES_H
#include <Base/Handle.h>
#include <DirectX/Texture.h>


namespace EtherEngine {
    // ���_��\������\����
    struct Vertex {
        Eigen::Vector3f pos;    // ���W
        Eigen::Vector3f normal; // �@��
        Eigen::Vector2f uv;     // �e�N�X�`�����W

        Vertex(void) = default;
        Vertex(const Vertex& copy) = default;
        Vertex(Vertex&& move) = default;
        Vertex& operator =(const Vertex& in) = default;
    };


    // �}�e���A����\������\����
    struct Material {
        Eigen::Vector4f diffuse;    // �g�U��
        Eigen::Vector4f ambient;    // ����
        Eigen::Vector4f specular;   // ���ˌ�
        std::unique_ptr<Texture> texture;    // �e�N�X�`���[

        Material(void) = default;
        Material(const Material& copy) = default;
        Material(Material&& move) = default;
        Material& operator =(const Material& in) = default;
    };
}


#endif // !I_GRAPHICDEFINES_H
