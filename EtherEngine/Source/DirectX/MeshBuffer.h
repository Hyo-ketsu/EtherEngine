#ifndef I_MESHBUFFER_H
#define I_MESHBUFFER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <DirectX/ComPointer.h>


namespace EtherEngine {
    // ���b�V���o�b�t�@
    class MeshBuffer {
    public:
        // ���������\����
        struct Description {
            // �R���X�g���N�^
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

        // �R���X�g���N�^
        // @ Arg1 : ���������
        MeshBuffer(const Description& desc);
        // �f�X�g���N�^
        ~MeshBuffer(void);


        // �`�悷��
        // @ Arg1 : 
        void Draw(const int count = 0);
        // ��������
        // @ Arg1 : �������ޒ��_���
        HRESULT Write(void* vertex);

    private:
        // ���_�o�b�t�@���쐬����
        // @ Arg1 : 
        // @ Arg2 : 
        // @ Arg3 : 
        HRESULT CreateVertexBuffer(const void* vertex, uint size, uint count, bool isWrite);
        // �C���f�b�N�X�o�b�t�@���쐬����
        // @ Arg1 : 
        // @ Arg2 : 
        // @ Arg3 : 
        HRESULT CreateIndexBuffer(const void* index, uint size, uint count);


        BaseHandle<DirectXRender> m_directxRender;  // �`��Ώ�
        ComPtr<ID3D11Buffer> m_vertexBuffer; // ���_�o�b�t�@
        uint m_vertexSize;                   // ���_�o�b�t�@�̃T�C�Y        
        uint m_vertexCount;                  // ���_�o�b�t�@�̐�
        ComPtr<ID3D11Buffer> m_indexBuffer; // �C���f�b�N�X�o�b�t�@
        uint m_indexSize;                   // �C���f�b�N�X�o�b�t�@�̃T�C�Y
        uint m_indexCount;                  // �C���f�b�N�X�o�b�t�@�̐�
        D3D11_PRIMITIVE_TOPOLOGY m_topology; // �`�����
    };
}


#endif // !I_MESHBUFFER_H
