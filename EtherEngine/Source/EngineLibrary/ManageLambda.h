#ifndef I_MANAGELAMBDA_H
#define I_MANAGELAMBDA_H


// マネージラムダ定義マクロ
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


// マネージラムダ使用マクロ
#define ETHER_ENGINE_MANAGE_LAMBDA_USE(EventHandlerType, LambdaName)\
gcnew EventHandlerType(gcnew EtherEngine::Lambda::LambdaName(), &EtherEngine::Lambda::LambdaName::UseLambda)


#endif // !I_MANAGELAMBDA_H
