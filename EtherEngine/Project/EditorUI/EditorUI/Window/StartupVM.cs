using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    public class StartupVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public StartupVM() {
        }


        /// <summary>保持しているパス一覧</summary>
        public ReactiveCollection<string> Paths { get; private set; } = new();
    }
}
