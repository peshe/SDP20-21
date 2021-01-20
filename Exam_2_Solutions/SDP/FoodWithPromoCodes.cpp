#include <iostream>
#include <vector>
#include <unordered_map>

struct Promo
{
	int			perc;
	std::string	promoName;

	Promo( int p, const std::string& name ): perc( p ), promoName( name ) {}
};

using TFoodToPromocodesMap = std::unordered_map< std::string, std::vector< Promo > >;

void initPromos( TFoodToPromocodesMap& foods )
{
	int num;
	std::cin >> num;
	
	for ( int i = 0; i < num; ++i )
	{
		int			perc;
		std::string promoName;
		int			numFoods;
		std::cin >> perc >> promoName >> numFoods;

		Promo p( perc, promoName );
		
		for ( int j = 0; j < numFoods; ++j )
		{
			std::string nameFood;
			std::cin >> nameFood;

			foods[ nameFood ].push_back( p );
		}
	}
}

void printPromos( const std::vector<Promo>& promos )
{
	for ( const Promo& it : promos )
	{
		std::cout << it.perc << "% " << it.promoName << " ";
	}
}

void getPromos( TFoodToPromocodesMap& foods )
{
	int num;
	std::cin >> num;

	std::string food;

	for ( int i = 0; i < num; ++i )
	{
		std::cin >> food;
		std::unordered_map<std::string, std::vector<Promo>>::iterator it = foods.find( food );
		if ( it != foods.end() )
		{
			printPromos( *it );
		}
		else
		{
			std::cout << "no-promo";
		}
		std::cout << std::endl;
	}
}

int main()
{
	TFoodToPromocodesMap foods;
	initPromos( foods );
	getPromos( foods );
	return 0;
}