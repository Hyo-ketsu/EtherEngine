﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    internal static class UIMainFunction {
        /// <summary>メインループ</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public static void MainFunction(object? sender, EventArgs e) {
            //----- ウィンドウを取得、表示する
            {
                var window = CreateWindow.GetCreateWindow();
                window?.GetUILock().Item2.Show();
            }
        }
    }
}