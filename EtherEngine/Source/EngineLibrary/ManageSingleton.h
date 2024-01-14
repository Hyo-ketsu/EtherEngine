#ifndef I_MANAGESINGLETON_H
#define I_MANAGESINGLETON_H


// シングルトンとして使用するためのマクロ
// @ Memo : 現状スレッドセーフとしては実装されていません
// @ Memo : シングルトンとして定義するクラス内で使用してください
// @ Arg1 : シングルトンとして定義するクラス名(例 : RefHogeClass)
// @ Arg2 : 初期化時に使用する関数。空白可(例 : Init(1))
// @ Memo : 以下使用例
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
