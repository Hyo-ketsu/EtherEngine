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
                    if (LockObject == null) {
                        LockObject = new();
                    }
                }

                return Instance;
            }
        }


        /// <summary>ログを追加する</summary>
        /// <param name="addLog">追加するログ</param>
        public void AddLog(EditorLog addLog) {
            lock (LockObject) {
                Logs.Add(addLog);
            }
        }
        /// <summary>保持しているログをすべて削除する</summary>
        public void DeleteLog() {
            lock (LockObject) {
                Logs.Clear();
            }
        }


        /// <summary>ログが更新されたかを表す(フラグが立っていれば折る)</summary>
        /// <returns></returns>
        internal bool GetIsUpdate() {
            var ret = m_isUpdate;
            m_isUpdate = false;
            return ret;
        }


        /// <summary>保持しているログ</summary>
        public ReactiveCollection<EditorLog> Logs { get; private set; } = new();
        /// <summary>保持しているインスタンス</summary>
        private static LogSystem Instance { get; set; } = new();
        /// <summary>ロックオブジェクト</summary>
        private static object LockObject { get; set; } = new ();
        /// <summary>ログが（追加・削除）更新されたか</summary>
        private bool m_isUpdate = false;
    }
}
