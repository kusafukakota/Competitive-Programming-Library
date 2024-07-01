function global:box($condition){
  if($condition -eq 1){
    Write-Host "[" -NoNewline
    Write-Host "+" -ForegroundColor Green -NoNewline
    Write-Host "] " -NoNewline
  }
  if($condition -eq 0){
    Write-Host "[" -NoNewline
    Write-Host "x" -ForegroundColor Red -NoNewline
    Write-Host "] " -NoNewline
  }
  if($condition -eq -1){
    Write-Host "[" -NoNewline
    Write-Host "i" -ForegroundColor DarkCyan -NoNewline
    Write-Host "] " -NoNewline
  }
  if($condition -eq 2){
    Write-Host "[" -NoNewline
    Write-Host "#" -ForegroundColor DarkYellow -NoNewline
    Write-Host "] " -NoNewline
  }
  if($condition -eq 3){
    Write-Host "[" -NoNewline
    Write-Host "?" -ForegroundColor DarkYellow -NoNewline
    Write-Host "] " -NoNewline
  }
}

$global:dirflag=0
$global:curfile="0"

function global:s($type,[string]$number){
  $type=$type.toupper()
  if(Test-Path ".\$type\$number"){
    $global:dirflag=1
    $global:contest=$type+$number
    $global:contestdir=".\$type\$number\$type$number-"
    $Host.ui.RawUI.WindowTitle="$type$number"
    box(1)
    Write-Host "Set Directory Successfully!" -ForegroundColor Green
    box(-1)
    Write-Host "Contest : $type$number" -ForegroundColor DarkCyan
  }
  else{
    $global:dirflag=0
    $Host.ui.RawUI.WindowTitle="Windows PowerShell"
    box(0)
    Write-Host "Directory Not Found" -ForegroundColor Red
  }
}

function global:run($type="def",[string]$number="def",$problem="def",$GLIBCXX="def"){
  if($type -eq "def"){
    if($curfile -eq "0"){
      box(0)
      Write-Host "File is not Specified" -ForegroundColor Red
      $global:tflag=0
      return
    }
    g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG $curfile
  }
  elseif($problem -eq "def"){
    if($global:dirflag -eq 0){
      box(0)
      Write-Host "Directory is not Specified" -ForegroundColor Red
      $global:tflag=0
      return
    }
    if(Test-Path $global:contestdir$type.cpp){
      if($number -eq "def"){g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG $global:contestdir$type.cpp}
      else{g++ -std=c++20 -I . -Wall -O2 $global:contestdir$type.cpp}
      $global:curfile="$global:contestdir$type.cpp"
    }
    else{
      box(0)
      Write-Host "File Not Found" -ForegroundColor Red
      $global:tflag=0
      return
    }
  }
  else{
    if(Test-Path .\$type\$number\$type$number-$problem.cpp){
      if($GLIBCXX -eq "def"){g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG .\$type\$number\$type$number-$problem.cpp}
      else{g++ -std=c++20 -I . -Wall -O2 .\$type\$number\$type$number-$problem.cpp}
      $global:curfile=".\$type\$number\$type$number-$problem.cpp"
    }
    else{
      box(0)
      Write-Host "File Not Found" -ForegroundColor Red
      return
    }
  }
  if($LastExitCode -eq 0){
    box(1)
    Write-Host "Compiled Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Compilation Failed" -ForegroundColor Red
    $global:tflag=0
  }
}

function global:c($arg1="def",[string]$arg2="def",$arg3="def",$arg4="def"){
  if($arg1 -eq "def"){
    if($curfile -eq "0"){
      box(0)
      Write-Host "File is not Specified" -ForegroundColor Red
      return
    }
    g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG $curfile
  }
  elseif($arg3 -eq "def"){
    if($global:dirflag -eq 0){
      box(0)
      Write-Host "Directory is not Specified" -ForegroundColor Red
      $global:tflag=0
      return
    }
    if(Test-Path $global:contestdir$arg1.cpp){
      if($arg2 -eq "def"){g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG $global:contestdir$arg1.cpp}
      else{g++ -std=c++20 -I . -Wall -O2 $global:contestdir$arg1.cpp}
      $global:curfile="$global:contestdir$arg1.cpp"
    }
    else{
      box(0)
      Write-Host "File Not Found" -ForegroundColor Red
      $global:tflag=0
      return
    }
  }
  else{
    if(Test-Path .\$arg1\$arg2\$arg1$arg2-$arg3.cpp){
      if($arg4 -eq "def"){g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG .\$arg1\$arg2\$arg1$arg2-$arg3.cpp}
      else{g++ -std=c++20 -I . -Wall -O2 .\$arg1\$arg2\$arg1$arg2-$arg3.cpp}
      $global:curfile=".\$arg1\$arg2\$arg1$arg2-$arg3.cpp"
    }
    else{
      box(0)
      Write-Host "File Not Found" -ForegroundColor Red
      return
    }
  }
  if($LastExitCode -eq 0){
    box(1)
    Write-Host "Compiled Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Compilation Failed" -ForegroundColor Red
    $global:tflag=0
  }
}

function global:in($display="def"){
  Write-Host "[>] Standard Input :" -ForegroundColor DarkGray
  if($display -eq "def"){Get-Content .\in.txt | Write-Host}
  else{Write-Host "-- hidden --" -ForegroundColor DarkYellow}
  Write-Host
  Write-Host "[<] Standard Output :" -ForegroundColor DarkGray
  Get-Content .\in.txt | .\a
  if($LastExitCode -eq 0){
    Write-Host
    box(1)
    Write-Host "Executed Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Runtime Error" -ForegroundColor Red
  }
}

function global:q{
  Write-Host "[>] Standard Input :" -ForegroundColor DarkGray
  Get-Clipboard | Write-Host
  Write-Host
  Write-Host "[<] Standard Output :" -ForegroundColor DarkGray
  Get-Clipboard | .\a
  if($LastExitCode -eq 0){
    Write-Host
    box(1)
    Write-Host "Executed Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Runtime Error" -ForegroundColor Red
  }
}

function global:a{
  .\a
  if($LastExitCode -eq 0){
    Write-Host
    box(1)
    Write-Host "Executed Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Runtime Error" -ForegroundColor Red
  }
}

function global:out{
  Get-Content .\in.txt | .\a > .\out.txt
  if($LastExitCode -eq 0){
    Write-Host
    box(1)
    Write-Host "Executed Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Runtime Error" -ForegroundColor Red
  }
}

function global:m($GLIBCXX="def"){
  if($GLIBCXX -eq "def"){g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG memo.cpp}
  else{g++ -std=c++20 -I . -Wall -O2 memo.cpp}
  $global:curfile="memo.cpp"
  if($LastExitCode -eq 0){
    box(1)
    Write-Host "Compiled Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Compilation Failed" -ForegroundColor Red
  }
}

function global:naive{
  g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG -o naive_ naive.cpp
  if($LastExitCode -eq 0){
    box(1)
    Write-Host "Compiled Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Compilation Failed" -ForegroundColor Red
  }
}

function global:random{
  g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG -o random_ random.cpp
  if($LastExitCode -eq 0){
    box(1)
    Write-Host "Compiled Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Compilation Failed" -ForegroundColor Red
  }
}

function global:v{
  if($curfile -eq "0"){
    box(0)
    Write-Host "File is not Specified" -ForegroundColor Red
    return
  }
  Get-Content $global:curfile | Set-Clipboard
  box(-1)
  Write-Host "Copied to Clipboard" -ForegroundColor DarkCyan
}

$PSDefaultParameterValues['*:Encoding'] = 'utf8'
function global:debug([int]$TrialCount=100){
  $c=0;
  while(1){
    ++$c
    .\random_ > .\WA_input.txt
    $ans = (Get-Content .\WA_input.txt | .\naive_)
    $myans = (Get-Content .\WA_input.txt | .\a)
    Write-Host -NoNewline "`r"
    box(-1)
    Write-Host -NoNewline "Running on Testcase $c ..." -ForegroundColor DarkCyan
    if($LastExitCode -ne 0){
      Write-Host
      box(0)
      Write-Host "Runtime Error (Failed in Case"$c")" -ForegroundColor Red
      Write-Host "Correct Answer :" $ans -ForegroundColor Green
      break
    }
    $ans = $ans -join "`n"
    $myans = $myans -join "`n"
    $ans=[regex]::Replace($ans,"\s"," ")
    $myans=[regex]::Replace($myans,"\s"," ")
    $ans=[regex]::Replace($ans,"  * "," ")
    $myans=[regex]::Replace($myans,"  * "," ")
    $ans=$ans.TrimEnd()
    $myans=$myans.TrimEnd()
    if($myans -ne $ans){
      Write-Host
      box(0)
      Write-Host "Wrong Answer (Failed in Case"$c")" -ForegroundColor Red
      Write-Host "Correct Answer :" $ans -ForegroundColor Green
      Write-Host "   Your Answer :" $myans -ForegroundColor Red
      break
    }
    if($c -eq $TrialCount){
      Write-Host
      box(1)
      Write-Host "Passed"$TrialCount" Testcases!" -ForegroundColor Green
      break
    }
  }
}


$PSDefaultParameterValues['*:Encoding'] = 'utf8'
function global:rt([int]$TrialCount = 1, [string]$Writeans = "def"){
  $c=0;
  while(1){
    ++$c
    .\random_ > .\WA_input.txt
    if($Writeans -eq "def"){Get-Content .\WA_input.txt | .\a}
    else {$ans=(Get-Content .\WA_input.txt | .\a)}
    Write-Host -NoNewline "`r"
    box(-1)
    Write-Host -NoNewline "Running on Testcase $c ..." -ForegroundColor DarkCyan
    if($LastExitCode -ne 0){
      box(0)
      Write-Host "Runtime Error (Failed in Case"$c")" -ForegroundColor Red
      break
    }
    if($c -eq $TrialCount){
      Write-Host
      box(1)
      Write-Host "Executed Successfully!" -ForegroundColor Green
      break
    }
  }
}

$PSDefaultParameterValues['*:Encoding'] = 'utf8'
function global:judge([int]$TrialCount = 100){
  $c=0;
  while(1){
    ++$c
    .\random_ > .\WA_input.txt
    $input=(Get-Content .\WA_input.txt)
    $ans=(Get-Content .\WA_input.txt | .\a)
    Write-Host -NoNewline "`r"
    box(-1)
    Write-Host -NoNewline "Running on Judge $c ..." -ForegroundColor DarkCyan
    if($LastExitCode -ne 0){
      Write-Host
      box(0)
      Write-Host "Runtime Error (Failed in Case"$c")" -ForegroundColor Red
      break
    }
    $Judge=("$input $ans" | .\naive_)
    if($Judge -ne "Yes"){
      Write-Host
      box(0)
      Write-Host "Wrong Answer (Failed in Case"$c")" -ForegroundColor Red
      Write-Host "Your Answer :" $ans -ForegroundColor Red
      break
    }
    if($c -eq $TrialCount){
      Write-Host
      box(1)
      Write-Host "Passed $TrialCount Judges!" -ForegroundColor Green
      break
    }
  }
}

function global:op{
  if($global:dirflag -eq 0){
    box(0)
    Write-Host "Directory is not Specified" -ForegroundColor Red
    return
  }
  if (-not (Get-Process -Name "Pulsar" -ErrorAction SilentlyContinue)){
    box(0)
    Write-Host "Pulsar is not running" -ForegroundColor Red
    return
  }
  Invoke-Item "$contestdir*"
  box(1)
  Write-Host "Opened All Files Successfully!" -ForegroundColor Green
}

function global:time($display="def"){
  Write-Host "[>] Standard Input :" -ForegroundColor DarkGray
  if($display -eq "def"){Get-Content .\in.txt | Write-Host}
  else{Write-Host "-- hidden --" -ForegroundColor DarkYellow}
  Write-Host
  Write-Host "[<] Standard Output :" -ForegroundColor DarkGray
  Get-Content .\in.txt | .\a
  $msec =(Measure-Command {Get-Content .\in.txt | .\a}).totalmilliseconds
  Write-Host
  Write-Host "---------------------------------"
  box(-1)
  Write-Host "Execution Time : $msec ms" -ForegroundColor DarkCyan
  Write-Host "---------------------------------"
  if($LastExitCode -eq 0){
    Write-Host
    box(1)
    Write-Host "Executed Successfully!" -ForegroundColor Green
  }else{
    box(0)
    Write-Host "Runtime Error" -ForegroundColor Red
  }
}
