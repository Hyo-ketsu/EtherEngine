#ifndef I_COMPOINTER_H
#define I_COMPOINTER_H


template <typename T>
concept ComObject = std::derived_from<IUnknown, T> || !(std::is_pointer_v<T>); // COM�I�u�W�F�N�g�p���R���Z�v�g


// Com�I�u�W�F�N�g�̉���������ōs���N���X
// @ Temp : Com
template <ComObject Com>
class ComPtr {
public:
    // �R���X�g���N�^
    // @ Arg1 : ������Com�I�u�W�F�N�g(�f�t�H���g : nullptr)
    ComPtr(Com* com = nullptr);
    // �f�X�g���N�^
    ~ComPtr(void);


    // COM�I�u�W�F�N�g�|�C���^�擾
    Com* const Get(void) const { return m_com; }
    // COM�I�u�W�F�N�g�|�C���^�擾
    Com* operator ->(void) { return m_com; }
    // �ҏW�\COM�I�u�W�F�N�g�|�C���^�擾
    Com** GetEditable(void) { return &m_com; }
private:
    Com* m_com;
};




// �R���X�g���N�^
template <ComObject Com>
ComPtr<Com>::ComPtr(Com* com) 
    : m_com(com) {
}
// �f�X�g���N�^
template <ComObject Com>
ComPtr<Com>::~ComPtr(void) {
    if (m_com != nullptr) m_com->Release();
    m_com = nullptr;
}


#endif // !I_COMPOINTER_H
