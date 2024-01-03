using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>
    /// ObjectReference.xaml の相互作用ロジック
    /// </summary>
    public partial class ObjectReference : UserControl, INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public ObjectReference() {
            //----- 初期化
            InitializeComponent();

            //----- イベント設定
            ObjectRefarence.Subscribe(_ => { NameChange(); });

            //----- DataContextへの追加
            DataContext = this;
        }


        /// <summary>オブジェクトをキャストして取得する</summary>
        /// <typeparam name="ObjectType">キャストして取得されたオブジェクト（null許容）</typeparam>
        /// <returns></returns>
        public ObjectType? GetObject<ObjectType>() where ObjectType : EtherEngine.BaseObject {
            return ObjectRefarence.Value as ObjectType;
        }
        /// <summary>オブジェクトを与える</summary>
        public EtherEngine.BaseObject Object {
            set { 
                ObjectRefarence.Value = value;
                ObjectType.Value = value.GetType();
                NameChange();
            }
        }


        /// <summary>表示オブジェクト名を変更する</summary>
        private void NameChange() {
            //----- 変数宣言
            string name;

            //----- 与える名前を決定
            do {
                //----- オブジェクトが設定されていないのであればnull表示
                if (ObjectRefarence.Value == null) {
                    name = new("(Null Object)");
                    break;
                }

                //----- 型名表示
                // @ MEMO : 仮措置
                name = ObjectType.Value.Name;
            } while (false);

            //----- 設定する
            ObjectName.Text = name;
        }


        /// <summary>保持している参照</summary>
        public ReactiveProperty<EtherEngine.BaseObject> ObjectRefarence { get; set; } = new();
        /// <summary>保持しているオブジェクトの型</summary>
        public ReactiveProperty<Type> ObjectType { get; set; } = new();
    }
}
