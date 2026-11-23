@echo off
cd /d "%~dp0"
"C:\Program Files\Git\bin\bash.exe" -lc "git add . && git commit -m \"feat: DHT11 working sketch verified on UNO\" && git push && echo DONE"
pause
