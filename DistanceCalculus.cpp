#include "DistanceCalculus.h"
/**
* Gets the L2 distance between two image represented by p1,p2
* @param p1,p2 transactions lines with id,category and features
* @param nbrcolumns number of coluns (id,category and features) in pi
* @return distance between p1 and p2
**/
float DistanceCalculus::getDistance(float p1[],float p2[])
{
	float dist = 0;
    for(int i = 2; i<nbrcolumns;i++)
		dist = dist + fabs(pow(p1[i]-p2[i],2));
	dist = sqrt(dist);
    return dist;
}