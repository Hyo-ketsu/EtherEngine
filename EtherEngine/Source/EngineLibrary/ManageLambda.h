#ifndef I_MANAGELAMBDA_H
#define I_MANAGELAMBDA_H


// �}�l�[�W�����_��`�}�N��
#define ETHER_ENGINE_MANAGE_LAMBDA_DEFINE(LambdaName, EventArgsType, Function)\
namespace EtherEngine {\
    namespace Lambda {\
        private ref class LambdaName {\
        public:\
            void UseLambda(System::Object^ s, EventArgsType e) {\
                Function\
            }\
        };\
    }\
}\


// �}�l�[�W�����_�g�p�}�N��
#define ETHER_ENGINE_MANAGE_LAMBDA_USE(EventHandlerType, LambdaName)\
gcnew EventHandlerType(gcnew EtherEngine::Lambda::LambdaName(), &EtherEngine::Lambda::LambdaName::UseLambda)


#endif // !I_MANAGELAMBDA_H
