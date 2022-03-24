Set-Location -Path F:\Code\C\tictactoe
gcc main.c -o tictactoe.exe -C -Wall -ggdb3 -O0 -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
& "F:\Code\C\tictactoe\tictactoe.exe" -recurse -force  /run /exit
Start-Sleep -s 3