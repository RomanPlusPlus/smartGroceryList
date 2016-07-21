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
   using priority_t = std::uint16_t;
public:
   product();
   product(std::string line);
   product(std::string name, priority_t priority);

public:
   std::string name() const { return name_; }
   priority_t priority() const { return priority_; }

   friend bool operator==(const product &lhs, const product &rhs);

private:
   //! The product name
   std::string name_;

   //! The product priority
   priority_t priority_;
};

bool is_similar_to(const product &lhs, const product &rhs);

} // namespace sgl

#endif // SRC_LIB_PRODUCT_CC
