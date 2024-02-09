using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


// @ MEMO : 現在ユーザー定義のエディター拡張は考えていません。時間があればやる


namespace EditorUI {
    /// <summary>エディター用の初期化を行うUtilityクラス</summary>
    internal static class EditorExtensionInit {
        /// <summary>Inspector用の拡張を取得する関数</summary>
        /// <param name="loadAssembly"></param>
        public static void Init(Assembly loadAssembly) {
            //----- エディター上の全型を取得し、InspectorExtensionを継承したクラスを取得する
            foreach (var type in loadAssembly.GetTypes()) {
                //----- InspectorExtensionを継承しているか
                if (type.IsSubclassOf(typeof(InspectorExtension)) == false) continue;

                //----- 属性用変数宣言
                bool isHeader   = false;    // Header表示の属性は既に追加されたか
                bool isTypeShow = false;    // TypeShow表示の属性は既に追加されたか
                bool isFooter   = false;    // Footer表示の属性は既に追加されたか

                //----- Inspector用の何らかの属性が付与されているか
                foreach (var attribute in type.GetCustomAttributes(false)) {
                    if (attribute is InspectorTypeBaseAttribute) {
                        //----- 付与されている。各表示（とそれ用の属性）を取得、判定、追加する
                        if (isHeader == false) {
                            var inspectorTypeHeaderAttribute = attribute as InspectorTypeHeaderAttribute;
                            inspectorTypeHeaderAttribute?.AddInspectorExtension();
                            isHeader = true;
                            continue;
                        }
                        if (isTypeShow == false) {
                            var inspectorTypeTypeShowAttribute = attribute as InspectorTypeTypeShowAttribute;
                            inspectorTypeTypeShowAttribute?.AddInspectorExtension();
                            isTypeShow = true;
                            continue;
                        }
                        if (isFooter == false) {
                            var inspectorTypeFooterAttribute = attribute as InspectorTypeFooterAttribute;
                            inspectorTypeFooterAttribute?.AddInspectorExtension();
                            isFooter = true;
                            continue;
                        }
                    }
                }
            }
        }
    }
}
