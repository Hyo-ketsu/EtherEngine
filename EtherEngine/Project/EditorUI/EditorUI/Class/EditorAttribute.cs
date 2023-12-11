using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>このウィンドウをウィンドウとして使用する属性</summary>
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]
    public class UseWindowAttribute : Attribute {
        /// <summary>コンストラクタ</summary>
        /// <param name="showName">表示するウィンドウ名(Default : クラス名表示)</param>
        /// <param name="directory">ウィンドウを追加する階層(記述無し可)</param>
        public UseWindowAttribute(string? showName = null, string directory = "") { 
            ShowName = showName;
            Directory = directory; 
        }


        /// <summary>ウィンドウの表示名</summary>
        public string? ShowName { get; set; }
        /// <summary>ウィンドウを追加する階層</summary>
        public string Directory { get; private set; }
    }
}
