#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/BaseDefines.h>


//----- IDClass 定義
namespace EtherEngine {
    // IDを管理・表現するクラス
    public ref class IDClass {
    public:
        // デフォルトコンストラクタ
        IDClass(void);
        // IDを生成せず取得するコンストラクタ
        IDClass(IDNumberType copyId);


        // IDを取得する
        property IDNumberType ID {
            IDNumberType get(void);
        }

    private:
        IDNumberType m_id;  // id番号
    };
}


#endif // !I_IDCLASS_H
