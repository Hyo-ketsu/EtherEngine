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
        /// <param name="directory">ウィンドウを追加する階層(記述無し可)</param>
        /// <param name="isAbbreviation">「Window」を無視するか</param>
        public UseWindowAttribute(string directory = "", bool isAbbreviation = true) { 
            Directory = directory; 
            IsAbbreviation = isAbbreviation;
        }


        /// <summary>ウィンドウを追加する階層(記述無し可)</summary>
        public string Directory { get; private set; }
        /// <summary>「Window」を無視するか</summary>
        public bool IsAbbreviation { get; private set; }
    }
}
