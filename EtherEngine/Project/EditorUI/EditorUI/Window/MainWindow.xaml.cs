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
using MahApps.Metro.Controls;


namespace EditorUI {
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : MetroWindow {
        public MainWindow() {
            //----- メインループ開始
            CompositionTarget.Rendering += UIMainFunction.MainFunction;

            InitializeComponent();

            //----- Dockパネルを渡す
            var vm = DataContext as MainVM;
            vm.LayoutRoot = DockRoot;
            vm.DockingManager = DockManager;
        }
    }
}
