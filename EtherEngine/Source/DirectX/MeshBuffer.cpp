#include <DirectX/MeshBuffer.h>

namespace EtherEngine {
    // �R���X�g���N�^
    MeshBuffer::Description::Description(Handle<DirectXRender> directXRender,
        const void* vertex, uint vertexSize, uint vertexCount, bool isWrite,
        const void* index, uint indexSize, uint indexCount,
        D3D11_PRIMITIVE_TOPOLOGY topology) 
        : directXRender(directXRender.GetHandle())
        , vertex(vertex), vertexSize(vertexSize), vertexCount(vertexCount), isWrite(isWrite)
        , index(index), indexSize(indexSize), indexCount(indexCount), topology(topology) {
    }


    // �R���X�g���N�^
    MeshBuffer::MeshBuffer(const Description& desc)
        : m_directxRender(desc.directXRender.GetHandle())
        , m_vertexBuffer(nullptr)
        , m_vertexSize(0)
        , m_vertexCount(0)
        , m_indexBuffer(nullptr)
        , m_indexSize(0)
        , m_indexCount(0) {
        //----- �ϐ��錾
        HRESULT hr = E_FAIL;

        //----- ���_�o�b�t�@�쐬
        hr = CreateVertexBuffer(desc.vertex, desc.vertexSize, desc.vertexCount, desc.isWrite);

        //----- �C���f�b�N�X�o�b�t�@�쐬
        if (desc.index) {
            hr = CreateIndexBuffer(desc.index, desc.indexSize, desc.indexCount);
        }

        m_topology = desc.topology;
    }
    // �f�X�g���N�^
    MeshBuffer::~MeshBuffer(void) {
    }


    // �`�悷��
    void MeshBuffer::Draw(const int count) {
        //----- �ϐ��錾
        auto data = m_directxRender.GetAtomicItem();
        auto context = data.GetData().GetContext();
        uint stride = m_vertexSize;
        uint offset = 0;

        //----- �`������ݒ�
        context->IASetPrimitiveTopology(m_topology);
        context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetEditable(), &stride, &offset);

        //----- �`����s��
        if (m_indexCount > 0) {
            //----- �C���f�b�N�X��p�����`��
            //----- �ϐ��錾
            DXGI_FORMAT format;
            switch (m_indexSize) {
            case 4: format = DXGI_FORMAT_R32_UINT; break;
            case 2: format = DXGI_FORMAT_R16_UINT; break;
            }

            context->IASetIndexBuffer(m_indexBuffer.Get(), format, 0);
            context->DrawIndexed(count ? count : m_indexCount, 0, 0);
        }
        else {
            //----- ���_�o�b�t�@�݂̂̏��ŕ`��
            context->Draw(count ? count : m_vertexCount, 0);
        }
    }
    // ��������
    HRESULT MeshBuffer::Write(void* vertex) {
        //----- �ϐ��錾
        HRESULT hr;
        auto data = m_directxRender.GetAtomicItem();
        auto device = data.GetData().GetDevice();
        auto context = data.GetData().GetContext();
        D3D11_MAPPED_SUBRESOURCE mapResource;

        //----- �f�[�^�̃R�s�[
        hr = context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);

        //----- ����������
        if (SUCCEEDED(hr)) {
            rsize_t size = m_vertexCount * m_vertexSize;
            memcpy_s(mapResource.pData, size, vertex, size);
            context->Unmap(m_vertexBuffer.Get(), 0);
        }

        //----- �ԋp
        return hr;
    }

    // ���_�o�b�t�@���쐬����
    HRESULT MeshBuffer::CreateVertexBuffer(const void* vertex, uint size, uint count, bool isWrite) {
        //----- �쐬����o�b�t�@�̏��
        D3D11_BUFFER_DESC bufDesc = {};
        bufDesc.ByteWidth = size * count;
        bufDesc.Usage = D3D11_USAGE_DEFAULT;
        bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        if (isWrite) {
            bufDesc.Usage = D3D11_USAGE_DYNAMIC;
            bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        }

        //----- �o�b�t�@�̏����l��ݒ�
        D3D11_SUBRESOURCE_DATA subResource = {};
        subResource.pSysMem = vertex;

        //----- ���_�o�b�t�@�̍쐬
        HRESULT hr;
        hr = m_directxRender.GetAtomicData().GetDevice()->CreateBuffer(&bufDesc, &subResource, m_vertexBuffer.GetEditable());

        //----- ���̂ق��̏���ݒ�
        if (SUCCEEDED(hr)) {
            m_vertexSize  = size;
            m_vertexCount = count;
        }
        return hr;
    }
    // �C���f�b�N�X�o�b�t�@���쐬����
    HRESULT MeshBuffer::CreateIndexBuffer(const void* index, uint size, uint count) {
        //----- �C���f�b�N�X�T�C�Y�̊m�F
        if (size != 2 && size != 4) {
            return E_FAIL;
        }

        //----- �o�b�t�@�̏���ݒ�
        D3D11_BUFFER_DESC bufDesc = {};
        bufDesc.ByteWidth = size * count;
        bufDesc.Usage = D3D11_USAGE_DEFAULT;
        bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        //----- �o�b�t�@�̏����f�[�^
        D3D11_SUBRESOURCE_DATA subResource = {};
        subResource.pSysMem = index;

        // �C���f�b�N�X�o�b�t�@����
        HRESULT hr;
        hr = m_directxRender.GetAtomicData().GetDevice()->CreateBuffer(&bufDesc, &subResource, m_indexBuffer.GetEditable());
        if (SUCCEEDED(hr)) {
            m_indexSize = size;
            m_indexCount = count;
        }

        //----- �ԋp
        return hr;
    }
}
