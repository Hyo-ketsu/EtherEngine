#ifndef I_MESH_H
#define I_MESH_H
#include <Base/GraphicDefines.h>
#include <DirectX/MeshBuffer.h>


namespace EtherEngine {
    // ���b�V����\������\����
    struct Mesh {
        std::vector<Vertex> vertexs;    // �����̒��_
        std::vector<uint>   indexs;     // �����̃C���f�b�N�X
        uint                materialID; // �}�e���A����ID
        std::shared_ptr<MeshBuffer> mesh;       // �ێ����Ă��钸�_�o�b�t�@

        Mesh(void) = default;
        Mesh(const Mesh& copy) = default;
        Mesh(Mesh&& move) = default;
        Mesh& operator =(const Mesh& in) = default;
    };
}


#endif // !I_MESH_H
