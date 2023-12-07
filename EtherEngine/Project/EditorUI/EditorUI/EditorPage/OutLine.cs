using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    internal class OutLineVM : INotifyCollectionChanged {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;
    }
}
