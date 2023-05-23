#ifndef I_GRAPHICDEFINES_H
#define I_GRAPHICDEFINES_H
#include <Base/Handle.h>
#include <DirectX/Texture.h>


namespace EtherEngine {
    // 頂点を表現する構造体
    struct Vertex {
        Eigen::Vector3f pos;    // 座標
        Eigen::Vector3f normal; // 法線
        Eigen::Vector3f uv;     // テクスチャ座標
    };


    // マテリアルを表現する構造体
    struct Material {
        Eigen::Vector4f diffuse;    // 拡散光
        Eigen::Vector4f ambient;    // 環境光
        Eigen::Vector4f specular;   // 反射光
        Handle<Texture> texture;    // テクスチャー
    };


    // メッシュを表現する構造体
    struct Mesh {
        std::vector<Vertex> vertexs;    // 複数の頂点
        std::vector<uint>   indexs;     // 複数のインデックス
        uint                materialID; // マテリアルのID
    };
}


#endif // !I_GRAPHICDEFINES_H
