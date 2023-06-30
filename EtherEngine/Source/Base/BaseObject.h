#ifndef I_BASEOBJECT_H_
#define I_BASEOBJECT_H_

// @ MEMO : �t�@�C���p�X���܂߂邩�����H


//----- BaseObject �錾
namespace EtherEngine {
    // GameObject���A�O���o��
    class BaseObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �I�u�W�F�N�g��
        BaseObject(const std::string& name);


        // �I�u�W�F�N�g���Q�b�^�[
        const std::string& GetName(void) const { return m_name; }
        // �I�u�W�F�N�g���Z�b�^�[
        void SetName(const std::string& in) { m_name = in; }
        // �I�u�W�F�N�g���A�N�Z�T�[
        std::string& AccessName(void) { return m_name; }
        

    private:
        std::string m_name;     // �I�u�W�F�N�g��
    };
}


#endif // !I_BASEOBJECT_H_
