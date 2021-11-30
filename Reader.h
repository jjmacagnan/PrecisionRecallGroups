/**
*  This class is reponsible for scanning the database.
*  It also maintain indexes of analyzing columns. 
**/

#ifndef READER_H
#define READER_H
/*max number of characteres of a line of image features*/
#define LINETAM 10000
/*max number of atributes of a line of image features*/
#define MAX 400
/*max number of characteres in a float number of a image feature*/
#define PRECISION 12
#include<stdlib.h>
#include <math.h>
#include<stdio.h>
#include<string.h>

char * getNextWord(char * &str);

class Reader{
	protected:
		FILE * f;
		int nbrcolumns; /*!<Number of Total Transation Columns including id and category!>*/
		int nbrValidColumns; /*!<Number of selected features columns from user!>*/
		int nbrObjs; /*!<Number of transaction lines of the dataset!>*/
		int indValidColumns[MAX];/*!<Indexes of the select features columns!>*/  
		float column[MAX]; /*<Data from transaction id and category and valid features!>*/
		char * filename;
	public:
	/**
	* Constructor, It opens the file and initializes almost all private
	* attributes. Only nrblines is not initialized.
	* @param filename file name
	* @param nbrcolumns number of columns atributes including the transaction id and category
	* @param format string indicating the valid features to be used to calculate distance
	**/		
	Reader(char * filename, int nbrcols, char * format);
	
	/**
	* Move the current file reader to next transaction.
	* If there is next line it inicializes the vector column.
	* The vector column has id, category and the features choosen from user
	* Return -1 if next line doesn't exist.
	**/
	int nextLine();
	
	/**
	* Move the current file reader to the first transaction.
	*@return returns a vector with the data of the first transaction
	**/
	void firstTransaction();
	
	/**
	* Gets the value of column cind of the current transaction (only considering id, category and valid features)
	* Returns -1 if it doesn´t exist.
	* @param cind column index
	*/
	float getValue(int cind);
	
	/**
	* Prints the values current transaction
	* transaction.
	**/
	void showCurrent();
	void showCurrent(FILE * fa);
	/**
	* Initializes nbrValidColumns and indValidColumns from string format inputed by the user
	*@param format string format inputed by the user	
	**/
	void initializeValidColumns(char * format);
	
	/**
	*@return the current line features (id,categorie,choosen features)
	**/
	float * getFeatures(){
		return column;
	}
    
	/**
    *@return the number of columns including (id,categorie,choosen features)
	**/
	int getNumberColumns(){
		return nbrValidColumns+2;
	}

	/**
	*Sets the number of images or transactions in database
	**/
	void setNbrObjs(int val){
		nbrObjs = val;
	}
	
	/**
	*@return the number of images or transactions in database
	**/
	int getNbrObjs(){
		return nbrObjs;
	}
};
#endif
