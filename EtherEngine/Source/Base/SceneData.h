#ifndef I_SCENEDATA_H
#define I_SCENEDATA_H


namespace EtherEngine {
    // �eScene�p�̏����Ǘ�����N���X
    //�i�ʌɂ����̂�GameObject���ɃR���|�W�V���������ۂɃf�[�^�݂̂�ێ��ł��Ă�������ǂ����߁j
    class SceneData {
    public:
        // �R���X�g���N�^
        // @ Temp1 : Scene��
        // @ Temp2 : Scene�ԍ�
        template <const char* Name, uint Number>
        SceneData(void);

    private:

    };
}


#endif // !I_SCENEDATA_H
