Set-PSDebug -Trace 1

function CheckLastExitCode {
    param ([int[]]$SuccessCodes = @(0), [scriptblock]$CleanupScript=$null)

    if ($SuccessCodes -notcontains $LastExitCode) {
        if ($CleanupScript) {
            "Executing cleanup script: $CleanupScript"
            &$CleanupScript
        }
        $msg = @"
EXE RETURNED EXIT CODE $LastExitCode
CALLSTACK:$(Get-PSCallStack | Out-String)
"@
        throw $msg
    }
}

cd C:\projects\libossia\build\
cmake --build . > C:\projects\libossia\build-${env:APPVEYOR_BUILD_TYPE}.log
CheckLastExitCode

if ( $env:APPVEYOR_BUILD_TYPE -eq "max"){
  cd C:\projects\libossia\build-32bit
  cmake --build . > C:\projects\libossia\build-${env:APPVEYOR_BUILD_TYPE}-32bit.log
  CheckLastExitCode
}
