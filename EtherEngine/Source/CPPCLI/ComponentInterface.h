#ifndef I_COMPONENTINTERFACE_H
#define I_COMPONENTINTERFACE_H


//----- 各種Interface宣言
namespace EtherEngine {
    // Serializeを行うInterface
    interface class ISerialize {
    public:
        // 外部出力する
        // @ Memo : public, もしくはEtherEngineSerializeがついていれば出力します
        // @ Ret  : 外部出力するJson文字列
        std::string Serialize(void);
        // 外部入力する
        // @ Arg1 : 読み取るJson文字列
        void Deserialize(const std::string& input);
    };
}


#endif // !I_COMPONENTINTERFACE_H
