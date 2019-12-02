# TrabalhoRedes
Repositorio para o trabalho de Redes, 2019.2
/*Equipe:
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 * 
 * 
 * 
 */

COMPILAR MAKEFILE:
make -f makefileServer.make
make -f makefileClient.make

EXECUTAR
./bin/server
./bin/client -s 127.0.0.1 ./bin/files-to-send/text.txt