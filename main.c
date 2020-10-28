#include <stdio.h>
#include <stdlib.h>
int main(void){
     int ver=0;// количество вершин
     int uzl=0;// количество узлов
     int is_directed=0;// ориентированность графа
     int is_weight=0;// взвешенность графа
     int c;
	 FILE *MatrFile=fopen("matr.txt", "r");
	 if(MatrFile==NULL){
        printf("takogo faila net");
     }else{
        printf("ctenie faila\n");
        while(!feof(MatrFile)){              
            if((fgetc(MatrFile))==';'){
                ver++;
            }
        } 
        fclose(MatrFile);
        FILE *MatrFile=fopen("matr.txt", "r");
        while((c=fgetc(MatrFile))!=';'){
            if(c==',')
                uzl++;
        }
        uzl++;
        fclose(MatrFile);
        int Arr [ver][uzl]; // матрица инцидентности
        MatrFile=fopen("matr.txt", "r");
        for(int i=0;i<ver;i++){
            int j=0;
            while((c=fgetc(MatrFile))!=';')
                fscanf(MatrFile,"%d",&Arr[i][j++]);
        }
        fclose(MatrFile);
// проверяем является ли граф ориентрованным или взвешенным       
        for (int i = 0; i < ver; i++){
		    for (int j = 0; j < uzl; j++){
			    printf("%d ",Arr[i][j]);
                if (Arr[i][j]>1)
                    is_weight=1;
                if(Arr[i][j]<0)
                    is_directed=1;
            }
            printf("\n");
	    }  
        char weight[uzl];// массив взвешенных узлов
        if(is_weight){
            for (int j = 0; j < uzl; j++){
                for (int i = 0; i < uzl; i++){
                    if (Arr[i][j]>0)
                        weight[j]=Arr[i][j];
                }
             printf("%d - %d\n",j ,weight[j]);
            }
        }
    
        char VertNames[ver]; // массив вершин
        for (int i = 0; i < ver; i++)
            VertNames[i]='a'+i;
        char Connect[uzl][2];// массив соединенных вершин
        for (int j = 0; j < uzl; j++){
            int k=0;
            for (int i = 0; i < ver; i++){
                if(Arr[i][j]<0)
                    Connect[j][1]=VertNames[i];
                if (Arr[i][j]>0)
                    Connect[j][k++]=VertNames[i];   
             }
        }
        printf("\n");
        for (int i = 0; i < uzl; i++){
	        for (int j = 0; j < 2; j++){
                if(!Connect[i][j]){
                    Connect[i][j]=Connect[i][j-1];
                }
		        printf("%c ",Connect[i][j]);
            }
            printf("\n");
	    }  
   // создание графа на языке dot и компиляция файла
        FILE *GraphFile=fopen("graph.dot", "w");
        if(GraphFile==NULL){
            printf("ne poluchaetsya sozdat fail");
        }else{
            printf("chtenie\n");
            if(is_directed)
                fprintf(GraphFile,"di");
            fprintf(GraphFile,"graph Test {\n");
            for (int i = 0; i < uzl; i++){
                if(!is_directed)
                    fprintf(GraphFile,"%c -- %c ",Connect[i][0],Connect[i][1]);
                else{
                    fprintf(GraphFile,"%c -> %c ",Connect[i][0],Connect[i][1]);
                    }
                if (is_weight)
                    fprintf(GraphFile,"[label= %d] \n",weight[i]);
                }
            fprintf(GraphFile,"}\n");
            fclose(GraphFile);
            system("dot -Tpng graph.dot -o graph.png");
            system("xdg-open graph.png");
        }
        //проверка связности графа по теореме
        if(uzl>(((ver-1)*(ver-2))/2)){
            printf("svyazniy graph\n");
        }else{
            printf("nesvyazniy graph\n");
        }
    }
 return 0;
}
