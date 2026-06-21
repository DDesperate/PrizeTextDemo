@echo off
:: 增加这一行，让它跳转到右键传过来的文件夹路径 
if not "%~1"=="" cd /d "%~1"

set ANTHROPIC_BASE_URL=https://api.lkeap.cloud.tencent.com/plan/anthropic 
set ANTHROPIC_AUTH_TOKEN=sk-tp-Zjoimt262tp0XjTSJl5wZrBm9ZO9GV06KtPlwvzKaQGddDUA
set ANTHROPIC_MODEL=glm-5.1 
set ANTHROPIC_DEFAULT_HAIKU_MODEL=glm-5.1 
set API_TIMEOUT_MS=3000000 
set CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC=1 
claude