#include "CircularList.hpp"



size_t game( dsa::CircularList<int>&& knights )
{
	dsa::CircularList<int>::iterator currentKnight = knights.begin();

	while ( knights.getSize() != 1 )
	{
		currentKnight = knights.removeAfter( currentKnight );
	}
	return knights.front();
}

class CircularTable
{
public:
	void setKnights( const dsa::CircularList<int>& knights )
	{
		this->knights = knights;
	}
	void game();
private:
	dsa::CircularList<int> knights;
};

int main()
{

	//CircularTable table;
	dsa::CircularList<int> knights;

	for ( int i = 1; i <= 12; ++i )
	{
		knights.push_back( i );
	}
	//table.setKnights( knights );
	//table.game();


	std::cout << "Winner is: " << game( std::move( knights ) ) << std::endl;;


	return 0;
}