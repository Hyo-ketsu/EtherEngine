using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows.Controls;
using ControlzEx.Standard;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>
    /// NumberInput.xaml の相互作用ロジック
    /// </summary>
    public partial class NumberInput : UserControl, INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        public NumberInput() {
            InitializeComponent();
            DataContext = this;
        }


        /// <summary>保持している数値を取得します</summary>
        /// <typeparam name="NumberType">数値（）</typeparam>
        /// <returns></returns>
        public Type? GetNumber<Type>() where Type : IConvertible {
            //----- 取得数値型と保持型が一致しているか
            if (NumberType == null || NumberType != typeof(Type)) {
                throw new Exception("Error! The type held and the type you are trying to retrieve do not match");
            }

            //----- 文字列を数値に変換
            return (Type)Convert.ChangeType(InputNumberText.Value, typeof(Type));
        }
        public void SetNumber(object inputNumber) {
            //----- 数値を文字列に変換
            InputNumberText.Value = inputNumber.ToString();
        }


        //----- 文字列を適切に修正する
        private void TextChanged(object sender, TextChangedEventArgs e) {
            //----- 現在実行中かのチェック
            if (IsTextChanged) return;
            IsTextChanged = true;

            //----- 変数宣言
            string newText = new("");       // 不適切な記号等を省略後
            string formatText = new("");    // 0削除後の綺麗な文字列
            bool isPeriod = false;  // ピリオドがすでに入力されていたか
            bool isMinus = false;   // マイナス記号が入力されているか
            bool isAllZero = true;  // 入力が全て0か

            //----- 入力が指定された文字以外か判定
            for (int i = 0; i < InputNumber.Text.Length; i++) { 
                //----- 文字取得
                var letter = InputNumber.Text[i];

                //----- 入力された文字列が各型と合致しているか判定
                // @ Memo : 以下の正しくない入力が検知された際その文字を省略して入力します
                //----- 0~9の数値、マイナス、小数点以外
                if (char.IsDigit(letter) == false && letter != '-' && letter != '.') continue;

                //----- 入力が0以外?
                if (letter != '0') {
                    isAllZero = true;
                }

                //----- マイナスの入力?
                if (letter == '-') {
                    //----- 型が非符号なのに - が入力されている
                    if (NumberType == typeof(uint) || NumberType == typeof(ulong) || NumberType == typeof(ushort)) continue;

                    //----- 先頭以外での - の入力
                    if (i > 0) continue;

                    //----- 入力フラグ設定
                    isMinus = true;
                }

                //----- 小数点の入力？
                if (letter == '.') {
                    //----- 非浮動小数なのに小数点(ピリオド)が入力されている
                    if (NumberType != typeof(float) && NumberType != typeof(double) && NumberType != typeof(decimal)) continue;

                    //----- すでに小数点は入力されている
                    if (isPeriod) continue;

                    //----- 先頭、もしくはマイナスの後の小数点であれば頭に0を足す
                    if (i == 0 || i == 1 && InputNumber.Text[0] ==  '-') {
                        newText += '0';
                    }

                    //----- 入力フラグ設定
                    isPeriod = true;
                }

                //----- 入力された文字は問題ない。追加
                newText += letter;
            }

            // @ MEMO : やる気があればやる
            //----- 先頭の0削除
            if (false && !(isAllZero)) {
                ////----- 全て0ではない。0削除を行う。0削除ラムダ定義
                //var zeroClear = (string text) => {
                //    //----- 変数宣言
                //    string ret = new("");
                //    bool notZero = false;

                //    foreach (var letter in text) {
                //        if (!(notZero)) {
                //            //----- 0,-以外が来るまで0を無視
                //            if (letter == '0' || letter == '-') {
                //                continue;
                //            }
                //            else {
                //                //----- 終了フラグを立てる
                //                ret += ret + letter;
                //                notZero = true;
                //            }
                //        }
                //        else {
                //            //----- 0以外が来ている。ひたすらコピー
                //            ret += ret + letter;
                //        }
                //    }

                //    return ret;
                //};

                ////----- 整数部の0削除
                //formatText = zeroClear(formatText);
                ////----- 少数部の0削除
                //string text = new("");
                //foreach (var letter in formatText.Reverse()) {
                //    text += letter;
                //}
                //formatText = zeroClear(text);
                ////----- 先ほどの反転を修正する
                //text = new("");
                //foreach (var letter in formatText.Reverse()) {
                //    text += letter;
                //}

                ////----- 少数点前
            }
            else {
                //----- 全て0。削除は行わない
                formatText = newText;
            }

            //----- 文字の入力
            InputNumber.Text = formatText;

            //----- 修正終了
            IsTextChanged = false;
        }


        /// <summary>TextChangedを行っている最中か</summary>
        private bool IsTextChanged { get; set; } = false;
        /// <summary>保持している番号型</summary>
        public Type? NumberType { get; set; }
        /// <summary>保持している数値(UI・内部用)</summary>
        public ReactiveProperty<string> InputNumberText { get; private set; } = new();
    }
}
