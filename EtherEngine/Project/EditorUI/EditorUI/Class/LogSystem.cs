using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>表示するログを表現するクラス</summary>
    public class EditorLog {
        /// <summary>コンストラクタ</summary>
        /// <param name="logType">ログの種類</param>
        /// <param name="message">ログ</param>
        public EditorLog(MessageType logType, string message) {
            //----- フィールドの初期化
            LogType = logType;
            Message = message;

            //----- 時間の取得
            var time = DateTime.Now;
            LogTime = $"{time.Hour}h {time.Minute}m {time.Second}s {time.Millisecond}ms";
        }


        /// <summary>ログの内容を表す</summary>
        public MessageType LogType { get; private set; }
        /// <summary>ログを出力した時間</summary>
        public string LogTime { get; private set; }
        /// <summary>ログ</summary>
        public string Message { get; private set; }
    }


    /// <summary>ログ保持しておくクラス(シングルトン)</summary>
    public class LogSystem : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;
        /// <summary>コンストラクタ</summary>
        private LogSystem() {
        }
        /// <summary>Instance</summary>
        /// <returns></returns>
        public static LogSystem Get {
            get {
                lock (LockObject) {
                    if (Instance == null) {
                        Instance = new();
                    }
                }

                return Instance;
            }
        }


        /// <summary>ログ追加時のイベント</summary>
        public event EventHandler<EditorLog> AddLogEvent;
        /// <summary>ログ削除時のイベント</summary>
        public event EventHandler DeleteLogEvent;


        /// <summary>ログを追加する</summary>
        /// <param name="addLog">追加するログ</param>
        public void AddLog(EditorLog addLog) {
            lock (LockObject) {
                Logs.Add(addLog);
                if (AddLogEvent != null) AddLogEvent(this, addLog);
            }
        }
        /// <summary>保持しているログをすべて削除する</summary>
        public void DeleteLog() {
            lock (LockObject) {
                Logs.Clear();
                if (AddLogEvent != null) DeleteLogEvent(this, EventArgs.Empty);
            }
        }
        /// <summary>全てのログを取得する</summary>
        /// <returns></returns>
        public ReactiveCollection<EditorLog> GetAllLog() {
            lock (LockObject) {
                //----- 変数宣言
                ReactiveCollection<EditorLog> ret = new();

                //----- コピーする
                foreach (var log in Logs) {
                    ret.Add(log);
                }

                return ret;
            }
        }


        /// <summary>保持しているログ</summary>
        public List<EditorLog> Logs { get; private set; } = new();
        /// <summary>保持しているインスタンス</summary>
        private static LogSystem Instance { get; set; }
        /// <summary>ロックオブジェクト</summary>
        private static object LockObject { get; set; } = new();
    }
}
