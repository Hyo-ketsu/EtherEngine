using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    ///// <summary></summary>
    //public class ExplorerSetCurrentDirectory {
    //    public ExplorerSetCurrentDirectory(string setDirectory) {

    //    }
    //}


    ///// <summary></summary>
    //public enum ExplorerMessage {

    //}


    /// <summary>ViewModel</summary>
    internal class FileExplorerVM : INotifyCollectionChanged {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;
    }
}
