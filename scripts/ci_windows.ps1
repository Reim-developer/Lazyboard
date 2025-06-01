function Get-VS2019 {
    choco install visualstudio2019buildtools `
    --package-parameters "--add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.Windows10SDK.19041 --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 --add Microsoft.VisualStudio.Component.VC.CMake.Project" `
    -y --confirm --force `
}

function Get-Vcpkg {
    param(
        [string]$vcpkgDir = "$PSScriptRoot\vcpkg"
    )

    if (-Not (Test-Path -Path $vcpkgDir)) {
        git clone https://github.com/microsoft/vcpkg.git  $vcpkgDir
    }

    Set-Location $vcpkgDir

    .\bootstrap-vcpkg.bat
    .\vcpkg integrate install
}

function Get-Dependency {
    param(
        [string]$vcpkgDir = "$PSScriptRoot\vcpkg"
    )

    Set-Location $vcpkgDir
    .\vcpkg install libsodium:x64-windows
}
function build {
    $vs_path = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
        $toolchain_path = "$PSScriptRoot\vcpkg\scripts\buildsystems\vcpkg.cmake"
    $build_dir = "build"

    $cmd = @"
call `"$vs_path`" x64
mkdir build
cd "$build_dir"
cmake -G "Visual Studio 16 2019" -T v142 -DCMAKE_TOOLCHAIN_FILE="$toolchain_path" ..
cmake --build . --config Release
"@
    
    cmd /k "$cmd"
}

function deploy_qt {
    cmd /c call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
    Set-Location build

    $qt_win = "D:\a\zClipboard\Qt\6.5.3\msvc2019_64\bin\windeployqt.exe"
    $binary = "Release\zclipboard.exe"
    $target_dir = "deploy"

    if (-not (Test-Path -Path $target_dir)) {
        New-Item -ItemType Directory -Path $target_dir
    }

    Copy-Item -Path $binary -Destination "$target_dir\zclipboard.exe"

    Set-Location $target_dir

    & $qt_win `
    --release `
    --no-translations `
    --dir deploy zclipboard.exe

    Set-Location ..
}

function main {
    switch ($args[0]) {
        "install-vs" {
            Get-Vcpkg
            Get-Dependency
            Get-VS2019
            break
        }
        "build" {
            build
            break
        }
        "deploy_qt" {
            deploy_qt
            break
        }
    }
}

main @args