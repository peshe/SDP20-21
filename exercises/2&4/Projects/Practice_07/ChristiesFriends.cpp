#include <iostream>
#include <forward_list>
#include <stack>
#include <ctime>


struct Friend
{
    int     fPopularity;
    bool    fIsMale;
    Friend( int popularity, bool isMale )
        : fPopularity( popularity )
        , fIsMale( isMale )
    {}
};


using   FriendList   = std::forward_list< Friend >;
const size_t    INIT_FR_COUNT   = 30;   // Initial random friends count
const size_t    POPUL_RANGE     = 100;  // Popularity will be in the range [0; RANGE)
const size_t    MALE_CHANCE     = 50;   // in %
const size_t    DELETE_RATIO    = 25;   // in %


size_t initFriendList( FriendList& friends )
{
    size_t  count   = 0;
    FriendList::const_iterator   insertIt    = friends.before_begin();
    for ( size_t i = 0; i < INIT_FR_COUNT; i++ )
    {
        size_t  chance  = rand() % 100;
        Friend  temp    = { rand() % POPUL_RANGE,
                            chance < MALE_CHANCE };

        // Effectively does a constant push_back for a forward_list
        insertIt = friends.insert_after( insertIt, temp );
        ++count;
    }

    return count;
}


std::ostream& operator<<( std::ostream& out, const Friend& fr )
{
    return out << "[ " << ( fr.fIsMale ? "m" : "f" ) << ", " << fr.fPopularity << " ]";
}


std::ostream& operator<<( std::ostream& out, const FriendList& friends )
{
    FriendList::const_iterator   it  = friends.begin();
    if ( !friends.empty() )
        out << *it++;

    while ( it != friends.end() )
        out << " -> " << *it++;

    return out;
}


int main()
{
    srand( time( nullptr ) );

    FriendList  christiesFriends;
    size_t      initialFriendsCount;
    initialFriendsCount = initFriendList( christiesFriends );
    std::cout << "Initial friends count: " << initialFriendsCount << "\n";
    std::cout << "Initial friends: \n" << christiesFriends << "\n";

    std::stack< Friend >        deletedFriends;
    size_t                      currFrCnt   = initialFriendsCount;
    FriendList::iterator        firstIt     = christiesFriends.begin();
    FriendList::iterator        secondIt    = christiesFriends.begin();
    FriendList::const_iterator  lastStartIt = firstIt;  // The last iterator a full search was started from

    while ( currFrCnt > initialFriendsCount * ( ( 100 - DELETE_RATIO ) * 0.01 ) )
    {
        secondIt    = firstIt;

        if ( secondIt == christiesFriends.end() )
        {
            firstIt = christiesFriends.begin();
            continue;
        }
        else
        {
            ++secondIt;
        }

        if ( secondIt->fIsMale && firstIt->fPopularity > secondIt->fPopularity )
        {
            deletedFriends.push( *secondIt );
            firstIt     = christiesFriends.erase_after( firstIt );
            lastStartIt = firstIt;
            --currFrCnt;
        }
        else if (  secondIt->fIsMale
                && !deletedFriends.empty()
                && deletedFriends.top().fPopularity > secondIt->fPopularity )
        {
            *secondIt   = deletedFriends.top();
            lastStartIt = secondIt;
            deletedFriends.pop();
        }
        else
        {
            ++firstIt;
            if ( firstIt == lastStartIt )
            {
                // Done a full iteration from lastStartIt back to it again without any changes
                break;
            }
        }
    }

    std::cout << "\nFriends count after deletion: " << currFrCnt << "\n";
    std::cout << "Deleted percentage: " << 100 - ( (float)currFrCnt / initialFriendsCount ) * 100 << "%\n";
    std::cout << "Friends after deletion: \n" << christiesFriends << "\n";

    return 0;
}
