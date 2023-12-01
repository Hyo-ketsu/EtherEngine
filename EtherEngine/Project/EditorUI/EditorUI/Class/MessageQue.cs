using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;


namespace EditorUI {
    /// <summary>メッセージの送受信を行うクラス</summary>
    /// <typeparam name="MessageType"></typeparam>
    public static class MessageQue<MessageType> where MessageType : class {
        /// <summary>エンジン側でエンジンのメッセージを送信する</summary>
        /// <param name="message">送信するメッセージ</param>
        public static void AddEngineMessage(MessageType message) {
            lock (ms_engineLockObject) {
                ms_engineMessages.Add(message);
            }
        }
        /// <summary>エンジン側でUIのメッセージを取得する</summary>
        /// <returns>取得したメッセージ(Null含む)</returns>
        public static MessageType? GetEngineMessage() {
            //----- 変数宣言
            MessageType? ret = null;

            lock (ms_uiLockObject) {
                //----- 取得、削除を行えるなら行う
                if (ms_uiMessages.Count > 0) {
                    ret = ms_uiMessages[0];
                    ms_uiMessages.RemoveAt(0);
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
}
