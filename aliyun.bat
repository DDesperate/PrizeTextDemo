@echo off
:: 增加这一行，让它跳转到右键传过来的文件夹路径 
if not "%~1"=="" cd /d "%~1"

set ANTHROPIC_BASE_URL=https://token-plan.cn-beijing.maas.aliyuncs.com/apps/anthropic
set ANTHROPIC_AUTH_TOKEN=sk-sp-H.DYDIPR.2cfa.MEQCID4V7I5qqS52NgVFcNPa8dzM2kYk3zZVTSiYB51DTm8oAiAF28E2qjXXB_pEoj_Xfg33wknAhx6c2onlqcmjYa_ujg
set ANTHROPIC_MODEL=qwen3.7-plus
set ANTHROPIC_DEFAULT_HAIKU_MODEL=qwen3.7-plus
set API_TIMEOUT_MS=3000000 
set CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC=1 
claude