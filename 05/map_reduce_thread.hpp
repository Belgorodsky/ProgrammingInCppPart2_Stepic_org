// заголовок <thread> уже подключён.
// заново подключать не нужно
#include <numeric>
#include <algorithm>
#include <vector>

template <typename Iterator, typename f1_t, typename f2_t, typename number>
auto map_reduce(Iterator p, Iterator q, f1_t f1, f2_t f2, number nthreads)->decltype(f2(f1(*p),f1(*q)))
{
    using res_type=decltype(f2(f1(*p),f1(*q)));
    std::vector<Iterator> positions(nthreads+1);
    std::vector<std::thread> threads(nthreads);
    std::vector<res_type> fv(nthreads);
	auto d = std::distance(p, q);
	auto len = d / nthreads;
    positions[0] = p;
    for(auto i=1; i < nthreads; ++i)
    {
        positions[i] = positions[i-1];
        std::advance(positions[i], len);
    }
    positions[nthreads]=q;

    for(auto i=0; i<nthreads; ++i)
    {
        threads[i]=std::thread(
            [&,i]()
            {
                auto st = positions[i];
                fv[i]=f1(*st++);
                while(st != positions[i+1])
                {
                    fv[i]=f2(fv[i],f1(*st++));
                }
            }
        );
    }

    for(auto&& t: threads)
    {
        if (t.joinable())
            t.join();
    }
    return std::accumulate(fv.begin()+1, fv.end(), fv.front(), f2);
}
