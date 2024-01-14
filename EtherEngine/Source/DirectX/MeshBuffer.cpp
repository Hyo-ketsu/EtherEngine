#include <DirectX/MeshBuffer.h>

namespace EtherEngine {
    // コンストラクタ
    MeshBuffer::Description::Description(Handle<DirectXRender> directXRender,
        const void* vertex, uint vertexSize, uint vertexCount, bool isWrite,
        const void* index, uint indexSize, uint indexCount,
        D3D11_PRIMITIVE_TOPOLOGY topology) 
        : directXRender(directXRender.GetHandle())
        , vertex(vertex), vertexSize(vertexSize), vertexCount(vertexCount), isWrite(isWrite)
        , index(index), indexSize(indexSize), indexCount(indexCount), topology(topology) {
    }


    // コンストラクタ
    MeshBuffer::MeshBuffer(const Description& desc)
        : m_directxRender(desc.directXRender.GetHandle())
        , m_vertexBuffer(nullptr)
        , m_vertexSize(0)
        , m_vertexCount(0)
        , m_indexBuffer(nullptr)
        , m_indexSize(0)
        , m_indexCount(0) {
        //----- 変数宣言
        HRESULT hr = E_FAIL;

        //----- 頂点バッファ作成
        hr = CreateVertexBuffer(desc.vertex, desc.vertexSize, desc.vertexCount, desc.isWrite);

        //----- インデックスバッファ作成
        if (desc.index) {
            hr = CreateIndexBuffer(desc.index, desc.indexSize, desc.indexCount);
        }

        m_topology = desc.topology;
    }
    // デストラクタ
    MeshBuffer::~MeshBuffer(void) {
    }


    // 描画する
    void MeshBuffer::Draw(const int count) {
        //----- 変数宣言
        auto data = m_directxRender.GetAtomicItem();
        auto context = data.GetData().GetContext();
        uint stride = m_vertexSize;
        uint offset = 0;

        //----- 描画方式設定
        context->IASetPrimitiveTopology(m_topology);
        context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetEditable(), &stride, &offset);

        //----- 描画を行う
        if (m_indexCount > 0) {
            //----- インデックスを用いた描画
            //----- 変数宣言
            DXGI_FORMAT format;
            switch (m_indexSize) {
            case 4: format = DXGI_FORMAT_R32_UINT; break;
            case 2: format = DXGI_FORMAT_R16_UINT; break;
            }

            context->IASetIndexBuffer(m_indexBuffer.Get(), format, 0);
            context->DrawIndexed(count ? count : m_indexCount, 0, 0);
        }
        else {
            //----- 頂点バッファのみの情報で描画
            context->Draw(count ? count : m_vertexCount, 0);
        }
    }
    // 書き込む
    HRESULT MeshBuffer::Write(void* vertex) {
        //----- 変数宣言
        HRESULT hr;
        auto data = m_directxRender.GetAtomicItem();
        auto device = data.GetData().GetDevice();
        auto context = data.GetData().GetContext();
        D3D11_MAPPED_SUBRESOURCE mapResource;

        //----- データのコピー
        hr = context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);

        //----- 成功したか
        if (SUCCEEDED(hr)) {
            rsize_t size = m_vertexCount * m_vertexSize;
            memcpy_s(mapResource.pData, size, vertex, size);
            context->Unmap(m_vertexBuffer.Get(), 0);
        }

        //----- 返却
        return hr;
    }

    // 頂点バッファを作成する
    HRESULT MeshBuffer::CreateVertexBuffer(const void* vertex, uint size, uint count, bool isWrite) {
        //----- 作成するバッファの情報
        D3D11_BUFFER_DESC bufDesc = {};
        bufDesc.ByteWidth = size * count;
        bufDesc.Usage = D3D11_USAGE_DEFAULT;
        bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        if (isWrite) {
            bufDesc.Usage = D3D11_USAGE_DYNAMIC;
            bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        }

        //----- バッファの初期値を設定
        D3D11_SUBRESOURCE_DATA subResource = {};
        subResource.pSysMem = vertex;

        //----- 頂点バッファの作成
        HRESULT hr;
        hr = m_directxRender.GetAtomicData().GetDevice()->CreateBuffer(&bufDesc, &subResource, m_vertexBuffer.GetEditable());

        //----- そのほかの情報を設定
        if (SUCCEEDED(hr)) {
            m_vertexSize  = size;
            m_vertexCount = count;
        }
        return hr;
    }
    // インデックスバッファを作成する
    HRESULT MeshBuffer::CreateIndexBuffer(const void* index, uint size, uint count) {
        //----- インデックスサイズの確認
        if (size != 2 && size != 4) {
            return E_FAIL;
        }

        //----- バッファの情報を設定
        D3D11_BUFFER_DESC bufDesc = {};
        bufDesc.ByteWidth = size * count;
        bufDesc.Usage = D3D11_USAGE_DEFAULT;
        bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        //----- バッファの初期データ
        D3D11_SUBRESOURCE_DATA subResource = {};
        subResource.pSysMem = index;

        // インデックスバッファ生成
        HRESULT hr;
        hr = m_directxRender.GetAtomicData().GetDevice()->CreateBuffer(&bufDesc, &subResource, m_indexBuffer.GetEditable());
        if (SUCCEEDED(hr)) {
            m_indexSize = size;
            m_indexCount = count;
        }

        //----- 返却
        return hr;
    }
}
