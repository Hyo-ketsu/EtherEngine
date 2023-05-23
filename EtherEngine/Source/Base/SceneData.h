#ifndef I_SCENEDATA_H
#define I_SCENEDATA_H


namespace EtherEngine {
    // �eScene�p�̏����Ǘ�����N���X
    //�i�ʌɂ����̂�GameObject�Ƃ��ɃR���|�W�V���������ۂɃf�[�^�݂̂�ێ��ł��Ă�������ǂ����߁j
    class SceneData {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �V�[����
        SceneData(const std::string& sceneName);

    private:
        static std::unordered_map<std::string, unsigned long long> ms_sceneNumber;  // �V�[�����ɑΉ������ԍ�
    };
}


#endif // !I_SCENEDATA_H
