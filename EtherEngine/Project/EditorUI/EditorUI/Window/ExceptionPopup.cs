using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    public class ExceptionPopupVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public ExceptionPopupVM() {
            CloseWindow.Subscribe(x => ((System.Windows.Window)x)?.Close());
        }


        /// <summary>自身を閉じる</summary>
        public ReactiveCommand CloseWindow { get; } = new ReactiveCommand();
        /// <summary>表示テキスト</summary>
        public ReactiveProperty<string> ShowText { get; set; } = new();
    }
}
