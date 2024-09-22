@echo off
setlocal enabledelayedexpansion

rem Лимит размера в байтах (50 МБ)
set limit=52428800

rem Поиск всех файлов .uasset больше 50 МБ
for /r %%f in (*.uasset) do (
    for %%A in ("%%f") do set size=%%~zA
    if !size! gtr %limit% (
        rem Проверяем, отслеживается ли файл в LFS
        git lfs ls-files | find "%%f" >nul
        if errorlevel 1 (
            echo Добавляем в LFS: %%f
            git lfs track "%%f"
        )
    )
)