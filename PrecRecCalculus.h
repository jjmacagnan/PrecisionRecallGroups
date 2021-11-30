/**
* Process all data by calling reader function and generates graphics
* of precision and recall.  
**/

#ifndef PRECRECCALCULUS_H
#define PRECRECCALCULUS_H


#include "Reader.h"

#define NUMCAT 100 //number max of categories
#define RECALLINTERVALS 101 //number of recall intervals
#define MAXOBJECTS 15000

typedef struct{
    float id;
    float cat;
    float dist;
} trifloat;

class PrecRecCalculus{
private:
	Reader * reader1;
	Reader * reader2;
	
	/**
	*Counter of images in a category.
	*The cateory is the index of a vector.
	**/
	int categories[NUMCAT];
	
	/* It has the sum of precisions for a determined recall interval
	defined by the index. For instance, to store values of
	precision 0.1 and 0.3 that occured for a recall of 1%:
	precision[1][0] =0.1+0.3 =0.4
	precision[1][1] = 2 (number of values computed)*/
    int precision[RECALLINTERVALS][2];
	
	/*
	  It has data from image id, categorie and choosen features,
	  loaded from database.
	*/
	float objects[MAXOBJECTS][LINETAM];
	
	/**
	* It has the mean of values of precision for a determining k
	*for instance, meanprec[1] has the mean of precision values 
	*for k =1
	**/
	//float meanprec[MAXOBJECTS];
	
	/**
	* It has the mean of values of precision for a determining k
	*for instance, meanrec[1] has the mean of recall values 
	*for k =1
	**/
	float meanrec[MAXOBJECTS];
	
public:
	/**
	* Calls everything to generate the graphic
	**/
	PrecRecCalculus(Reader * r1, Reader * r2);
	
	/**
	* Finds categories and counts images occurences of it
	**/
	void countPerCategory1();
	
	/**
	* Finds categories and counts images occurences of it
	**/
	void countPerCategory2();
	
	/**
	* Loads data in the target array
	**/
	void loadData1();
	
	/**
	* Loads data in the target array
	**/
	void loadData2();
		
	/**
	* Calcules Precision and Recall for each image as target and for all k
	**/
	void calculate();
	
	/**
	* Calculate precision and recall for all knn and adds the results to precision array
	**/
	void processranking(trifloat * rank, int cattarget);


};	
#endif
