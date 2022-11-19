#include "../libs/data_controller.hpp"

#include <vector>
#include <set>

namespace data
{
    class controller
    {
    private:
        controller() = default;
        ~controller() = default;

        int m_mappers, m_reducers;
    
    public:
        std::vector<std::set<long long>*> m_map;

        static controller& get()
        {
            static controller instance;
            return instance;
        }

        std::vector<std::set<long long>*>& mapper_results() { return m_map; }
        int& mappers() { return m_mappers; }
        int& reducers() { return m_reducers; }
    };
}