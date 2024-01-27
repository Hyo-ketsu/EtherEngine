using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Build.Framework;
using Newtonsoft.Json.Serialization;


namespace EditorUI {
    public class GameLoaderLogger : ILogger {
        public void Initialize(IEventSource eventSource) {
            eventSource.AnyEventRaised += EventSource_AnyEventRaised;
        }


        /// <summary>ログ追加時</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void EventSource_AnyEventRaised(object sender, BuildEventArgs e) {
            //----- ログを取得してリストに追加
            lock (LockObject) {
                //----- 変数宣言
                MessageType messageType = MessageType.BuildMessage; // デフォルトは何ら問題ないメッセージを設定

                //----- エラー
                if (e is BuildErrorEventArgs) {
                    messageType = MessageType.Error;
                }
                //----- 警告
                if (e is BuildWarningEventArgs) {
                    messageType = MessageType.Warning;
                }

                //----- ログの追加
                Logs.Add(new EditorLog(messageType, e.Message));
            }
        }


        /// <summary>シャットダウン時の処理</summary>
        public void Shutdown() {
        }


        /// <summary>ロック用オブジェクト</summary>
        public object LockObject { get; set; } = new();
        /// <summary>保持しているログ一覧</summary>
        public List<EditorLog> Logs { get; private set; } = new();

        public LoggerVerbosity Verbosity { get; set; }
        public string Parameters { get; set; }
    }
}
