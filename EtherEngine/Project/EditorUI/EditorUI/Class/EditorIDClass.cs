using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace EditorUI {
    /// <summary>ID</summary>
    public class EditorIDClass {
        /// <summary>IDを生成するコンストラクタ</summary>
        public EditorIDClass() {
            //----- 変数宣言
            int index = 0;

            while (true) {
                //----- 番号生成
                ID = ((uint)Random.Next()); // intをuintにキャストしているため負値の際正常な値にはならないが、一意の整数であればよいのでこのまま

                //----- 例外的に生成IDが 0 の場合は即座に生成しなおす
                if (ID == 0) goto END;

                //----- 既に使用した番号として登録されているか
                foreach (var useNumber in UseNumbers) {
                    if (ID == useNumber) {
                        //----- 使用されている。即別の番号を生成しなおす
                        goto END;
                    }
                    if (ID > useNumber) {
                        //----- 使用されていない。インデックス取得
                        index = UseNumbers.IndexOf(useNumber);
                        break;
                    }
                }

                //----- 番号未使用。新しく追加
                UseNumbers.Insert(index, ID);
                break;

                //----- 番号使用時
                END: { }
            }
        }
        /// <summary>IDをコピーするコンストラクタ</summary>
        /// <param name="id"></param>
        public EditorIDClass(uint id) {
            ID = id;    
        }


        /// <summary>保持しているID</summary>
        public uint ID { get; private set; }
        /// <summary>保持している乱数生成器</summary>
        private static Random Random { get; set; } = new();
        /// <summary>既に使用した番号(昇順)</summary>
        private static List<uint> UseNumbers { get; set; } = new();
    }
}
