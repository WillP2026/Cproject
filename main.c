#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

//node of our tree
struct node {
    char letter;
    struct node* left;
    struct node* right;
};

//allocates a new node with given letter
//right and left pointers are NULL
struct node* createNode(char character) {

    struct node* ptr = malloc(sizeof *ptr);
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->letter = character;
    return ptr;
    //return NULL;
}

//build the tree needed to do morse to english conversion
//see project description
void buildMorseTree(struct node* root) {
    char letterstomorse[][10] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    struct node* current = root;

    for (int i = 0; i < 26; i++)
    {
        current = root;
        for (int j = 0; j < strlen(letterstomorse[i]); j++)
        {
            if (letterstomorse[i][j] == '.')
            {
                if (current->left == NULL)
                {
                    current->left = createNode('0');
                }
                current = current->left;
            }
            else if (letterstomorse[i][j] == '-')
            {
                if (current->right == NULL)
                {
                    current->right = createNode('0');
                }
                current = current->right;
            }
        }
        current->letter = letters[i];

    }
    

}

//prints the Morse Tree in preorder
void printMorseTree(struct node* node) {
    if (node == NULL)
    {   
        return;
    }


    printf("%c ",node->letter);
    
    printMorseTree(node->left);
    printMorseTree(node->right);
    
}

//converts all the characters(dot, dash, space, slash) pointed to 
//by characters and converts to english characters and places the 
//english conversions in output.
//This function will create the root by calling createNode.
//The data of the root node can be a character 0
//and will build the tree by calling buildTree(root)
//After building the tree, call printMorseTree to show it was built correctly
void convertMorseToEnglish(char* characters, char* output) {
    //struct node* root = createNode('0');
    //buildTree(root);
    //printMorseTree(root);
    //Convert morse characters to english output

    int counter = 0;
    struct node* root = createNode('0');
    struct node* current = root;
    buildMorseTree(current);
    current = root;
    printMorseTree(current);
    printf("\n");
    current = root;

    for (int i = 0; i < 200; i++)
    {
        if (characters[i] == '-')
        {
            current = current->right;
        }
        else if (characters[i] == '.'){
            current = current->left;
        }
        else if (characters[i] == ' '){
            output[counter] = current->letter;
            current = root;
            counter++;
        }
        else if (characters[i] == '/'){

            output[counter] = ' ';
            current = root;
            counter++;
            i++;

        }
        else if (characters[i] == '\0'){
            output[counter] = '\0';
            i = 200;
        }
    }
    printf("%s", output);
    
}

int main(int argc, char** argv) {
	//create and initialize arrays message and output
	char message[200] = { '0' };
	char output[100] = { '\0' };
	//the input file is the second argument when executing the program
	FILE* datafile = fopen(argv[1], "r");/* open file for reading*/
	if (datafile == NULL) { printf("can't open\n"); }
	else
	{
		fgets(message, 199, datafile);
		int length = strlen(message);
		message[length] = ' ';
		message[length + 1] = '\0';
		convertMorseToEnglish(message,output);
		// print out the output
	}
}

//helper functions
