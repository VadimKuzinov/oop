#include <string>
#include <tuple>

template<typename T, typename Head>
void setImplUnpacked(T& t, const std::string& name, const std::string& value, Head pair_head) {
    auto str = std::string(pair_head.second);
    if (str != name) {
        return;
    }

    std::istringstream(value) >> t.*pair_head.first;
}

template<typename T, typename Head, typename... Args>
std::enable_if<sizeof...(Args) != 0>::type setImplUnpacked(T& t, const std::string& name, const std::string& value, Head pair_head, Args... pairs) {
    auto str = std::string(pair_head.second);
    if (str != name) {
        setImplUnpacked(t, name, value, pairs...);
        return;
    }

    std::istringstream(value) >> t.*pair_head.first;
}

template <typename T, typename... Args, std::size_t... I>
void setImpl(T& t, const std::tuple<Args...>& tuple, const std::string& name, const std::string& value, std::index_sequence<I...>) {
    setImplUnpacked(t, name, value, std::get<I>(tuple)...);
}

