

#include <iostream>
#include <chrono>



namespace dsa
{
	enum class T_FORMAT
	{
		F_MICRO	= 1, //!< format the time in microseconds => 1000 microseconds = 1 millisecond 
		F_MILLI	= 2, //!< format the time in milliseconds => 1000 milliseconds = 1 second 
		F_SEC	= 4,   //!< format the time in seconds      => 60 seconds = 1 minute
		F_MIN	= 8,   //!< format the time in minutes
		F_ALL	= 15    //!< format the time as: m-s-ms-us
	};

	template <typename Func>
	void benchmarking_this_function( const Func& f, T_FORMAT format = T_FORMAT::F_MICRO,
										std::string name = "", std::ostream os = std::cout )
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

		f();

		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

		if ( format & F_MICRO )
		{
			os << std::chrono::duration_cast<std::chrono::microseconds>( start - end ).count() << std::endl;
		}
		if ( format & F_MILLI )
		{
			os << std::chrono::duration_cast<std::chrono::milliseconds>( start - end ).count() << std::endl;
		}
		if ( format & F_SEC )
		{
			os << std::chrono::duration_cast<std::chrono::seconds>( start - end ).count() << std::endl;
		}
		if ( format & F_MIN )
		{
			os << std::chrono::duration_cast<std::chrono::minutes>( start - end ).count() << std::endl;
		}

	}


}