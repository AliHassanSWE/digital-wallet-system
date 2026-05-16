@echo off
echo Compiling Multi-User Digital Wallet System...
g++ main.cpp User.cpp Wallet.cpp FileManager.cpp Transaction.cpp -o WalletSystem.exe
if %ERRORLEVEL% EQU 0 (
    echo Compilation Successful! Running program...
    echo ==================================================
    WalletSystem.exe
) else (
    echo Compilation Failed! Please check your code.
)
pause