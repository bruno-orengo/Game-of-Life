#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define ALIVE 1
#define DEAD 0
//#define ROW 20
//#define COL 20
#define ISALIVE "O"
#define ISDEAD "."
#define SEPARATION "\n___________________________________________________________\n"

int ROW, COL;
float runtime;
int geracao = 0, numAlive = 0, numDead, stability = 0,oldStability = 0, olderStability = 0, evenOlderStability = 0, stabilityCount = 0, chosenStability;
int i,j;

struct cell{
	int state;
	int livingNeighbors;
};


void initColony(struct cell colony[ROW][COL], struct cell auxColony[ROW][COL]){
	srand(time(NULL));
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			colony[i][j].state = rand() % 2;
			auxColony[i][j].state = colony[i][j].state;
			if(colony[i][j].state == ALIVE) numAlive++;
			else numDead++;
		}
	}
}

void checkState(struct cell colony[ROW][COL]){
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			
			if(colony[i][j].state == DEAD && colony[i][j].livingNeighbors == 3){
				colony[i][j].state = ALIVE;
				numAlive++;
				numDead--;
			}else if(colony[i][j].state == ALIVE && (colony[i][j].livingNeighbors == 2 || colony[i][j].livingNeighbors == 3)){
					colony[i][j].state = ALIVE;
			}else{
				if(colony[i][j].state == ALIVE){
					numAlive--;
					numDead++;
				}
				colony[i][j].state = DEAD;
				
			}
			
		}
	}
}


void checkNeighbours(struct cell colony[ROW][COL], struct cell auxColony[ROW][COL]){
	
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			
			auxColony[i][j].livingNeighbors = 0;
		}
	}
	
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			
			if(i == 0 && j == 0){
				auxColony[i][j].livingNeighbors += colony[i+1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j+1].state;
			}else if((i == ROW -1) && (j == 0)){
				auxColony[i][j].livingNeighbors += colony[i-1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j+1].state;
			}else if(j == 0){
				auxColony[i][j].livingNeighbors += colony[i-1][j].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j+1].state;
			}else if(i == 0 && (j == COL - 1)){
				auxColony[i][j].livingNeighbors += colony[i+1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j-1].state;
			}else if((i == ROW - 1) && (j == COL - 1)){
				auxColony[i][j].livingNeighbors += colony[i-1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j-1].state;
			}else if(j == COL - 1){
				auxColony[i][j].livingNeighbors += colony[i-1][j].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j-1].state;
			}else if(i == 0){
				auxColony[i][j].livingNeighbors += colony[i][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j+1].state;
			}else if(i == ROW - 1){
				auxColony[i][j].livingNeighbors += colony[i][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j-1].state;
			}else{
				auxColony[i][j].livingNeighbors += colony[i+1][j].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j].state;
				auxColony[i][j].livingNeighbors += colony[i][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i+1][j-1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j+1].state;
				auxColony[i][j].livingNeighbors += colony[i-1][j-1].state;
			}
		}
	}
	
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			
			colony[i][j].livingNeighbors = auxColony[i][j].livingNeighbors;
			//printf("Posicao %d %d vizinhos vivos %d",i,j,colony[i][j].livingNeighbors);
			//getch();
			
		}
	}
	
}

void displayColony(struct cell colony[ROW][COL]){
	printf("Generation: %d Alive: %d Dead: %d\n", geracao, numAlive, numDead);
	for(i = 0; i < ROW; i++){
		printf("\n");
		for(j = 0; j < COL; j++){
			
			if(colony[i][j].state == ALIVE)printf(ISALIVE);
			else printf(ISDEAD);
			
		}
	}
	
	printf(SEPARATION);
}

//void debug(){
//	for(i = 0; i < ROW; i++){
//		for(j = 0; j < COL; j++){
//			
//			printf("Cell[%d][%d] state: %d",i,j, colony[i][j].state);
//			
//		}
//	}
//	
//	getch();
//}


	
	
int main(void) {
	
	
	
printf(" _______  _______  _______  _______    _______  _______    _       _________ _______  _______\n");
printf("(  ____ \\(  ___  )(       )(  ____ \\  (  ___  )(  ____ \\  ( \\      \\__   __/(  ____ \\(  ____ \\ \n");
printf("| (    \\/| (   ) || () () || (    \\/  | (   ) || (    \\/  | (         ) (   | (    \\/| (    \\/ \n");
printf("| |      | (___) || || || || (__      | |   | || (__      | |         | |   | (__    | (__ \n");
printf("| | ____ |  ___  || |(_)| ||  __)     | |   | ||  __)     | |         | |   |  __)   |  __)\n");
printf("| | \\_  )| (   ) || |   | || (        | |   | || (        | |         | |   | (      | ( \n");
printf("| (___) || )   ( || )   ( || (____/\\  | (___) || )        | (____/\\___) (___| )      | (____/\\ \n");
printf("(_______)|/     \\||/     \\|(_______/  (_______)|/         (_______/\\_______/|/       (_______/ \n");

printf("\n                                         PRESS ENTER");
getch();
system("cls");
	
	char op;
	int maxGenerations;
	printf("Rows size: ");
	scanf("%d", &ROW);
	printf("Columns size: ");
	scanf("%d", &COL);
	printf("Rate of new generations(s): ");
	scanf("%f", &runtime);
	printf("Number of generations to be stable: ");
	scanf("%d", &chosenStability);
	printf("Limit generations?(y/n): ");
	scanf(" %c", &op);
	
	if(op == 'y'){
		printf("Max number of generations: ");
		scanf("%d", &maxGenerations);
	}
	
	printf("\nRows: %d Columns: %d Generation rate: %.2fs Stability in: %d generations Limit Generations: %c", ROW, COL, runtime, chosenStability, op);
	if(op == 'y')printf(" Generation Limit: %d\n", maxGenerations);
	else printf("\n");
	printf("PRESS ENTER TO START\n\n");
	getch();
	
	struct cell colony[ROW][COL];
	struct cell auxColony[ROW][COL];
		
	initColony(colony, auxColony);
	
	
	//debug();
	displayColony(colony);
	printf("\nPress enter to continue");
	getch();
	system("cls");
	while(1){
		
		geracao++;
		checkNeighbours(colony, auxColony);
		checkState(colony);
		displayColony(colony);
		sleep(runtime);
		//getch();
		evenOlderStability = olderStability;
		olderStability = oldStability;
		oldStability = stability;
		stability = numAlive;
		
		if(stability == oldStability || stability == olderStability || stability == evenOlderStability)stabilityCount++;
		else stabilityCount = 0;
		
		if(numAlive == 0 || stabilityCount == chosenStability || (op == 'y' && geracao == maxGenerations))break;
		system("cls");
	}
	
	
	if(numAlive == 0)printf("All cells are dead. Final generation: %d\n", geracao);
	else if(geracao == maxGenerations)printf("The system reached the generation limit. Final generation: %d\n", geracao);
	else printf("The system got stable. Final generation: %d\n", geracao);
	
	printf("Press ENTER to close application");
	getch();
	
	return 0;
}
