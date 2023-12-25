#include <EngineLibrary/IDClass.h>
#include <Base/RandomManage.h>


#pragma managed
//----- IDClass 定義
namespace EtherEngine {
    // デフォルトコンストラクタ
    IDClass::IDClass(void) 
        : m_id(0) {
        //----- 0 以外の番号になるまで乱数生成する
        while (m_id == 0) {
            m_id = RandomManage<IDNumberType>::Get()->GetRandom();
        }
    }
    // IDを生成せず取得するコンストラクタ
    IDClass::IDClass(IDNumberType copyId) 
        : m_id(copyId) {
    }


    // IDを取得する
    IDNumberType IDClass::ID::get(void) {
        return m_id;
    }
}
