#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<climits>
#include<algorithm>
#include<sys/types.h>

#include <memory>
#include <stdexcept>
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

using typename std::vector;
#define UNDEFINED -1
#define MAXLEN 100+1
int cache[MAXLEN][MAXLEN];

int jlis(const vector<int>& A, const vector<int>& B);
int jlis_iter(const vector<int>& A, const vector<int>& B, int indexA, int indexB);

int main(void)
{
    int c;
    vector<int> A,B;
    std::cin>> c;
    while(c-->0)
    {
        size_t n,m;
        std::cin>> n >> m;
        A= vector<int>(n);
        B= vector<int>(m);
        for (size_t i=0; i<n; i++)
            std::cin>> A[i];
        for (size_t i=0; i<m; i++)
            std::cin>> B[i];
        std::cout<< jlis(A, B) << '\n';
    }
    return EXIT_SUCCESS;
}


int jlis(const vector<int>& A, const vector<int>& B)
{
    #if DBG==1
        std::cerr<< "\tA=[";
        for (auto i=A.begin(); i!= A.end(); i++){
            std::cerr<< *i << " ";
        }
        std::cerr<< "\b]\n\tB=[";
        for (auto i=B.begin(); i!= B.end(); i++){
            std::cerr<< *i << " ";
        }
        std::cerr<< "\b]\n";
    #endif

    int ret=0;
    memset(cache, -1, sizeof(cache));
    for (size_t n=0; n<A.size(); n++){
        for (size_t m=0; m<B.size(); m++){
            ret = std::max(ret, jlis_iter(A,B, n, m));
        }
    }
    return ret;
}
int jlis_iter(const vector<int>& A, const vector<int>& B, int indexA, int indexB)
{
    int& ret= cache[indexA+1][indexB+1];
    if (ret != UNDEFINED)
    {
    #if DBG==1
        std::cerr<< string_format("\tcache[%d][%d]= %d\n", indexA+1, indexB+1, ret);
    #endif
        return ret;
    }

    // A[indexA], B[indexB] 를 이미 포함하고 있기 때문에 2부터 시작한다.
    ret=2;
    for (size_t nextA=indexA+1; nextA< A.size(); nextA++){
        if ( std::max(A[indexA], B[indexB]) < A[nextA] )
            ret = std::max(ret, jlis_iter(A, B, nextA, indexB)+1);
    }
    for (size_t nextB=indexB+1; nextB< B.size(); nextB++){
        if ( std::max(A[indexA], B[indexB]) < B[nextB])
            ret = std::max(ret, jlis_iter(A, B, indexA, nextB)+1);
    }

    return ret;
}
