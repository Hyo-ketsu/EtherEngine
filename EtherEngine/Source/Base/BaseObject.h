#ifndef I_BASEOBJECT_H_
#define I_BASEOBJECT_H_
#include <Base/IDClass.h>
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

        // ID�Q�b�^�[
        const IDClass& GetId(void) const { return m_id; }

        // �I�u�W�F�N�g�A�N�e�B�u�Q�b�^�[
        bool GetActive(void) const { return m_isActive; }
        // �I�u�W�F�N�g�A�N�e�B�u�Z�b�^�[
        void SetActive(const bool in) { m_isActive = in; }

        // �폜�ς݃Q�b�^�[
        bool GetDelete(void) const { return m_isDelete; }


        // ���̃I�u�W�F�N�g���폜����
        void DeleteObject(void);
        // ���̃I�u�W�F�N�g���g���Ȃ������肷��
        // @ Ret  : �g�p�ł��Ȃ��Ȃ� true
        bool IsUnvalidObject(void) const;

    private:
        std::string m_name;     // �I�u�W�F�N�g��
        IDClass m_id;           // ���g��ID
        bool m_isActive;        // ���̃I�u�W�F�N�g���L����
        bool m_isDelete;        // ���̃I�u�W�F�N�g�͍폜�ς݂�
    };
}


#endif // !I_BASEOBJECT_H_
