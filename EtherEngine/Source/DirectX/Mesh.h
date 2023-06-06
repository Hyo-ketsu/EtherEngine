#ifndef I_MESH_H
#define I_MESH_H
#include <Base/GraphicDefines.h>
#include <DirectX/MeshBuffer.h>


namespace EtherEngine {
    // メッシュを表現する構造体
    struct Mesh {
        std::vector<Vertex> vertexs;    // 複数の頂点
        std::vector<uint>   indexs;     // 複数のインデックス
        uint                materialID; // マテリアルのID
        std::shared_ptr<MeshBuffer> mesh;       // 保持している頂点バッファ

        Mesh(void) = default;
        Mesh(const Mesh& copy) = default;
        Mesh(Mesh&& move) = default;
        Mesh& operator =(const Mesh& in) = default;
    };
}


#endif // !I_MESH_H
