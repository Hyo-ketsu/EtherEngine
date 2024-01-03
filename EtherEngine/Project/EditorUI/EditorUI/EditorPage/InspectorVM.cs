using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;
using Reactive.Bindings.Interactivity;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    internal class InspectorVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>現在参照しているオブジェクト</summary>
        public static ReactiveProperty<EtherEngine.BaseObject> InspectoObject { get; set; } = new();
    }
}
