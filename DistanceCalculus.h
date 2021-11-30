/**
* This class compute distance calculus from features from 2 images features (discarding the
* the columns with id and category
**/
#ifndef DISTANCECALCULUS_H
#define DISTANCECALCULUS_H

#include<math.h>
class DistanceCalculus{
protected:
	int nbrcolumns;
public:
	DistanceCalculus(int nbrc){
		nbrcolumns = nbrc;
	}
	  
	/**
	* Gets the L2 distance between two image represented by p1,p2
	* @param p1,p2 transactions lines with id,category and features
	* @param nbrcolumns number of coluns (id,category and features) in pi
	* @return distance between p1 and p2
	**/
	float getDistance(float p1[],float p2[]); 	
};
#endif
