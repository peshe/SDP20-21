#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

struct Node
{
	std::string				word;
	std::vector< Node* >	children;

	Node( const std::string& _word = "" ) : word( _word ) { }
};

void insertChildOnTheRightPlace( const std::string& currentChild, std::vector<Node*>& currentLine, std::vector< Node* >& lastLine, size_t& parentIndex )
{
	if ( currentChild != "*" )
	{
		Node* newNode = new Node( currentChild );
		assert( parentIndex < lastLine.size() );
		lastLine[ parentIndex ]->children.push_back( newNode );
		currentLine.push_back( newNode );
	}
	else
	{
		parentIndex++;
	}
}

Node* init( const std::string& fileName )
{
	std::ifstream file( fileName );
	if ( !file.is_open() ) return nullptr;

	std::string rootString;
	std::getline( file, rootString );

	Node* root = new Node( rootString );

	std::vector<Node*> lastLine;
	lastLine.push_back( root );

	while ( !file.eof() )
	{
		std::string line;
		std::getline( file, line );

		std::vector<Node*> currentLine;
		std::string currentChild;
		size_t parentIndex = 0;
		size_t pos = 0;
		while ( ( pos = line.find( ' ' ) ) != std::string::npos )
		{
			currentChild = line.substr( 0, pos );
			insertChildOnTheRightPlace( currentChild, currentLine, lastLine, parentIndex );
			line.erase( 0, pos + 1 );
		}

		insertChildOnTheRightPlace( line, currentLine, lastLine, parentIndex ); // for the last word of this level

		lastLine = currentLine;
	}

	file.close();
	return root;
}

void printSent( Node* root, int depth, int& maxRight )
{
	if ( !root )
	{
		return;
	}

	if ( maxRight < depth )
	{
		std::cout << root->word << " ";
		maxRight = depth;
	}

	for ( std::vector<Node*>::reverse_iterator it = root->children.rbegin(); it != root->children.rend(); ++it )
	{
		printSent( *it, depth + 1, maxRight );
	}

	/* or
	size_t size = root->children.size();
	for ( int index = size - 1; index >= 0; --index )
	{
		printSent( root->children[ index ], depth + 1, maxRight );
	}
	*/
}

void deleteTree( Node* root )
{
	if ( root )
	{
		for ( Node* child : root->children )
		{
			deleteTree( child );
		}
		delete root;
	}
}

int main()
{
	std::string filename;
	std::cin >> filename;

	Node* root = init( filename );
	int maxRight = 0;
	printSent( root, 1, maxRight );

	deleteTree( root );

	return 0;
}
