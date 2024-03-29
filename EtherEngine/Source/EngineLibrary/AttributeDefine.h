#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


#pragma managed
namespace EtherEngine {
    //----- 入出力属性
    namespace Attribute {
        // 入出力を行うための属性
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class OutputAttribute : System::Attribute {
        };
        // 入出力が行われるものを入出力しないための属性
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class NoOutputAttribute : System::Attribute {
        };
    }
    //----- BaseObject制御属性
    namespace Attribute {
        // BaseObjectを直接入出力する属性
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class BaseObjectSerializeAttribute : System::Attribute {
        };
        //// BaseObjectの参照を保持するの属性
        //[System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        //public ref class NoOutputAttribute : System::Attribute {
        //};
    }
    //----- エディター表示属性
    // @ Memo : エディター関連の処理はEngineLibraryに記述すべきではないと思いますがただの属性なので問題ないです
    namespace Attribute {
        // 入出力がされるがエディターに表示しないための属性
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class NonEditorOutputAttribute : System::Attribute {
        };
    }
}


#endif // !I_ATTRIBUTEDEFINE_H
