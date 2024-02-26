using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.WebSockets;
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
using EtherEngine;
using MahApps.Metro.IconPacks;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>View Model</summary>
    public class InspectorHeaderBaseObjectVM {
        /// <summary>コンストラクタ</summary>
        public InspectorHeaderBaseObjectVM() {
            ShowIconType.Value = PackIconVaadinIconsKind.SunOutline;
        }


        /// <summary>BaseObjectを設定する</summary>
        public BaseObject BaseObejct {
            set {
                m_baseObject = value;
                TypeName.Value = m_baseObject.GetType().Name;
                IsActive.Value = m_baseObject.IsActive;
                Name.Value = m_baseObject.Name;
                Name.Subscribe(value => {
                    if (m_baseObject != null) {
                        m_baseObject.Name = value;
                        m_baseObject.UpdateEventIgnition(EventArgs.Empty);
                    }
                });
                ID.Value = m_baseObject.ID.ID;
            }
        }


        /// <summary>タイプ名</summary>
        public ReactiveProperty<string> TypeName { get; private set; } = new();
        /// <summary>有効無効の設定</summary>
        public ReactiveProperty<bool> IsActive { get; private set; } = new();
        /// <summary>オブジェクト名</summary>
        public ReactiveProperty<string> Name { get; private set; } = new();
        /// <summary>ID表示</summary>
        public ReactiveProperty<ulong> ID { get; private set; } = new();
        /// <summary>表示するアイコン</summary>
        public ReactiveProperty<PackIconVaadinIconsKind> ShowIconType { get; private set; } = new();

        /// <summary>保持しているBaseObject</summary>
        private BaseObject m_baseObject;
    }


    /// <summary>
    /// InspectorHeaderBaseObject.xaml の相互作用ロジック
    /// </summary>
    public partial class InspectorHeaderBaseObject : UserControl {
        public InspectorHeaderBaseObject() {
            InitializeComponent();
        }


        public BaseObject BaseObject { 
            set { 
                var vm = DataContext as InspectorHeaderBaseObjectVM; 
                vm.BaseObejct = value;
            }
        }
    }
}
