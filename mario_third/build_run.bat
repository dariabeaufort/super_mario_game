@echo off
chcp 1251 > log
del log

set CPP_FILES="object.cpp brick.cpp enemy.cpp money.cpp mario.cpp game_state.cpp collision.cpp render.cpp movement.cpp level.cpp main.cpp"
set EXE=mario.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%

%EXE%

pause