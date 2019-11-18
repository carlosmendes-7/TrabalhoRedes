CC=gcc
CFLAGS=-I.
DEPS = ./include/camadaAplicacao.h ./include/camadaTransporte.h ./include/camadaRede.h ./include/camadaEnlace.h ./include/socketHandler.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

aplicacaoServidor: ./src/aplicacaoServidor.o ./src/camadaAplicacao.o ./src/camadaTransporte.o ./src/camadaRede.o ./src/camadaEnlace.o ./src/socketHandler.o
	$(CC) -o ./bin/server ./src/aplicacaoServidor.o ./src/camadaAplicacao.o ./src/camadaTransporte.o ./src/camadaRede.o ./src/camadaEnlace.o ./src/socketHandler.o
	@ echo [CLEAN] Excluindo Objetos Criados...
	@ rm -f ./src/*.o
	@ echo [DONE] Exclusao realizada com sucesso!