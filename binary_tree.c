/* Author  : Van Nguyen
 * Class   : Data Structures
 * Project : Binary Tree
 * Due Date: 2019.03.29
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tree
{
	char line[125];
	char letter;
	struct tree * left;
	struct tree * right;
};

struct tree * insert(struct tree * reader, char letter);
void print_forward(struct tree * reader, FILE * fp);
void print_backward(struct tree * reader, FILE * fp);
struct tree * free_tree(struct tree * reader);
int count(FILE * fp, char letter);

int main(void)
{
	char file[65];
	char line[125];
	FILE * fp;
	struct tree * reader = NULL;
	char letter, low, high;
	int count = 0;
	
	printf("Please enter the name of the file you wish to open: \n");
	scanf("%s", file);
	fp = fopen(file, "r");
	if (!fp)
	{
		printf("Could not open file %s", file);
		exit(EXIT_FAILURE);
	}
	
    letter = fgetc(fp);
    if (isalpha(letter)) 
    {
        low = letter;
        high = letter;
        reader = insert(reader, letter);
		count++;
    }
	
	while ((letter = fgetc(fp)) != EOF)
	{
		if (isalpha(letter))
		{
			reader = insert(reader, letter);
			count++;
			if (letter < low)
			{
				low = letter;
			}
			else if (letter > high)
			{
				high = letter;
			}
		}
	}
	
	printf("In Order:\n");
	print_forward(reader, fp);
	printf("Reverse Order:\n");
	print_backward(reader, fp);
	printf("Total number of letters: %d\n", count);
	printf("Lowest Letter Value: %c\n", low);
	printf("Highest Letter Value: %c\n", high);
	free_tree(reader);
	fclose(fp);
	
}

struct tree * insert(struct tree * reader, char letter)
{
	if (!reader)
	{
		struct tree * new_node = (struct tree *)malloc(sizeof(struct tree));
		new_node->letter = letter;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}
	else
	{
		if (letter < reader->letter)
		{
			reader->left = insert(reader->left, letter);
		}
		else if (letter > reader->letter)
		{
			reader->right = insert(reader->right, letter);
		}
		return reader;
	}
}

void print_forward(struct tree * reader, FILE * fp)
{
	if (!reader)
	{
		return;
	}
	print_forward(reader->left, fp);
	printf("\t%c, %d\n", reader->letter, count(fp, reader->letter));
	print_forward(reader->right, fp);
}

void print_backward(struct tree * reader, FILE * fp)
{
	if (!reader)
	{
		return;
	}
	print_backward(reader->right, fp);
	printf("\t%c, %d\n", reader->letter, count(fp, reader->letter));
	print_backward(reader->left, fp);
}
	
int count(FILE * fp, char letter)
{
	char target;
	int num = 0;
	
	fseek(fp, 0, SEEK_SET);
	while ((target = fgetc(fp)) != EOF)
	{
		if (target == letter)
		{
			num++;
		}
	}
	return num;
}
	
struct tree * free_tree(struct tree * reader)
{
	if (!reader)
	{
		return NULL;
	}
	free_tree(reader->left);
	free_tree(reader->right);
	free(reader);
}