CC=gcc
CFLAGS=-I.
DEPS = ./include/transporte.h ./include/socketHandler.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

aplicacaoCliente: ./src/aplicacaoCliente.o ./src/socketHandler.o ./src/transporte.o
	$(CC) -o ./bin/client ./src/aplicacaoCliente.o ./src/socketHandler.o ./src/transporte.o
	@ echo [CLEAN] Excluindo Objetos Criados...
	@ rm -f ./src/*.o
	@ echo [DONE] Exclusao realizada com sucesso!