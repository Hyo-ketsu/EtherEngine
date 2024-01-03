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

            m_vm = new(ObjectList);
            DataContext = m_vm;
        }

        private OutLineVM m_vm;
    }
}
