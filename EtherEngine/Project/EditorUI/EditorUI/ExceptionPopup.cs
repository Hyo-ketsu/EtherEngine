using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    public class ExceptionPopupVM {
        public ReactiveProperty<string> ShowText { get; set; } = new();
    }
}
