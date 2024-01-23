using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace EditorUI {
    /// <summary>インスペクターで使用する関数</summary>
    public static class InspectorUtility {
        /// <summary>「m_変数名」,「_変数名」を取り除き、名前をアッパーキャメルに変更します</summary>
        /// <param name="fieldName">修正前のフィールド名</param>
        /// <returns></returns>
        public static string GetNonDecorationFieldName(in string fieldName) {
            //----- 変数宣言
            string ret = fieldName;

            //----- 頭の「m_変数名」,「_変数名」の削除
            if (ret[0] == '_') {
                ret = ret.Remove(0, 1);
            }
            if (ret[0] == 'm' && ret[1] == '_') {
                ret = ret.Remove(0, 2);
            }

            //----- 頭の小文字を大文字にする
            if (char.IsLower(ret[0])) {
                var copyText = ret.Remove(0, 1);
                var upperChar = char.ToUpper(ret[0]);
                ret = upperChar + copyText;
            }

            return ret;
        }
    }
}
