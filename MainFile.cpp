//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

/*
*  Generate a precision/recall graphic script
*  argv[1] = input filename
*  argv[2] = total number of columns of file, including the transaction id and category
*  argv[3] = string in the format [+i1,i2,...,ik]
*  with the indexes of columns to be cosidered
*  the first attribute of the feature vector is 1 (one).
*  ps: the output file is default out.plt
**/
#include "Reader.h"
#include "DistanceCalculus.h"
#include "PrecRecCalculus.h"
#include <conio.h>

int main(int argc, char * argv[]){
	char * filename1 = argv[1];
	char * filename2 = argv[2];
	int nrocols= atoi(argv[3]);
	char * format = argv[4];
	printf("\n%s",filename1);
	printf("\n%s",filename2);
	printf("\n%d",nrocols);
	printf("\n%s",format);
	Reader * reader1 = new Reader(filename1,nrocols,format);
	Reader * reader2 = new Reader(filename2,nrocols,format);
	//See if database was read correctly
    FILE * fa1 = fopen("datasel1.txt","w");
    FILE * fa2 = fopen("datasel2.txt","w");
	
	reader1->firstTransaction();
	do{
		reader1->showCurrent(fa1);
	}while(reader1->nextLine()!=-1);
        fclose(fa1);
        
    reader2->firstTransaction();
	do{
		reader2->showCurrent(fa2);
	}while(reader2->nextLine()!=-1);
        fclose(fa2);
    
	
	/*//See if DistanceCalculus is correctly working
	DistanceCalculus * cq = new DistanceCalculus(4);
	//test2: Distance Function ok
	//vector has id, categories, features
	float c1[] = {0,0,7,4}, c2[] = {0,0,4,8};
	printf("\n****\n %.4f\n****",cq->getDistance(c1,c2)); */
	
	PrecRecCalculus * prc = new PrecRecCalculus(reader1,reader2);
        printf("\nProgram ended, press any key to continue...");
        getch();
}

