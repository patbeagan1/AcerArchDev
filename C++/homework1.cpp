#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;

struct TreeNode
{
	string word;
	vector<int> line;
	int freq;
	TreeNode* ante;
	TreeNode* post;
};

//GLOBALS
//----------------------
int currLine = 0;
TreeNode* head = NULL;
//----------------------

TreeNode* newNode(string s)
{
	TreeNode* branch = new TreeNode;
	branch->word = s;
	branch->line.push_back(currLine);
	branch->freq = 1;
	branch->ante = NULL;
	branch->post = NULL;
	return branch;
}

TreeNode* insert(TreeNode* j, string s)
{
	//if(j==NULL)
	//{
		TreeNode* tmp = newNode(s);
		if(head==NULL)
			head = tmp;
		return tmp;
	//}
	//else
	/*{
//		int alpha = s.compare(j->word);//j->word.compare(s);//
		if(alpha<0)
		{
			//cout<<j->word<<" BEFORE "<<s<<endl;
			j->ante = insert(j->ante,s);
		}
		if(alpha>0)
		{
			//cout<<j->word<<" AFTER "<<s<<endl;
			j->post = insert(j->post,s);
		}
		if(alpha==0)
		{
			//cout<<"EXISTING-NODE "<<s<<j->word<<endl;
			j->freq++;
			j->line.push_back(currLine);
			return j;
		}
		else
		{
			return j;
		}
	}*/
}

void find(TreeNode* i)
{
	if(i==NULL)
		return;

	find(i->ante);
	//:::::::::::::::::::::::::
	int spaces = 10- i->word.length();

	cout<< i->word;
	for(int r = 0; r<spaces; r++)
		cout<<" ";
	cout<< " Frequency:" << i->freq
		<< "  Occurs line(s):";
	for(int q = 0; q< i->line.size(); q++)
		cout<< i->line.at(q);
	cout<<endl;
	//:::::::::::::::::::::::::
	find(i->post);
}

int main () {
	string line;
	char* input;

	cout<<"Enter the precise name of the input file."<<endl
	<<"If you get it wrong, program will exit."<<endl;
	cin>>input; 

	ifstream file ("input.txt");

	while(getline(file,line)){
		currLine++;
		//getline(file, line);
		//cout<<line<<endl;

		char* cstr = new char[line.length()+1];
		strcpy(cstr,line.c_str());
		strtok(cstr, " ");

		while(cstr!=NULL)
		{
			//if(head==NULL)
			//head = newNode(cstr);
			insert(head, cstr);
			//find(head);
			//cout<<endl;
			cstr = strtok(NULL, " ");
		}
	}
	find(head);
	return 0;
};

/*
sources:
stackoverflow.com/questions/7352099/stdstring-to-char
www.cprogramming.com/tutorial/lesson12.html
*/
