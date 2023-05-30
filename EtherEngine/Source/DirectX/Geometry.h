#ifndef I_GEOMETRY_H
#define I_GEOMETRY_H
#include <DirectX/Texture.h>


namespace EtherEngine {
    class Geometory {
        // 初期化処理
        static void Init(void);
        // 終了処理
        static void Uninit(void);


        // 頂点シェーダーをセットする
        // @ Arg1 : 頂点シェーダーのポインタ
        static void SetVertexShader()

        // 頂点シェーダをセットする
        static void SetPixelShader()
    };
}


#endif // !I_GEOMETRY_H
