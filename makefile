ALL:
	gcc -Wall -o mkf.exe *.c -L"F:\dev\dataStructures\linkedList" -llinkedlist -I"F:\dev\dataStructures\linkedList"

CLEAN:
	-@ DEL mkf.exe
	