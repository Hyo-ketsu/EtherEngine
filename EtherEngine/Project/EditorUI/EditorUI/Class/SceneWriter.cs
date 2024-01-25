using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EtherEngine;


namespace EditorUI {
    /// <summary>シーンの読み書きを行う</summary>
    public static class SceneWriter {
        /// <summary>シーン情報をJsonとして出力する</summary>
        /// <param name="scene">保存するシーン</param>
        /// <returns></returns>
        public static string SaveScene(Scene scene) {
            //----- ゲームオブジェクトをシリアライズする
            string ret = new("");
            foreach (var gameObject in GameObjectStorage.Get.GameObjects) {
                if (gameObject.)
                ret += ClassLoader.Output(gameObject);
            }

            //----- 返却
            return ret;
        }
    }
}
