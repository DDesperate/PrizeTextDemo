@echo off
:: 增加这一行，让它跳转到右键传过来的文件夹路径 
if not "%~1"=="" cd /d "%~1"

set ANTHROPIC_BASE_URL=https://token-plan.cn-beijing.maas.aliyuncs.com/apps/anthropic
set ANTHROPIC_AUTH_TOKEN=sk-sp-H.HMYHER.AVdH.MEUCIQDbiAQLEi4TGsy3eEZHUdRYEu_LzYC7kurWnzl427FhxwIgQkey-isRi3YV9Oy3tVIa88SHaJS2JMlpvh61KoSARHg
set ANTHROPIC_MODEL=qwen3.7-plus
set ANTHROPIC_DEFAULT_HAIKU_MODEL=qwen3.7-plus
set API_TIMEOUT_MS=3000000 
set CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC=1 
claude