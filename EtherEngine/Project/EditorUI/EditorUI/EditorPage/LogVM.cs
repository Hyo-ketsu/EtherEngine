using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Reactive.Bindings;


namespace EditorUI {
    public class Log : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public Log() {
            //----- ログ設定
            var logs = LogSystem.Get.GetAllLog();
            foreach (var log in logs) {
                Logs.Add(new(log));
            }

            //----- イベント登録
            ClearButtonCommand.Subscribe(() => { Logs.Clear(); });
            LogSystem.Get.AddLogEvent += (_, addLog) => {
                Application.Current.Dispatcher.Invoke(() => {
                    Logs.Add(new(addLog));
                });
            };
        }


        /// <summary>保持しているログ</summary>
        public static ReactiveCollection<ReactiveProperty<EditorLog>> Logs { get; private set; } = new();
        /// <summary>Clearボタンが押された際の処理</summary>
        public ReactiveCommand ClearButtonCommand { get; private set; } = new();
    }
}
