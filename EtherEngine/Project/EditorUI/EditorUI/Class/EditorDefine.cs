using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    public static class EditorDefine {
        static EditorDefine() {
            NewCreateGameObjectName = new(en: "New GameObject", jp: "新しいゲームオブジェクト");
            NewCreateFile = new(en: "New File", jp: "New File");
            BuildSuccess = new(en: "*** Build Success! ***", jp: "*** ビルド成功! ***");
            BuildFailed = new(en: "*** Build Failed…… ***", jp: "*** ビルド失敗…… ***");
        }

        /// <summary>ゲームオブジェクト作成時の名前</summary>
        public static readonly EditorText NewCreateGameObjectName;
        /// <summary>ファイル作成時の名前</summary>
        public static readonly EditorText NewCreateFile;

        /// <summary>ビルド成功時の出力ログ</summary>
        public static readonly EditorText BuildSuccess;
        /// <summary>ビルド失敗時の出力ログ</summary>
        public static readonly EditorText BuildFailed;

        /// <summary>ビルドメッセージのセパレート</summary>
        public static readonly string BuildMessageSeparate = "=========================================";

        /// <summary>プロジェクト名</summary>
        public static readonly string GameSourceName = "GameSource";
        /// <summary>プロジェクトエントリーポイント名(拡張子含む)</summary>
        public static readonly string GameSourceMainName = "GameMain.cs";
        /// <summary>プロジェクトエントリーポイントソース</summary>
        public static readonly string GameSourceMainSource = @"
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameSource {
    internal static class GameMain {
        public static void Main(string[] args) {
        }
    }
}
";
        /// <summary>プロジェクト名(拡張子含む)</summary>
        public static readonly string GameSourceProjectName = GameSourceName + ".csproj";
        /// <summary>プロジェクトソース</summary>
        public static readonly string GameSourceProjectSource = @"
<Project Sdk=""Microsoft.NET.Sdk"">
  <PropertyGroup>
    <TargetFramework>net7.0</TargetFramework>
    <ImplicitUsings>enable</ImplicitUsings>
    <Nullable>enable</Nullable>
    <BaseOutputPath>Object\</BaseOutputPath>
    <AppendTargetFrameworkToOutputPath>false</AppendTargetFrameworkToOutputPath>
    <AppendRuntimeIdentifierToOutputPath>false</AppendRuntimeIdentifierToOutputPath>
    <BaseIntermediateOutputPath>Object\GameSource\</BaseIntermediateOutputPath>
  </PropertyGroup>
	
  <PropertyGroup Condition=""'$(Configuration)|$(Platform)'=='Debug|AnyCPU'"">
	<OutputPath>Object\</OutputPath>
	<IntermediateOutputPath>Object\GameSource\$(Configuration)\$(Platform)\</IntermediateOutputPath>
  </PropertyGroup>
  <PropertyGroup Condition=""'$(Configuration)|$(Platform)'=='Release|AnyCPU'"">
	<OutputPath>Object\</OutputPath>
	<IntermediateOutputPath>Object\GameSource\$(Configuration)\$(Platform)\</IntermediateOutputPath>
  </PropertyGroup>
</Project>
";
        /// <summary>ソリューション名(拡張子含む)</summary>
        public static readonly string GameSourceSolutionName = GameSourceName + ".sln";
        /// <summary>ソリューションソース</summary>
        public static readonly string GameSourceSolutionSource = @"
Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.8.34511.84
MinimumVisualStudioVersion = 10.0.40219.1
Project(""{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}"") = ""GameSource"", ""GameSource.csproj"", ""{8AE5AFFC-2635-41B1-B7A6-66223169DC77}""
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Any CPU = Debug|Any CPU
		Release|Any CPU = Release|Any CPU
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{8AE5AFFC-2635-41B1-B7A6-66223169DC77}.Debug|Any CPU.ActiveCfg = Debug|Any CPU
		{8AE5AFFC-2635-41B1-B7A6-66223169DC77}.Debug|Any CPU.Build.0 = Debug|Any CPU
		{8AE5AFFC-2635-41B1-B7A6-66223169DC77}.Release|Any CPU.ActiveCfg = Release|Any CPU
		{8AE5AFFC-2635-41B1-B7A6-66223169DC77}.Release|Any CPU.Build.0 = Release|Any CPU
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
	GlobalSection(ExtensibilityGlobals) = postSolution
		SolutionGuid = {22BC75AA-A0D7-4CAA-9FAF-7D5E80F39DAB}
	EndGlobalSection
EndGlobal
";
    }
}
