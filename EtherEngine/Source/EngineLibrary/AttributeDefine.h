#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


#pragma managed
namespace EtherEngine {
    namespace Attribute {
        // ���o�͂��s�����߂̑���
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class OutputAttribute : System::Attribute {
        };


        // ���o�͂��s������̂���o�͂��Ȃ����߂̑���
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class NoOutputAttribute : System::Attribute {
        };
    }
}


#endif // !I_ATTRIBUTEDEFINE_H
