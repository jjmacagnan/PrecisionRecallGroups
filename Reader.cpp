#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

#include "Reader.h"
/**
*  This class is reponsible for scanning the database.
*  It also maintain indexes of analyzing columns. 
**/

char * getNextWord(char * &str){
	char * begin = str;
	while(*str!=' ' && *str!='\n' && *str!='\0')
		str++;
	*str='\0';
    str++;
	return begin;
}

/**
* Constructor, It opens the file and initializes almost all private
* attributes. Only nrblines is not initialized.
* @param filename file name
* @param nbrcolumns number of columns atributes including the transaction id and category
* @param format string indicating the valid features to be used to calculate distance
**/		
Reader::Reader(char * filename, int nbrcols, char * format){
    nbrcolumns = nbrcols;
	f = fopen(filename,"r"); 
	initializeValidColumns(format); //it initializes indValidColumns and nbrValidColumns  
	this->filename = filename;
	if(f==NULL){
		printf("\nErro ao abrir o arquivo.");
		printf("\nPressione qualquer tecla para terminar...");
		getch();
		exit(0);
	}
}

/**
* Move the current file reader to next transaction.
* If there is next line it inicializes the vector column.
* The vector column has id, category and the features choosen from user
* Return -1 if next line doesn't exist.
**/
int Reader::nextLine(){
	char line[LINETAM];
	if(fgets(line,LINETAM,f)==NULL)
		return -1;
        else if (strcmp(line,"\n")==0)
                return -1;
	else{
		char * ptr = line;
		int ind=0;
		float val;
		column[0] = atof( getNextWord(ptr) ); //id
		column[1] = atof( getNextWord(ptr) ); //class
                //printf("\n %.0f %.0f ", column[0],column[1]);
                for(int i = 2; i< nbrcolumns; i++){
			val = atof( getNextWord(ptr));
			if(i==indValidColumns[ind]+1){//initialize also the id and class columns
				column[ind+2] = val;
                                //printf("%.4f ",val);
			    ind++;
			}
		}
		nbrObjs++;
		return 1;
	}
}
/**
* Move the current file reader to the first transaction.
**/
void Reader::firstTransaction(){
	fseek(f,0,0);
	nextLine(); /*!<reads the next e carries data to column vector>!*/
	nbrObjs=1; /*!<first valid transaction line>!*/
}

/**
* Gets the quantitative attribute value of the current transaction.
* Returns -1 if it doesn´t exist.
*/
float Reader::getValue(int cind){
	return(column[cind]);
}

/**
* Prints the values current transaction
* transaction.
**/
void Reader::showCurrent(){
	printf("\n");
	printf("%.0f ",column[0]);
	printf("%.0f ",column[1]);
	for(int i = 2; i< nbrValidColumns+2;i++)
		printf("%.4f ",column[i]);
}


void Reader::showCurrent(FILE * fa){
        fprintf(fa,"%.0f ",column[0]);
	fprintf(fa,"%.0f ",column[1]);
	for(int i = 2; i< nbrValidColumns+2;i++)
		fprintf(fa,"%.4f ",column[i]);
        fprintf(fa,"\n");
}

/**
* Initializes nbrValidColumns and indValidColumns from string format inputed by the user
*@param format string format inputed by the user	
**/
void Reader::initializeValidColumns(char * format){
	char * str = format;
	nbrValidColumns = 0;
	int i;
	char number[PRECISION];
	*str++; //firs is [
	if(*str=='+'){ //adding attributes
	   while(*str!=']'){
		   i=0;
		   str++;
		   while(*str!=',' &&  *str!=']'){
			   number[i++]=*str;
		       str++;
		   }
		   number[i]='\0';
		   indValidColumns[nbrValidColumns++] = atoi(number);
		}
		
	}	
	else if(*str=='-'){ //removing attibutes
	/**
	*@todo Do this part later.
        **/
	}
        printf("\n");
	for(int i = 0; i<nbrValidColumns;i++)
            printf("%d ",indValidColumns[i]);
	printf("\n");
}
