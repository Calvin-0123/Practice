#!/usr/bin/env bash
set -euo pipefail

git rev-parse --is-inside-work-tree >/dev/null 2>&1 || {
  echo "❌ 当前目录不是 Git 仓库。请先 cd 到你的项目根目录。"
  exit 1
}

IGNORE_LIST=("a.out" "practice" "calculator")

touch .gitignore
for item in "${I
GNORE_LIST[@]}"; do
  if ! grep -qxF "$item" .gitignore; then
    echo "$item" >> .gitignore
    echo "➕ 已写入 .gitignore: $item"
  fi
done

for item in "${IGNORE_LIST[@]}"; do
  if git ls-files --error-unmatch "$item" >/dev/null 2>&1; then
    git rm --cached "$item"
    echo "🧹 已从 Git 追踪移除: $item"
  fi
done

git add .gitignore
if git commit -m "chore: ignore build outputs" >/dev/null 2>&1; then
  echo "✅ 已提交 .gitignore 变更。"
else
  echo "ℹ️ 无需提交：.gitignore 无变化。"
fi

git push
echo "🚀 已推送到远端。全部完成！"
