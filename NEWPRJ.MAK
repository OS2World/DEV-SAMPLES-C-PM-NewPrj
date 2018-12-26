newprj.obj : newprj.c
    cl -c -G2 -W3 newprj.c

newprj.exe : newprj.obj newprj.def
    link newprj, /align:16, NUL, os2, newprj


