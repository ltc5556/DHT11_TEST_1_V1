#!/bin/bash
set -e
cd "$(dirname "$0")"
git init
git add .
git commit -m "feat: initial commit for Arduino project" || true
git branch -M main
git remote remove origin 2>/dev/null || true
git remote add origin git@github.com:ltc5556/DHT11_TEST_1_V1.git
git push -u origin main
echo "DONE. Refresh GitHub page."
read -p "Press Enter to close..."
