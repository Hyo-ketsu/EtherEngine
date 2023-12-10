#ifndef I_MESSAGEQUE_H
#define I_MESSAGEQUE_H
#include <Base/Mutex.h>


namespace EtherEngine {
    // メッセージとして使用できるかのコンセプト
    // @ Memo : 算術型、修飾のない型かつ、ムーブもしくはコピーが可能か
    template <typename T>
    concept MessageTypeConcept = std::is_arithmetic_v<T> || std::is_object_v<T> &&
        std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>;
}


//----- MessageQue 宣言
namespace EtherEngine {
    // スレッドセーフにメッセージパッシングを行えるメッセージキュー
    // @ Temps: コピーコンストラクタかムーブコンストラクタが定義されているメッセージ型
    // @ Memo : テンプレート引数に同じ型が複数あることは想定していません
    template <MessageTypeConcept ...ArgsType>
    class MessageQue {
    public:
        // コンストラクタ
        MessageQue(void) {}
        // デストラクタ
        ~MessageQue(void) {}


        // メッセージを送信する
        // @ Arg1 : メッセージ
        template <MessageTypeConcept MessageType>
        void Send(const MessageType& message);
        // メッセージを取得する
        // @ Ret  : メッセージ
        std::optional<std::variant<ArgsType...>> Get(void);
        // 現在のメッセージ数を取得する
        // @ Ret  : 保有メッセージ数
        uint GetMessageCount(void);

    private:
        std::vector<std::variant<ArgsType...>> m_messages;  // 格納メッセージ
        std::shared_ptr<Mutex> m_mutex;
    };
}




//----- MessageQue 定義
namespace EtherEngine {
    // メッセージを送信する
    // @ Arg1 : メッセージ
    template <MessageTypeConcept ...ArgsType>
    template <MessageTypeConcept MessageType>
    void MessageQue<ArgsType...>::Send(const MessageType& message) {
        //----- ロック取得
        auto lock = m_mutex->KeySpinLock();

        //----- メッセージ追加
        m_messages.push_back(std::variant<ArgsType...>(message));
    }
    // メッセージを取得する
    // @ Ret  : メッセージ
    template <MessageTypeConcept ...ArgsType>
    std::optional<std::variant<ArgsType...>> MessageQue<ArgsType...>::Get(void) {
        //----- ロック取得
        auto lock = m_mutex->KeySpinLock();
        
        //----- メッセージ取得
        if (m_messages.size() < 1) {
            //----- メッセージなし
            return std::optional<std::variant<ArgsType...>>();
        }
        else {
            //----- メッセージあり。取得して返却
            std::optional<std::variant<ArgsType...>> ret = m_messages.front();
            m_messages.erase(m_messages.begin());
            return ret;
        }
    }
    // 現在のメッセージ数を取得する
    // @ Ret  : 保有メッセージ数
    template <MessageTypeConcept ...ArgsType>
    uint MessageQue<ArgsType...>::GetMessageCount(void) {
        //----- ロック取得
        auto lock = m_mutex->KeySpinLock();

        //----- 返却
        return m_messages.size();
    }
}


#endif // !I_MESSAGEQUE_H
