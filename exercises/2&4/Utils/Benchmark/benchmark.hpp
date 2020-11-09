

#include <iostream>
#include <chrono>



namespace dsa
{
	enum T_FORMAT
	{
		// 0001
		// 0010
		// 0100
		// 1000
		// 1111
		F_MICRO	= 1, //!< format the time in microseconds => 1000 microseconds = 1 millisecond 
		F_MILLI	= 2, //!< format the time in milliseconds => 1000 milliseconds = 1 second 
		F_SEC	= 4,   //!< format the time in seconds      => 60 seconds = 1 minute
		F_MIN	= 8,   //!< format the time in minutes
		F_ALL	= 15    //!< format the time as: m-s-ms-us
	};

	template <typename Func>
	void benchmarking_this_function( const Func& f, T_FORMAT format = T_FORMAT::F_MICRO,
										std::string name = "", std::ostream& os = std::cout )
	{
		using namespace std::chrono;
		time_point<high_resolution_clock> start = high_resolution_clock::now();

		f();

		time_point<high_resolution_clock> end = high_resolution_clock::now();
		
		if ( !name.empty() ) os << '[' << name << "] " << std::endl;

		if ( format & T_FORMAT::F_MICRO )
		{
			os << duration_cast<microseconds>( end - start ).count() << " microseconds" << std::endl;
		}
		if ( format & T_FORMAT::F_MILLI )
		{
			os << duration_cast<milliseconds>( end - start ).count() << " milliseconds" << std::endl;
		}
		if ( format & T_FORMAT::F_SEC )
		{
			os << duration_cast<seconds>( end - start ).count() << " seconds" << std::endl;
		}
		if ( format & T_FORMAT::F_MIN )
		{
			os << duration_cast<minutes>( end - start ).count() << " minutes" << std::endl;
		}

	}


}
