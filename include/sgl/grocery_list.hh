/**
 * @file   grocery_list.hh
 * @author Dennis Sitelew
 * @date   Jul 21, 2016
 */

#ifndef INCLUDE_SGL_GROCERY_LIST_HH
#define INCLUDE_SGL_GROCERY_LIST_HH

#include <sgl/product.hh>

#include <string>
#include <vector>

namespace sgl {

/**
 * Contains a list of all products and
 * generates a list of weighted products for today.
 */
class grocery_list {
public:
   using product_list_t = std::vector<product>;

public:
   void load(std::string path);

   product_list_t generate(unsigned number);

private:
   //! Full list of products
   product_list_t products_;
};

} // namespace sgl

#endif // INCLUDE_SGL_GROCERY_LIST_HH
