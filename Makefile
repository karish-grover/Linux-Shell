all: 
	gcc rm.c -o rm
	gcc mkdir.c -o mkdir
	gcc ls.c -o ls
	gcc date.c -o date
	gcc cat.c -o cat
	gcc myShell.c -o myShell
	./myShell

rm:
	gcc rm.c -o rm

mkdir:
	gcc mkdir.c -o mkdir

ls:
	gcc ls.c -o ls

cat:
	gcc cat.c -o cat

date:
	gcc date.c -o date