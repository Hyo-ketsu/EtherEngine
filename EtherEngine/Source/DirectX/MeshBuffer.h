#ifndef I_MESHBUFFER_H
#define I_MESHBUFFER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <DirectX/ComPointer.h>


namespace EtherEngine {
    // メッシュバッファ
    class MeshBuffer {
    public:
        // 初期化情報構造体
        struct Description {
            // コンストラクタ
            Description(BaseHandle<DirectXRender> directXRender,
                const void* vertex, uint vertexSize, uint vertexCount, bool isWrite,
                const void* index, uint indexSize, uint indexCount,
                D3D11_PRIMITIVE_TOPOLOGY topology);


            BaseHandle<DirectXRender> directXRender;
            const void* vertex;
            uint vertexSize;
            uint vertexCount;
            bool isWrite;
            const void* index;
            uint indexSize;
            uint indexCount;
            D3D11_PRIMITIVE_TOPOLOGY topology;
        };

        // コンストラクタ
        // @ Arg1 : 初期化情報
        MeshBuffer(const Description& desc);
        // デストラクタ
        ~MeshBuffer(void);


        // 描画する
        // @ Arg1 : 
        void Draw(const int count = 0);
        // 書き込む
        // @ Arg1 : 書き込む頂点情報
        HRESULT Write(void* vertex);

    private:
        // 頂点バッファを作成する
        // @ Arg1 : 
        // @ Arg2 : 
        // @ Arg3 : 
        HRESULT CreateVertexBuffer(const void* vertex, uint size, uint count, bool isWrite);
        // インデックスバッファを作成する
        // @ Arg1 : 
        // @ Arg2 : 
        // @ Arg3 : 
        HRESULT CreateIndexBuffer(const void* index, uint size, uint count);


        BaseHandle<DirectXRender> m_directxRender;  // 描画対象
        ComPtr<ID3D11Buffer> m_vertexBuffer; // 頂点バッファ
        uint m_vertexSize;                   // 頂点バッファのサイズ        
        uint m_vertexCount;                  // 頂点バッファの数
        ComPtr<ID3D11Buffer> m_indexBuffer; // インデックスバッファ
        uint m_indexSize;                   // インデックスバッファのサイズ
        uint m_indexCount;                  // インデックスバッファの数
        D3D11_PRIMITIVE_TOPOLOGY m_topology; // 描画方式
    };
}


#endif // !I_MESHBUFFER_H
