#ifndef I_WINDOW_H
#define I_WINDOW_H


//----- Window ��`
namespace EtherEngine {
    // �E�B���h�E��\������N���X
    class Window {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �E�B���h�E�̖��O
        Window(const std::string& name);


        // �E�B���h�E�n���h���Q�b�^�[
        const HWND& GetHWND(void) const { return m_hwnd.value(); }
        // �E�B���h�E�n���h���Z�b�^�[
        void SetHWND(HWND in) { m_hwnd.emplace(in); }

        // �E�B���h�E�T�C�Y�Q�b�^�[
        const Eigen::Array2<int>& GetWindSize(void) const { return m_windowSize; }
        // �E�B���h�E�T�C�Y�Z�b�^�[
        void SetWindSize(const Eigen::Array2<int>& in) { m_windowSize = in; }


    protected:
        std::string m_name;               // �E�B���h�E�̖��O 
        std::optional<HWND> m_hwnd;       // �E�B���h�E�n���h��
        Eigen::Array2<int>  m_windowSize; // �E�B���h�E�̃T�C�Y
    };
}


#endif // !I_WINDOW_H
