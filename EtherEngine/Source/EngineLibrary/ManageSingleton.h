#ifndef I_MANAGESINGLETON_H
#define I_MANAGESINGLETON_H


// �V���O���g���Ƃ��Ďg�p���邽�߂̃}�N��
// @ Memo : ����X���b�h�Z�[�t�Ƃ��Ă͎�������Ă��܂���
// @ Memo : �V���O���g���Ƃ��Ē�`����N���X���Ŏg�p���Ă�������
// @ Arg1 : �V���O���g���Ƃ��Ē�`����N���X��(�� : RefHogeClass)
// @ Arg2 : ���������Ɏg�p����֐��B�󔒉�(�� : Init(1))
// @ Memo : �ȉ��g�p��
//public ref class Hoge {
//    MANAGE_SINGLETON(Hoge, Init());
//    void Init(void) { m_hoge = 1; }
//    int m_hoge;
//};
#define ETHER_ENGINE_MANAGE_SINGLETON(singletonType) \
public:\
static property singletonType^ Get {\
    public: singletonType^ get(void) { \
        if (ms_instance == nullptr) {\
            ms_instance = gcnew singletonType();\
        }\
        return ms_instance;\
    }\
    protected: void set(singletonType^ value) {\
        ms_instance = value;\
    }\
}\
static void Delete(void) {\
    ms_instance = nullptr;\
}\
protected:\
singletonType(void);\
private:\
static singletonType^ ms_instance = nullptr\


#endif // !I_MANAGESINGLETON_H
