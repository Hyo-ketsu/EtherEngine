using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using Reactive.Bindings;
using Reactive.Bindings.Interactivity;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    internal class InspectorVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        /// <param name="showStackPanel">コントロールの表示に使用するstackパネル</param>
        public InspectorVM(StackPanel showStackPanel) {
            Inspector = showStackPanel;

            InspectoObject.Subscribe(baseObject => {
                if (baseObject != null) {
                    CreateInspectorItem(baseObject);
                }
                else {
                    Inspector.Children.Clear();
                }
            });
        }


        /// <summary>インスペクター用のUIを生成する</summary>
        public void CreateInspectorItem(EtherEngine.BaseObject baseObject) {
            //----- まずはClearする
            Inspector.Children.Clear();

            //----- 追加
            Inspector.Children.Add(InspectorUtility.GetControl(baseObject));
        }


        /// <summary>現在参照しているオブジェクト</summary>
        public static ReactiveProperty<EtherEngine.BaseObject> InspectoObject { get; set; } = new();


        /// <summary>現在保持しているインスペクターの表示エリア</summary>
        private StackPanel Inspector { get; set; }
    }
}
