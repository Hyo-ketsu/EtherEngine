using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    public class Log : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public Log() {
            //----- イベント登録
            ClearButtonCommand.Subscribe(() => { LogSystem.Get().DeleteLog(); });

            LogSystem.Get().AddLog(new(MessageType.Info, "Hoge")); // @ MEMO : テスト
        }


        /// <summary>保持しているログ</summary>
        public ReactiveCollection<EditorLog> Logs => LogSystem.Get().Logs;
        /// <summary>Clearボタンが押された際の処理</summary>
        public ReactiveCommand ClearButtonCommand { get; private set; } = new();
    }
}
