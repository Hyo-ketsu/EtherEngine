using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reflection.Emit;
using System.Reflection;
using Microsoft.Build.Locator;
using Microsoft.Build.Evaluation;
using Microsoft.Build.Execution;
using Microsoft.Build.Framework;
using Microsoft.Build.Logging;
using System.Threading;


namespace EditorUI {
    /// <summary>アセンブリのビルドを行う</summary>
    public class GameReloader {
        /// <summary>インスタンスの取得</summary>
        static public GameReloader Get {
            get {
                if (ms_instance == null) {
                    ms_instance = new();
                }

                return ms_instance;
            }
        }


        /// <summary>コンストラクタ</summary>
        private GameReloader() {
            //----- プロジェクト作成
            ProjectCreate();
        }


        /// <summary>プロジェクトのビルド</summary>
        /// <param name="configuration">ビルド種類</param>
        public void ProjectLoad(BuildConfiguration configuration) {
            //----- プロジェクトがなければ作成しておく
            ProjectCreate();

            //----- 変数宣言
            var sln = Directory.GetCurrentDirectory() + EditorDefine.GameSourceSolutionName;    // ソリューションのパス

            //----- プロジェクトコレクションの作成
            var projectCollection = new ProjectCollection();
            var globalProperty = new Dictionary<string, string> {
                { "OutputType", "Exe" },
                { "Configuration", configuration.ToString() },
            };

            //----- ビルドロガーの用意
            var gameLoaderLogger = new GameLoaderLogger();
            var buildParameters = new BuildParameters(projectCollection) {
                Loggers = new ILogger[] { gameLoaderLogger }
            };

            //----- ビルドスレッド立ち上げ
            bool isBuildEnd = false;    // ビルドが終了したか
            var buildTask = Task.Run(() => {
                //----- Nugetの初期化
                var restoreRequest = new BuildRequestData(sln, globalProperty, null, new[] { "Restore" }, null);
                BuildManager.DefaultBuildManager.Build(buildParameters, restoreRequest);

                //----- ビルドを行う
                var buildRequest = new BuildRequestData(sln, globalProperty, null, new[] { "Build" }, null);
                var buildResult = BuildManager.DefaultBuildManager.Build(buildParameters, buildRequest);

                isBuildEnd = true;
            });

            //----- メッセージスレッド立ち上げ
            var messageTask = Task.Run(() => {
                while (isBuildEnd == false) {
                    //----- 変数宣言
                    EditorLog log = null;

                    //----- ロガーからログを取得
                    lock (gameLoaderLogger.LockObject) {
                        //----- ログが追加されていないなら無視する
                        if (gameLoaderLogger.Logs.Count == 0) {
                            Thread.Sleep(1);
                            continue;
                        }

                        //----- ログを取得
                        log = gameLoaderLogger.Logs[0];
                        gameLoaderLogger.Logs.Remove(log);
                    }

                    //----- ログを追加
                    LogSystem.Get.AddLog(log);
                }
            });
        }


        /// <summary>プロジェクト作成</summary>
        public void ProjectCreate() {
            //----- 変数宣言
            string path = Directory.GetCurrentDirectory() + EditorDefine.GameSourceMainName;

            //----- エントリーポイントがあるか
            if (Path.Exists(path) == false) {
                //----- ない。作成
                File.WriteAllText(path, EditorDefine.GameSourceMainSource);
            }

            //----- csprojが存在するか
            path = Directory.GetCurrentDirectory() + EditorDefine.GameSourceProjectName;
            if (Path.Exists(path) == false) {
                //----- ない。作成
                File.WriteAllText(path, EditorDefine.GameSourceProjectSource);
            }
            
            //----- slnが存在するか
            path = Directory.GetCurrentDirectory() + EditorDefine.GameSourceSolutionName;
            if (Path.Exists(path) == false) {
                //----- ない。作成
                File.WriteAllText(path, EditorDefine.GameSourceSolutionSource);
            }
        }


        static private GameReloader ms_instance;
    }
}
