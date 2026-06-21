@echo off
if not "%~1"=="" cd /d "%~1"
::  设置火山引擎 API 相关环境变量
set ANTHROPIC_BASE_URL=https://ark.cn-beijing.volces.com/api/coding
set ANTHROPIC_AUTH_TOKEN=ark-c66bc252-b9b4-42d0-9aba-d04976abf2ca-9c0f4
set ANTHROPIC_MODEL=glm-5.1
set ANTHROPIC_DEFAULT_HAIKU_MODEL=woxiabiande
set API_TIMEOUT_MS=3000000
set CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC=1

:: 启动 claude
claude