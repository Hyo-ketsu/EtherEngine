using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using MahApps.Metro.Controls;


namespace EditorUI {
    /// <summary>メッセージをやり取りする型</summary>
    /// <typeparam name="MessageType">メッセージの種類</typeparam>
    /// <typeparam name="MessageData">メッセージの内容</typeparam>
    public class MessageObject<MessageType, MessageData> 
        where MessageType : Enum {
        /// <summary>コンストラクタ</summary>
        /// <param name="message"></param>
        /// <param name="data"></param>
        public MessageObject(MessageType message, MessageData data) {
            Message = message;
            Data = data;
        }


        /// <summary>メッセージの種類</summary>
        public MessageType Message { get; set; }
        /// <summary>メッセージの内容</summary>
        public MessageData Data { get; set; }
    }


    /// <summary>メッセージのみの送受信を行うクラス</summary>
    /// <typeparam name="MessageType"></typeparam>
    public static class EditorMessageQue<MessageType> where MessageType : class {
        /// <summary>エンジン側でエンジンのメッセージを送信する</summary>
        /// <param name="message">送信するメッセージ</param>
        public static void AddEngineMessage(MessageType message) {
            lock (ms_engineLockObject) {
                ms_engineMessages.Add(message);
            }
        }
        /// <summary>エンジン側でUIのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        /// <param name="select">選択したメッセージの未取得する</param>
        public static MessageType? GetEngineMessage(MessageType? select = null) {
            //----- 変数宣言
            MessageType? ret = null;

            lock (ms_uiLockObject) {
                if (select == null) {
                    //----- 何らかのメッセージを取得、削除。
                    if (ms_uiMessages.Count > 0) {
                        ret = ms_uiMessages[0];
                        ms_uiMessages.RemoveAt(0);
                    }
                }
                else {
                    //----- 指定したメッセージのみ取得、削除
                    for (int i = 0; i < ms_uiMessages.Count; i++) {
                        if (ms_uiMessages[i] == select) {
                            ret = ms_uiMessages[i];
                            ms_uiMessages.RemoveAt(1);
                            break;
                        }
                    }
                }
            }

            return ret;
        }


        /// <summary>UI側からUIメッセージを送信する</summary>
        /// <param name="message">送信するメッセージ</param>
        internal static void AddUIMessage(MessageType message) {
            lock (ms_uiLockObject) {
                ms_uiMessages.Add(message);
            }
        }
        /// <summary>UI側でエンジンのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        internal static MessageType? GetUIMessage() {
            //----- 変数宣言
            MessageType? ret = null;

            lock (ms_engineLockObject) {
                //----- 取得、削除を行えるなら行う
                if (ms_engineMessages.Count > 0) {
                    ret = ms_engineMessages[0];
                    ms_engineMessages.RemoveAt(0);
                }
            }

            return ret;
        }



        /// <summary>保持しているエンジン側メッセージ</summary>
        private static List<MessageType> ms_engineMessages = new();
        /// <summary>保持しているUI側メッセージ</summary>
        private static List<MessageType> ms_uiMessages = new();
        /// <summary>エンジン側ロックに使用するオブジェクト</summary>
        private static object ms_engineLockObject = new();
        /// <summary>UI側ロックに使用するオブジェクト</summary>
        private static object ms_uiLockObject = new();
    }
    /// <summary>メッセージの送受信を行うクラス</summary>
    /// <typeparam name="MessageType"></typeparam>
    public static class EditorMessageQue<MessageType, MessageData> 
        where MessageType : Enum where MessageData : class {
        /// <summary>エンジン側でエンジンのメッセージを送信する</summary>
        /// <param name="message">送信するメッセージ</param>
        public static void AddEngineMessage(MessageObject<MessageType, MessageData> message) {
            lock (ms_engineLockObject) {
                ms_engineMessages.Add(message);
            }
        }
        /// <summary>エンジン側でUIのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        public static MessageObject<MessageType, MessageData>? GetEngineMessage() {
            //----- 変数宣言
            MessageObject<MessageType, MessageData>? ret = null;

            lock (ms_uiLockObject) {
                //----- 何らかのメッセージを取得、削除。
                if (ms_uiMessages.Count > 0) {
                    ret = ms_uiMessages[0];
                    ms_uiMessages.RemoveAt(0);
                }
            }

            return ret;
        }
        /// <summary>エンジン側でUIのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        /// <param name="select">選択したメッセージの未取得する</param>
        public static MessageObject<MessageType, MessageData>? GetEngineMessage(MessageType select) {
            //----- 変数宣言
            MessageObject<MessageType, MessageData>? ret = null;

            lock (ms_uiLockObject) {
                //----- 指定したメッセージのみ取得、削除
                for (int i = 0; i < ms_uiMessages.Count; i++) {
                    if (ms_uiMessages[i].Message.Equals(select)) {
                        ret = ms_uiMessages[i];
                        ms_uiMessages.RemoveAt(i);
                        break;
                    }
                }
            }

            return ret;
        }


        /// <summary>UI側からUIメッセージを送信する</summary>
        /// <param name="message">送信するメッセージ</param>
        internal static void AddUIMessage(MessageObject<MessageType, MessageData> message) {
            lock (ms_uiLockObject) {
                ms_uiMessages.Add(message);
            }
        }
        /// <summary>UI側でエンジンのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        internal static MessageObject<MessageType, MessageData>? GetUIMessage() {
            //----- 変数宣言
            MessageObject<MessageType, MessageData>? ret = null;

            lock (ms_engineLockObject) {
                //----- 取得、削除を行えるなら行う
                if (ms_engineMessages.Count > 0) {
                    ret = ms_engineMessages[0];
                    ms_engineMessages.RemoveAt(0);
                }
            }

            return ret;
        }
        /// <summary>UI側でエンジンのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        /// <param name="select">選択したメッセージの未取得する</param>
        public static MessageObject<MessageType, MessageData>? GetUIMessage(MessageType select) {
            //----- 変数宣言
            MessageObject<MessageType, MessageData>? ret = null;

            lock (ms_engineLockObject) {
                //----- 指定したメッセージのみ取得、削除
                for (int i = 0; i < ms_uiMessages.Count; i++) {
                    if (ms_uiMessages[i].Message.Equals(select)) {
                        ret = ms_uiMessages[i];
                        ms_uiMessages.RemoveAt(i);
                        break;
                    }
                }
            }

            return ret;
        }


        /// <summary>保持しているエンジン側メッセージ</summary>
        private static List<MessageObject<MessageType, MessageData>> ms_engineMessages = new();
        /// <summary>保持しているUI側メッセージ</summary>
        private static List<MessageObject<MessageType, MessageData>> ms_uiMessages = new();
        /// <summary>エンジン側ロックに使用するオブジェクト</summary>
        private static object ms_engineLockObject = new();
        /// <summary>UI側ロックに使用するオブジェクト</summary>
        private static object ms_uiLockObject = new();
    }
}
