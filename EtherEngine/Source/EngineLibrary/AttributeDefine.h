#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


#pragma managed
namespace EtherEngine {
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
}


#endif // !I_ATTRIBUTEDEFINE_H
