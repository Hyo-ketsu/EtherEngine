using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, AllowMultiple = true, Inherited = false)]
    public class CreatedWindowAttribute : Attribute {
        /// <summary>コンストラクタ</summary>
        /// <param name="en">メニューに表示するウィンドウ名</param>
        /// <param name="jp">メニューに表示するウィンドウ名</param>
        public CreatedWindowAttribute(string en = "", string jp = "", string directory = "") {
            ShowText = new(en, jp);
            Directory = directory;
        }

        
        /// <summary>メニューに表示するウィンドウ名</summary>
        public EditorText ShowText { get; private set; }
        /// <summary>ウィンドウを追加する階層</summary>
        public string Directory { get; private set; }
    }
}
