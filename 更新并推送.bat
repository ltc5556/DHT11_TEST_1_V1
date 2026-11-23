@echo off
chcp 65001 >nul
cd /d "%~dp0"
echo ===== git add =====
"C:\Program Files\Git\cmd\git.exe" add -A
echo ===== git status =====
"C:\Program Files\Git\cmd\git.exe" status
echo ===== git commit =====
"C:\Program Files\Git\cmd\git.exe" commit -m "feat: add original and modified RTCtester sketches"
echo ===== git push =====
"C:\Program Files\Git\cmd\git.exe" push
echo ===== done =====
"C:\Program Files\Git\cmd\git.exe" log -1 --oneline
pause
