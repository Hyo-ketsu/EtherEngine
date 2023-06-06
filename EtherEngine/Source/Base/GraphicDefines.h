#ifndef I_GRAPHICDEFINES_H
#define I_GRAPHICDEFINES_H
#include <Base/Handle.h>
#include <DirectX/Texture.h>


namespace EtherEngine {
    // 頂点を表現する構造体
    struct Vertex {
        Eigen::Vector3f pos;    // 座標
        Eigen::Vector3f normal; // 法線
        Eigen::Vector2f uv;     // テクスチャ座標

        Vertex(void) = default;
        Vertex(const Vertex& copy) = default;
        Vertex(Vertex&& move) = default;
        Vertex& operator =(const Vertex& in) = default;
    };


    // マテリアルを表現する構造体
    struct Material {
        Eigen::Vector4f diffuse;    // 拡散光
        Eigen::Vector4f ambient;    // 環境光
        Eigen::Vector4f specular;   // 反射光
        std::unique_ptr<Texture> texture;    // テクスチャー

        Material(void) = default;
        Material(const Material& copy) = default;
        Material(Material&& move) = default;
        Material& operator =(const Material& in) = default;
    };
}


#endif // !I_GRAPHICDEFINES_H
