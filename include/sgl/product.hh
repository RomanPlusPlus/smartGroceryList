/**
 * @file   product.cc
 * @author Dennis Sitelew
 * @date   Jul 21, 2016
 */

#ifndef SRC_LIB_PRODUCT_CC
#define SRC_LIB_PRODUCT_CC

#include <string>
#include <cstdint>
#include <ostream>

namespace sgl {

/**
 * Holds a product information
 */
class product {
public:
   product();
   product(std::string name, std::uint16_t priority);

public:
   std::string name() const { return name_; }
   std::uint16_t priority() const { return priority_; }

   bool is_similar_to(const product &other) const;

   friend std::ostream &operator<<(std::ostream &os, const product &p);
   friend std::istream &operator>>(std::istream &os, product &p);

   friend bool operator==(const product &lhs, const product &rhs);

private:
   //! The product name
   std::string name_;

   //! The product priority
   std::uint16_t priority_;
};

} // namespace sgl

#endif // SRC_LIB_PRODUCT_CC
