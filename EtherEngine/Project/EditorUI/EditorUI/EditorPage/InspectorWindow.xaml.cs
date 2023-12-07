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
    /// InspectorWindow.xaml の相互作用ロジック
    /// </summary>
    [CreatedWindow(en: "Inspector", jp: "詳細")]
    public partial class InspectorWindow : UserControl {
        public InspectorWindow() {
            InitializeComponent();
        }
    }
}
