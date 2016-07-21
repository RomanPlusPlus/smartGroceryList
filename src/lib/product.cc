#include "sgl/product.hh"

#include <algorithm>

// TODO REMOVE
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
/// Class: product
////////////////////////////////////////////////////////////////////////////////

using sgl::product;

/**
 * Default constructor - initializes an invalid product
 */
product::product()
   : name_()
   , priority_(0) {
   // Nothing to do here
}

/**
 * Initializes a product with a given values
 *
 * @param name       Product name
 * @param priority   Product priority
 */
product::product(std::string name, std::uint16_t priority)
   : name_(name)
   , priority_(priority) {
   // Nothing to do here
}

bool product::is_similar_to(const product &other) const {
   // This lambda function looks for the '(' character
   // and extracts all the characters before it assuming
   // it is the product's basic name.
   // @return An empty string in case if no parenthese found.
   auto extract_basic_name = [](std::string name) {
      std::string result;

      auto parenthese_position = std::find(name.begin(), name.end(), '(');
      if (parenthese_position != name.end()) {
         result = std::string(name.begin(), parenthese_position);
      }

      return result;
   };

   auto extract_product_type = [](std::string name) {
      std::string result;

      auto open_parenthese_position = std::find(name.begin(), name.end(), '(');
      auto close_parenthese_position = std::find(name.begin(), name.end(), ')');

      // Both parentheses found and appear in the expected order:
      // e.g. "(FooBar)"
      if (open_parenthese_position != name.end() &&
          close_parenthese_position != name.end() &&
          std::distance(open_parenthese_position, close_parenthese_position) >
              0) {
         result = std::string(open_parenthese_position, close_parenthese_position);
      }

      std::cout << name << "'s type is: " << result << std::endl;

      return result;
   };

   bool are_names_identical(extract_basic_name(name()) ==
                            extract_basic_name(other.name()));

   bool are_types_identical(extract_product_type(name()) ==
                            extract_product_type(other.name()));

   bool result(are_names_identical || are_types_identical);
   return result;
}


//std::ostream &operator<<(std::ostream &os, const product &p);
//std::istream &operator>>(std::istream &os, product &p);

bool operator==(const product &lhs, const product &rhs) {
   return (lhs.name() == rhs.name()) && (lhs.priority() == rhs.priority());
}
