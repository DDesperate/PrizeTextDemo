@echo off
if not "%~1"=="" cd /d "%~1"
::  设置火山引擎 API 相关环境变量
set ANTHROPIC_BASE_URL=https://api.xiaomimimo.com/anthropic
set ANTHROPIC_AUTH_TOKEN=sk-cowz6f778kstztq92x8t5jwn0uwy4c18ligoi76cjfswopl0
set ANTHROPIC_MODEL=mimo-v2.5-pro
set ANTHROPIC_DEFAULT_HAIKU_MODEL=mimo-v2.5-pro
set API_TIMEOUT_MS=3000000
set CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC=1

:: 启动 claude
claude