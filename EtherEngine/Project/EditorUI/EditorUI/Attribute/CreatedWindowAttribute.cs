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
        public CreatedWindowAttribute(string en = "", string jp = "") {
            ShowText = new(en, jp);
        }


        /// <summary>メニューに表示するウィンドウ名</summary>
        public EditorText ShowText { get; private set; } 
    }
}
