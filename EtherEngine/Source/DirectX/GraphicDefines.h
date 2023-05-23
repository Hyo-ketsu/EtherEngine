#ifndef I_GRAPHICDEFINES_H
#define I_GRAPHICDEFINES_H
#include <Base/Handle.h>
#include <DirectX/Texture.h>


namespace EtherEngine {
    // ���_��\������\����
    struct Vertex {
        Eigen::Vector3f pos;    // ���W
        Eigen::Vector3f normal; // �@��
        Eigen::Vector3f uv;     // �e�N�X�`�����W
    };


    // �}�e���A����\������\����
    struct Material {
        Eigen::Vector4f diffuse;    // �g�U��
        Eigen::Vector4f ambient;    // ����
        Eigen::Vector4f specular;   // ���ˌ�
        Handle<Texture> texture;    // �e�N�X�`���[
    };


    // ���b�V����\������\����
    struct Mesh {
        std::vector<Vertex> vertexs;    // �����̒��_
        std::vector<uint>   indexs;     // �����̃C���f�b�N�X
        uint                materialID; // �}�e���A����ID
    };
}


#endif // !I_GRAPHICDEFINES_H
