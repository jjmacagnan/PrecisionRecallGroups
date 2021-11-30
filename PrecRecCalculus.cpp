#include "PrecRecCalculus.h"
#include "DistanceCalculus.h"


/**
* Calls everything to generate the graphic
**/
PrecRecCalculus::PrecRecCalculus(Reader * r1, Reader * r2){
	reader1 = r1;
	reader2 = r2;
	countPerCategory1();
	/*//Verify category counters
	*/
	for(int i = 0; i<NUMCAT;i++)
		printf("\ncat file 1 [%i]=%i",i,categories[i]);
		
	countPerCategory2();
	for(int i = 0; i<NUMCAT;i++)
		printf("\ncat file 2 [%i]=%i",i,categories[i]);
	
	loadData1();
    printf("\nDados Arquivo 1 Carregados com Sucesso");
    
    loadData1();
    printf("\nDados Arquivo 2 Carregados com Sucesso");
	/*Verify data loaded in objects vector
	printf("\n*********************************\n");
	for(int i = 0; i< reader->getNbrObjs();i++){
		printf("\ni=%d; %.0f %.0f",i,objects[i][0],objects[i][1]);
		for(int j=2; j<reader->getNumberColumns(); j++)
			printf(" %.4f",objects[i][j]);
	} */
	
	calculate();
}
	
/**
* Finds categories and counts images occurences of it
**/
void PrecRecCalculus::countPerCategory1(){
	int nbrobj=0;
	int cat;
	for(int i = 0; i< NUMCAT;i++){
		categories[i]=0;
	}
	reader1->firstTransaction();
	do{
		cat = (int) reader1->getValue(1);
		categories[cat]++;
		nbrobj++;
	}while(reader1->nextLine()!=-1);
	reader1->setNbrObjs(nbrobj);
}

/**
* Finds categories and counts images occurences of it
**/
void PrecRecCalculus::countPerCategory2(){
	int nbrobj=0;
	int cat;
	for(int i = 0; i< NUMCAT;i++){
		categories[i]=0;
	}
	reader2->firstTransaction();
	do{
		cat = (int) reader2->getValue(1);
		categories[cat]++;
		nbrobj++;
	}while(reader2->nextLine()!=-1);
	reader2->setNbrObjs(nbrobj);
}


	
/**
* Loads data in the object array
**/
void PrecRecCalculus::loadData1(){
	reader1->firstTransaction(); 
	float * t;
	int nbrcols = reader1->getNumberColumns();
	int line = 0;
	do{
		t = reader1->getFeatures();
		//object copy
		for(int i=0; i<nbrcols; i++){
			objects[line][i] =*t++;
		}
		line++;
	}while(reader1->nextLine()!=-1);
		//scan all the database to them be the target
}	

/**
* Loads data in the object array
**/
void PrecRecCalculus::loadData2(){
	reader2->firstTransaction(); 
	float * t;
	int nbrcols = reader2->getNumberColumns();
	int line = 0;
	do{
		t = reader2->getFeatures();
		//object copy
		for(int i=0; i<nbrcols; i++){
			objects[line][i] =*t++;
		}
		line++;
	}while(reader2->nextLine()!=-1);
		//scan all the database to them be the target
}	
	
	
/**
* Calcules Precision and Recall for each image as target and for all
* k
**/

void PrecRecCalculus::calculate(){
    int n1=reader1->getNbrObjs();
    int n2=reader2->getNbrObjs();
	for(int i=0;i<n1;i++){
		//meanprec[i]=0;
	       //meanrec[i]=0;
	}
	/**
	* id, category, distance
	**/
    trifloat * rank = new trifloat[n1];
    int fim,k;
	int nbrcols= reader1->getNumberColumns();
	DistanceCalculus * c1 = new DistanceCalculus(nbrcols);
	//selecting the target
	for( int i = 0; i< n2 ;i++){
		//scan all measures
		fim=-1;
		//printf("\nTarget:%.0f",objects[i][0]);
		for( int j = 0; j < n1 ;j++){
		    float dist =c1->getDistance(objects[i],objects[j]);
		    //printf("\nId=%.0f,cat=%0.f,Distance:%.4f",objects[j][0],objects[j][1],dist);
		    k = fim;
		    while(k>=0 && rank[k].dist > dist){
				rank[k+1].id = rank[k].id;
				rank[k+1].cat = rank[k].cat;
				rank[k+1].dist = rank[k].dist;
				k--;
		    }
		    rank[k+1].id = objects[j][0];
		    rank[k+1].cat = objects[j][1];
		    rank[k+1].dist = dist;
		    fim++;
		}

		//Check rank values");
		/*for(int z=0;z<=fim; z++)
			printf("\nn=%d, id=%.0f, cat=%.0f, dist=%.4f",z,rank[z].id,rank[z].cat,rank[z].dist); */

		processranking(rank,(int)objects[i][1]);

	}

	/**
	* Calcula do jeito do bayesa e yattes
	*/
	FILE * fp = fopen("outsuave.plt","w");
    	fprintf(fp,"\nset title \"Precision X Recall\"");
	fprintf(fp,"\nset xlabel \"Recall (%%)\"");
        fprintf(fp,"\nset ylabel \"Precision (%%)\"");
        fprintf(fp,"\nset xrange [0:1]\nset yrange [0:1]");
	fprintf(fp,"\nplot '-' title 'attribs=%d' with linespoints 1", reader1->getNumberColumns()-2);
	fprintf(fp,"\n####################");
	fprintf(fp,"\n#attribs=%d",reader1->getNumberColumns()-2);
        float p,r,ct,oldp=0;
        int deltar = 5;
        for(int rec=RECALLINTERVALS-1;rec>0;rec-=deltar){
           ct=0; p=0; r =0;
           for(k=0;k<deltar;k++){
              if(precision[rec-k][1]>0){
                 p += ((float)(precision[rec-k][0])/precision[rec-k][1]);
                 ct++;
               }
           }
           if(ct>0){
             r = (double)(rec)/100;
             p = p/(ct*100);
             if(oldp>p)
                p=oldp;
             fprintf(fp,"\n%.3f %.3f",r,p);
             printf("\nGrafico: %.3f %.3f",r,p);
             oldp=p;
           }

       	}
        fprintf(fp,"\n0 1");
        printf("\nGrafico:0 1");
        fprintf(fp,"\nend\npause -1");
	fclose(fp);

}

/**
* Calculate precision and recall for all knn and adds the results to precision array
**/
void PrecRecCalculus::processranking(trifloat * rank, int cattarget){
	int prec=0,rec=0,correct=0,tmp=0;
	//printf("\ncat=%d\n",cattarget);
	for(int knn=0;knn<reader1->getNbrObjs();knn++){
		tmp =(int)rank[knn].cat;
		if(tmp == cattarget){
		       correct++;
                       prec = (int)(correct*1000)/(knn+1);
                       prec = (prec%10) >=5 ? prec/10 +1: prec/10;
		       rec = (int)(correct*1000)/categories[cattarget];
		       rec = (rec%10>=5)? rec/10 +1 : rec/10;
                       precision[rec][0]+=prec; //adds precision value
		       precision[rec][1]++; //adds precision counter
		       //printf("\nknn=%d,prec=%d,rec=%d",knn,prec,rec);
                 }
        }
  }



