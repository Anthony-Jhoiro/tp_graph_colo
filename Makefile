main: main.o graph.o parser.o graph_colo.o colo_genetique.o
	gcc -o main main.o graph.o parser.o graph_colo.o colo_genetique.o

graph.o: graph/graph.c
	gcc -c graph/graph.c

parser.o: parser/parser.c
	gcc -c parser/parser.c

graph_colo.o: graph_colo/graph_colo.c
	gcc -c graph_colo/graph_colo.c

colo_genetique.o: colo_genetique/colo_genetique.c 
	gcc -c colo_genetique/colo_genetique.c

clean:
	rm *.o
	rm main