#ifndef I_WINDOW_H
#define I_WINDOW_H
#include <DirectX/DirectX.h>


//----- Window ��`
namespace EtherEngine {
    // �E�B���h�E��\������N���X
    class Window {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �E�B���h�E�̖��O
        Window(const std::string& name);


        // �E�B���h�E���쐬����
        bool Create_Window(void);


        // �E�B���h�E�n���h���Q�b�^�[
        const HWND& GetHWND(void) const { return m_hwnd.value(); }
        // �E�B���h�E�n���h���Z�b�^�[
        void SetHWND(HWND in) { m_hwnd.emplace(in); }

        // �E�B���h�E�T�C�Y�Q�b�^�[
        const Eigen::Array2<int>& GetWindSize(void) const { return m_windowSize; }
        // �E�B���h�E�T�C�Y�Z�b�^�[
        void SetWindSize(const Eigen::Array2<int>& in) { m_windowSize = in; }


        // �E�B���h�E�L���v�V�����̕������擾����
        // @ Ret  : ���݂̃E�B���h�E�̃L���v�V����
        std::string GetCaption(void);
        // �E�B���h�E�L���v�V�����̕�����ݒ肷��
        // @ Ret  : �L���v�V�����̐ݒ肪�ł�����
        // @ Arg1 : �ݒ肷��E�B���h�E�̃L���v�V����
        bool SetCaption(const std::string& name) { return SetCaption(name.c_str()); }
        // �E�B���h�E�L���v�V�����̕�����ݒ肷��
        // @ Ret  : �L���v�V�����̐ݒ肪�ł�����
        // @ Arg1 : �ݒ肷��E�B���h�E�̃L���v�V����
        bool SetCaption(const char* name);

    protected:
        std::string m_name;               // �E�B���h�E�̖��O 
        std::optional<HWND> m_hwnd;       // �E�B���h�E�n���h��
        Eigen::Array2<int>  m_windowSize; // �E�B���h�E�̃T�C�Y
        BaseHandle<DirectXRender> m_dxRender;
    };
}


#endif // !I_WINDOW_H
