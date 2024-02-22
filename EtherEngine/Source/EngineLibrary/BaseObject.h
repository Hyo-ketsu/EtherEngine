#ifndef I_BASEOBJECT_H
#define I_BASEOBJECT_H
#include <EngineLibrary/IDClass.h>
#include <EngineLibrary/AttributeDefine.h>


#pragma managed
namespace EtherEngine {
    // 汎用的にエンジン内で扱われるオブジェクト
    public ref class BaseObject {
    public:
        // コンストラクタ
        BaseObject(void);
        // コンストラクタ
        // @ Arg1 : コピーID
        BaseObject(IDClass^ id);

        // ID
        property IDClass^ ID {
            IDClass^ get(void) { return gcnew IDClass(m_id->ID); }
        }
        // アクティブ
        property bool IsActive {
            bool get(void) { return m_isActive; }
            void set(bool value) { m_isActive = value; }
        }
        // 既に削除されているか
        property bool IsDelete {
            bool get(void) { return m_isDelete; }
        }
        // 名前
        property System::String^ Name {
            System::String^ get(void) { return m_objectName; }
            void set(System::String^ value) { m_objectName = value; }
        }


        // このオブジェクトを削除する
        void DeleteObject(void);
        // このオブジェクトが使えないか判定する
        // @ Ret  : 使用できないなら true
        bool IsUnvalidObject(void);

        //----- イベント定義
#ifdef _EDITOR
        event System::EventHandler^ UpdateEvent;    // 更新時に発火するイベント
        // イベントの発火を行う
        void UpdateEventIgnition(System::EventArgs^ e) { UpdateEvent(this, e); }
#endif // _EDITOR

    private:
        [Attribute::OutputAttribute, Attribute::NonEditorOutputAttribute] 
            bool m_isActive;    // 有効になっているか
        bool m_isDelete;        // 削除されているか
        IDClass^ m_id;      // id
        [Attribute::OutputAttribute, Attribute::NonEditorOutputAttribute] 
            System::String^ m_objectName; // オブジェクトの名前
    };
}


#endif // !I_USERBASEOBJECT_H
