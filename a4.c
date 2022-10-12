/*name: Killian Hasson		date: 03/02/2022		class: CS201
 *
 * 	For this assignement we were tasked with creating a program that would take in a certain number of arguments
 * and with said arguments be able to carry out the users choice of mathmatical formulas. This meant that we needed
 * to have a menu that would allow the user to interact with it multiple times and keep the original arguments. For
 * myself I created a doubly linked list where each node held the arguments data aswell as a previous and a next 
 * pointer to the next or previous argument. Overall there was alot more I would have liked to do with this but I was
 * happy with the end result.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

//Struct node for containing each argument entered by the user
struct node
{
	int is_num;
	int index;
	char * arg_str;
	int arg_int;
	struct node * next;
	struct node * prev;
};
//Below are the function prototypes that were implemented below main
int menu(unsigned int num_items, char * choices[]);
void add(struct node * curr, char * arg);
void die(struct node * head);
void math_add(struct node * head);
void math_sub(struct node * head);
void math_mult(struct node * head);
void math_div(struct node * head);
void math_mod(struct node * head);
void reverse_input(struct node * head);


int main(int argc, char * argv[])
{
	//two node pointers for traversing and tracking the DLL
	struct node* head = NULL;
	struct node* temp = NULL;
	//Check argument count
	if(argc < 3 || argc > 16)
	{
		printf("Error\n");
		exit(1);
	}
	//Loop through the input arguments, create a DLL
	for(int i = 1; i < argc; i++)
	{
		//Node will be created for each argument
		struct node* curr = (struct node*)malloc(sizeof(struct node));
		curr->prev = NULL;
		curr->next = NULL;
		//set head
		if(head == NULL)
		{
			head = curr;
			temp = head;
		}
		else
		{
			curr->prev = temp;
		}
		temp->next = curr;
		add(curr, argv[i]);
		temp = temp->next;
	}	
	temp = head;
	//Set up an array of choices for menu functions, aswell as an int for correct selection
	int num_choices = 7;
	char *choices[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"};
	void (*op[])(struct node * a) = {&die, &math_add, &math_sub, &math_mult, &math_div, &math_mod, &reverse_input};
	int menu_item;
	//loop for various function calls for same input
	while(1)
	{
		menu_item = menu(num_choices, choices);
		op[menu_item](head);
	}
	
}

//Menu function for display and selecting desired function call
int menu(unsigned int num_items, char * choices[])
{
	int menu_item = 0;

  	printf("The operations to be performed on those arguments will be based on the following menu:\n");
  
	for (int i = 0; i < num_items; i++) 
	{
    		printf("%u.      %s\n", i, choices[i]);
  	}
  	
	printf("Menu item: ");
  	fscanf(stdin, "%d", &menu_item);
  	//Check for correct menu select
	if (menu_item > num_items - 1 || menu_item < 0) 
	{
    		//Invalid selection error
   		 return 0;
  	}
  	return menu_item;
}

//Add the arguments to the DLL
void add(struct node * curr, char * arg)
{
	char * next;
	//Check if the argument is a hex
	if(!memcmp(arg, "0x", 2) || !memcmp(arg, "0X", 2) || !memcmp(arg, "-0x", 3) || !memcmp(arg, "-0X", 3))
	{
		curr->arg_int = strtol(arg, &next, 16);
	}
	else
	{
		//Arg is an int
		curr->arg_int = strtol(arg, &next, 10);
	}
	//assign and track node info
	curr->is_num = ((int)*next != 0);
	curr->arg_str = arg;
}

//Add all the nodes in the DLL
void math_add(struct node * head)
{ 	
	int result = 0;
  	struct node * temp = head;
  	//Loop through the DLL adding all arg_ints
	while (temp != NULL) 
	{
		result += temp->arg_int;
    		printf("%d", temp->arg_int);
    		//Properly display math symbols
		if (temp->next != NULL) 
		{
      			printf(" + ");
		} 
		else 
		{
      			printf(" = ");
    		}
	temp = temp->next;
  	}
	printf("%d\n", result);
  
	//Loop through and display the math done above as hex values
	temp = head;
	while (temp != NULL) 
	{
    		printf("0x%x", temp->arg_int);
    		if (temp->next != NULL) 
		{
      			printf(" + ");
		} 
		else 
		{
      			printf(" = ");
    		}
	temp = temp->next;
  	}
	printf("0x%x\n", result);
}

//Exit the program via the menu
void die(struct node * head)
{
	printf("Exiting\n");
	exit(0);
}

//Subtract the values entered left to right
void math_sub(struct node * head)
{
	//Start with the first value instead of 0
  	int result = head->arg_int;
  	struct node * temp = head;
	//Count the first iteration
  	int first_iter = 1;
  	//Loop through the DLL and subtract the next nodes data
	while (temp != NULL) 
	{
		//Check if this is the first node or not
    		if (!first_iter) 
		{
      			result -= temp->arg_int;
    		}
    		printf("%d", temp->arg_int);
		//Properly display math symbols
    		if (temp->next != NULL) 
		{
      			printf(" - ");
    		} 
		else 
		{
      			printf(" = ");
    		}
		//Set first iteration to zero to properly loop
		first_iter = 0;
   	 	temp = temp->next;
  	}
  	
	//Display the above math but in hex
	printf("%d\n", result);
  	temp = head;
  	while (temp != NULL) 
	{
    		printf("0x%x", temp->arg_int);
    		if (temp->next != NULL) 
		{
      			printf(" - ");
    		} 
		else 
		{
      			printf(" = ");
    		}
    		temp = temp->next;
  	}
  
	printf("0x%x\n", result);
}

//Multiply the DLL nodes from left to right
void math_mult(struct node * head)
{
	//Start with 1 to not effect the end result
  	int result = 1;
  	struct node * temp = head;
	//Loop through and multiply each node by the following node
  	while (temp != NULL) 
	{
    		result *= temp->arg_int;
    		printf("%d", temp->arg_int);
    		//Properly display the equation
		if (temp->next != NULL) 
		{
      			printf(" * ");
    		} 
		else 
		{
      			printf(" = ");
    		}
    		temp = temp->next;
  	}
	printf("%d\n", result);
  	//Begin the loop again but only displaying in hex values
	temp = head;
  	while (temp != NULL) 
	{
    		printf("0x%x", temp->arg_int);
    		if (temp->next != NULL) 
		{
      			printf(" * ");
    		} 
		else 
		{
      			printf(" = ");
    		}
    		temp = temp->next;
  	}
  
	printf("0x%x\n", result);
}

//Divide the first argument by the second argument
void math_div(struct node * head)
{
	printf("div\n");
	if(head == NULL|| head->next == NULL)
	{
		//not enough args
	}
	if(!head->is_num || !head->next->is_num)
	{
		//one of the first two args are not nums
	}
	//Used doubles since the requirements for grading were more specific data
	double num1 = head->arg_int;
  	double num2 = head->next->arg_int;
  	double result = num1 * pow(num2, -1.0f);
  	printf("%.0f / %.0f = %.6f\n", num1, num2, result);	

}

//Modulo function, first two numbers
void math_mod(struct node * head)
{
  	if (head == NULL ||head->next == NULL) {
    	//Not enough args error
  	}
  	if(!head->is_num || !head->next->is_num) 
	{
    	//One of the first two arguments is not a number error
  	}
  	int num1 = head->arg_int;
  	int num2 = head->next->arg_int;
  	unsigned int result = num1 % num2;
  	//Properly display
  	printf("%d %% %d = %d\n", num1, num2, result);
  	printf("%s0x%x mod %s0x%x = 0x%x\n", num1 < 0 ? "-" : "", num1 < 0 ? num1 * -1 : num1, num2 < 0 ? "-" : "", num2 < 0 ? num2 * -1 : num2, result);
}

//Reverse the input of the user
void reverse_input(struct node * head)
{
  	struct node * tail = head;
  	//Traverse to the end of the DLL
  	while (tail->next != NULL) 
  	{
    		tail = tail->next;
  	}
	//Using tail traverse backwards
  	while (tail != NULL) 
	{
		//Reverse the input of each string in the node
    		for (int i = strlen(tail->arg_str) - 1; i >= 0; i--) 
		{
      			printf("%c", tail->arg_str[i]);
    		}
    		printf(" ");
    		tail = tail->prev;
  	}
	printf("\n");
}

