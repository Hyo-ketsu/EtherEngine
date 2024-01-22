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
        }

        /// <summary>ゲームオブジェクト作成時の名前</summary>
        public static readonly EditorText NewCreateGameObjectName;
        /// <summary>ファイル作成時の名前</summary>
        public static readonly EditorText NewCreateFile;

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
        public static readonly string GameSourceProjectName = "GameSource.csproj";
        /// <summary>プロジェクトソース</summary>
        public static readonly string GameSourceProjectSource = @"
<Project Sdk=""Microsoft.NET.Sdk"">

  <PropertyGroup>
    <TargetFramework>net7.0-windows</TargetFramework>
    <ImplicitUsings>enable</ImplicitUsings>
    <Nullable>enable</Nullable>
    <AllowUnsafeBlocks>True</AllowUnsafeBlocks>
    <OutputType>WinExe</OutputType>
    <StartupObject>GameSource.GameMain</StartupObject>
  </PropertyGroup>

  <PropertyGroup Condition=""'$(Configuration)|$(Platform)'=='Debug|AnyCPU'"">
    <DefineConstants>$(DefineConstants);_DEBUG</DefineConstants>
  </PropertyGroup>

  <PropertyGroup Condition=""'$(Configuration)|$(Platform)'=='Release|AnyCPU'"">
    <DefineConstants>$(DefineConstants);_RELEASE</DefineConstants>
  </PropertyGroup>

</Project>
";
        /// <summary>ソリューション名(拡張子含む)</summary>
        public static readonly string GameSourceSolutionName = "GameSource.sln";
        /// <summary>ソリューションソース</summary>
        public static readonly string GameSourceSolutionSource = @"

Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.8.34511.84
MinimumVisualStudioVersion = 10.0.40219.1
Project(""{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}"") = ""GameSource"", ""GameSource.csproj"", ""{4DF722E2-5AC6-4769-BE7F-D9A2E2E9365B}""
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Any CPU = Debug|Any CPU
		Release|Any CPU = Release|Any CPU
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{4DF722E2-5AC6-4769-BE7F-D9A2E2E9365B}.Debug|Any CPU.ActiveCfg = Debug|Any CPU
		{4DF722E2-5AC6-4769-BE7F-D9A2E2E9365B}.Debug|Any CPU.Build.0 = Debug|Any CPU
		{4DF722E2-5AC6-4769-BE7F-D9A2E2E9365B}.Release|Any CPU.ActiveCfg = Release|Any CPU
		{4DF722E2-5AC6-4769-BE7F-D9A2E2E9365B}.Release|Any CPU.Build.0 = Release|Any CPU
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
	GlobalSection(ExtensibilityGlobals) = postSolution
		SolutionGuid = {E91887B5-B99F-4C2F-AC25-846F6E0FF352}
	EndGlobalSection
EndGlobal
";
    }
}
