//============================================================================
// Name        : smartGroceryList.cpp

/*
 * There are two types of products:
 * - everyday products you buy to survive
 * - additional products to compensate any possible nutritional deficiencies
 *
 * This console program shows you two such additional products you should buy today.
 * It takes random products from a comprehensive list (50+)
 * of healthy products containing all things neccessary for your health
 * (all vitamins, minerals, indispensable amino acids, fatty acids)
 * plus additional things to improve your wellbeing
 * (cholesterol reductors and chocholate).
 * The list contains 3 products for every necessary thing.
 * From these 3 products one has a higher priority, and 2 others - lower priority
 * (the product with the highest nutritional value + 2 a bit lower value for diversity)
* you can edit lists of products and priorities by editing corresponding txt files.
*/
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;



	void readingBase(string (&arrProducts)[1000], int (&arrImportance)[1000], int& ItemsNumber){

		string line;
		int k=0;
		  ifstream myfile ("products.txt");
		  if (myfile.is_open())
		  {
		    while ( getline (myfile,line) )
		    {

		    	arrProducts[k] = line;
		    	k++;

		      //cout << line << '\n';
		    }
		    myfile.close();
		  }

		  else cout << "ERROR. Unable to open file products.txt";

		  ItemsNumber=k;

		  	  	  int summ=0;

		  		  ifstream myfile2 ("importance.txt");
		  		  if (myfile2.is_open())
		  		  {
		  		    for (int i=0; i<k; i++)
		  		    {
		  		    	 getline (myfile2,line);
		  		    	istringstream convert(line);
		  		     	if ( !(convert >> arrImportance[i]) )
		  		     		arrImportance[i] = 0;

		  		     	summ+=arrImportance[i];

		  		    }
		  		    myfile2.close();
		  		  }

		  		  else cout << "ERROR. Unable to open file importance.txt" << endl;

		  		  if (summ!=100000) {cout << "ERROR. The summ of importances is not 100 000" << endl;}



	};


/* generates the index of a random product.
 *
 * The higher the importance of product,
 * the higher is its probability of showing up
 *
 * How it works:
 * an interval of 0 - 100 000 is divided into intervals of different lengths
 * the length = importance of product
 * random number is generated
 * the interval where the number is located corresponds to the product

*/

int IndexOfRndProduct(int arrayOfWeights[], int sizeOfArray){


	int startArray[sizeOfArray];
	int endArray[sizeOfArray];

	startArray[0] = 0;
	endArray[0] = arrayOfWeights[0];

	//cout << startArray[0] << " " << endArray[0] << endl;

	for(int i=1; i < sizeOfArray; i++){ //generating the intervals
		startArray[i] = endArray[i-1];
		endArray[i] = startArray[i]+arrayOfWeights[i];

		//cout << startArray[i] << " " << endArray[i] << endl;
	}




	  int randomNumber0_99 = rand() % 100000;

	  //cout << "rnd " << randomNumber0_99 << endl;

	  // searching the interval where the rnd number is located
	  int j=0;
	  while ((randomNumber0_99 > startArray[j]) && (j<sizeOfArray)){
		  j++;
	  }
	  j = j-1;


	 // cout << "j " << j << endl;
	  int index4rnd = j;



	return index4rnd;

}

void output4user(int actualN_OfProducts, string Products[], int productImportance[], int indexOfProduct1, int indexOfProduct2){

	//cout << actualN_OfProducts  << endl;

	cout << "EVERYDAY PRODUCTS:"  << endl;
	for (int m=0;m<actualN_OfProducts;m++){
		if (productImportance[m]==0) {cout << Products[m]  << ", ";}
	}
	cout << endl;
	cout << "---------"  << endl;
	cout << "SPECIAL PRODUCTS FOR TODAY:"  << endl;
	cout << Products[indexOfProduct1]  << ", " << Products[indexOfProduct2] << endl;



}


int main() {

	srand (time(NULL));


	const int maxOfProducts = 1000; //theoretical max number of products


	string Products[maxOfProducts];

	int productImportance[maxOfProducts];
	int actualN_OfProducts;

	readingBase(Products, productImportance, actualN_OfProducts);


int indexOfProduct1 = IndexOfRndProduct(productImportance, actualN_OfProducts);
int indexOfProduct2 = 0;

do { //two products must be different
	indexOfProduct2 = IndexOfRndProduct(productImportance, actualN_OfProducts);
} while (indexOfProduct1==indexOfProduct2);


output4user(actualN_OfProducts, Products, productImportance, indexOfProduct1, indexOfProduct2);


	return 0;
}