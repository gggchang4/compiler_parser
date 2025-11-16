$ErrorActionPreference = "Stop"

# 编译
Write-Host "Compiling..." -ForegroundColor Cyan
g++ -std=c++11 -o parser_v3.exe lexer.cpp parser.cpp main.cpp
if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit 1
}

$testDir = "parser_testcases\functional"
$testFiles = Get-ChildItem -Path $testDir -Filter "*.c" | Sort-Object Name

$total = 0
$passed = 0
$failed = @()

foreach ($testFile in $testFiles) {
    $testName = [System.IO.Path]::GetFileNameWithoutExtension($testFile.Name)
    $expectedFile = Join-Path $testDir "$testName.out"
    
    if (-not (Test-Path $expectedFile)) {
        Write-Host "Skipping $testName (no .out file)" -ForegroundColor Yellow
        continue
    }
    
    $total++
    
    # 运行测试
    $input = Get-Content $testFile.FullName -Raw -Encoding UTF8
    $actual = $input | .\parser_v3.exe
    
    # 读取期望输出
    $expected = Get-Content $expectedFile -Raw
    
    # 标准化行结束符
    $actual = $actual -replace "`r`n", "`n" -replace "`r", "`n"
    $expected = $expected -replace "`r`n", "`n" -replace "`r", "`n"
    
    # 比较
    if ($actual -eq $expected) {
        Write-Host "PASS: $testName" -ForegroundColor Green
        $passed++
    } else {
        Write-Host "FAIL: $testName" -ForegroundColor Red
        $failed += $testName
        Write-Host "Expected:" -ForegroundColor Yellow
        Write-Host $expected
        Write-Host "Actual:" -ForegroundColor Yellow
        Write-Host $actual
        Write-Host ""
    }
}

Write-Host "`nSummary: $passed/$total passed" -ForegroundColor Cyan
if ($failed.Count -gt 0) {
    Write-Host "Failed tests: $($failed -join ', ')" -ForegroundColor Red
}

