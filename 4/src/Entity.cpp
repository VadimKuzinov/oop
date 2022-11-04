#include "Entity.h"
#include "Utils.h"


std::istream& operator>>(std::istream& is, std::shared_ptr<Entity>& e) {
    std::string squad_name_type;
    is >> squad_name_type;
    e = createPtrToInstanceOf(getTypeInfoFromString(squad_name_type));
    std::size_t qty_of_fields;
    is >> qty_of_fields;
    std::string name, value;
    while (qty_of_fields--) {
        is >> name >> value;
        e->set(name, value);
    }

    std::cout << "CREATED ENTITY: " << std::endl;
    auto v = e->serialize();
    for (auto&& [name, value] : v) {
        std::cout << name << " " << value << std::endl;
    }

    return is;
}
