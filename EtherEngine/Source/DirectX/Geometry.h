#ifndef I_GEOMETRY_H
#define I_GEOMETRY_H
#include <DirectX/Texture.h>


namespace EtherEngine {
    class Geometory {
        // ����������
        static void Init(void);
        // �I������
        static void Uninit(void);


        // ���_�V�F�[�_�[���Z�b�g����
        // @ Arg1 : ���_�V�F�[�_�[�̃|�C���^
        static void SetVertexShader()

        // ���_�V�F�[�_���Z�b�g����
        static void SetPixelShader()
    };
}


#endif // !I_GEOMETRY_H
