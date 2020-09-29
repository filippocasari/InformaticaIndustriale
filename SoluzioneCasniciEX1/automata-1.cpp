#include <iostream>

using namespace std;

int state = 0;

void transit(char r)
{	
	switch(r)
	{
        case 'a':

	     if(state == 0)
         {
			     state = 2;
				 break;
		 }

		 if(state == 1)
         {
			 cout << "lettera invalida" << endl;
			 exit(-1);
		 }

		 if(state == 2)
         {
			    state = 0;
	            break;
		 }
		 break;

	    case 'b':
	     if(state == 0)
         {
			  state = 1;
			  break;
		 }

		 if(state == 1)
         {
			  state = 1;
			  break;
		 }    

		 if(state == 2)
         {
			 cout << "lettera invalida" << endl;
			 exit(-1);
		 }
	     break;

		case 'c':
	     if(state == 0)
         {
			  state = 3;
			  break;
		 }

		 if(state == 1)
         {
			  state = 3;
			  break;
		 }

		 if(state == 2)
         {
			 cout << "lettera invalida" << endl;
			 exit(-1);
		 }
	     break;

	}
}

int main()
{
	char input;

	do
	{   cout << "inserisci lettera: " ;
		cin >> input;
        
        cout << "current state: " << state << endl;
		cout << "input: " << input << endl; 

		transit(input);

		cout << "new current state: " << state << endl;
		cout << "-------------------------------" << endl;

	}while(input != 'c');

   return 0;
}