#ifndef I_COMPOINTER_H
#define I_COMPOINTER_H


template <typename T>
concept ComObject = std::derived_from<IUnknown, T> || !(std::is_pointer_v<T>); // COMオブジェクト継承コンセプト


// Comオブジェクトの解放を自動で行うクラス
// @ Temp : Com
template <ComObject Com>
class ComPtr {
public:
    // コンストラクタ
    // @ Arg1 : 初期化Comオブジェクト(デフォルト : nullptr)
    ComPtr(Com* com = nullptr);
    // デストラクタ
    ~ComPtr(void);


    // COMオブジェクトポインタ取得
    Com* const Get(void) const { return m_com; }
    // COMオブジェクトポインタ取得
    Com* operator ->(void) { return m_com; }
    // 編集可能COMオブジェクトポインタ取得
    Com** GetEditable(void) { return &m_com; }
private:
    Com* m_com;
};




// コンストラクタ
template <ComObject Com>
ComPtr<Com>::ComPtr(Com* com) 
    : m_com(com) {
}
// デストラクタ
template <ComObject Com>
ComPtr<Com>::~ComPtr(void) {
    if (m_com != nullptr) m_com->Release();
    m_com = nullptr;
}


#endif // !I_COMPOINTER_H
