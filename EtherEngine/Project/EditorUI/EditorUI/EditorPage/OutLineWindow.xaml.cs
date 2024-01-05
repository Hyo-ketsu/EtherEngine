using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;
using AvalonDock.Layout;
using MahApps.Metro.Controls;


namespace EditorUI {
    /// <summary>
    /// OutLineWindow.xaml の相互作用ロジック
    /// </summary>
    [CreatedWindow(en: "Scene outline window", jp: "シーン アウトラインウィンドウ")]
    public partial class OutLineWindow : UserControl {
        public OutLineWindow() {
            InitializeComponent();

            DataContext = new OutLineVM(ObjectList);
        }


        private void SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e) {
            var item = ObjectList.SelectedItem as OldTreeViewItem;
            var baseObject = item?.TreeItem.Value as EtherEngine.BaseObject;
            if (baseObject != null) {
                InspectorVM.InspectoObject.Value = baseObject;
            }
        }
    }
}
