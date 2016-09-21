#include "sgl/product.hh"

#include <stdexcept>
#include <string>
#include <algorithm>

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
 * Initialize a product from a "name,priority" line.
 * @param A line representing both name and product priority.
 */
product::product(std::string line) {
   auto comma = std::find(line.rbegin(), line.rend(), ',');
   if (comma == line.rend()) {
      throw std::runtime_error("Invalid product line format: " + line);
   }
   auto first_after_comma = comma.base();

   name_ = std::string(line.begin(), first_after_comma - 1);
   priority_ = std::stoi(std::string(first_after_comma, line.end()));
}

/**
 * Initializes a product with a given values
 *
 * @param name       Product name
 * @param priority   Product priority
 */
product::product(std::string name, priority_t priority)
   : name_(name)
   , priority_(priority) {
   // Nothing to do here
}

/**
 * Check products for similarity.
 * Products are similar in case if either their names
 * or types are euqal.
 *
 * @param lhs  First product
 * @param rhs  Second product
 *
 * @return True in case if products are similar.
 */
bool sgl::is_similar_to(const product &lhs, const product &rhs) {
   // This lambda function looks for the '(' character
   // and extracts all the characters before it assuming
   // it is the product's basic name.
   // Return an empty string in case if no parenthese found.
   auto extract_basic_name = [](std::string name) {
      std::string result;

      auto parenthese_position = std::find(name.begin(), name.end(), '(');
      if (parenthese_position != name.end()) {
         result = std::string(name.begin(), parenthese_position);
      }

      return result;
   };

   // This lambda function looks for both '(' and ')' characters
   // and extracts all the characters in between assuming
   // it is the product's type.
   // Returns an empty string in case if no type is found.
   auto extract_product_type = [](std::string name) {
      std::string result;

      auto open_parenthese_position = std::find(name.rbegin(), name.rend(), '(');

      auto close_parenthese_position = std::find(name.rbegin(), name.rend(), ')');
      if (close_parenthese_position != name.rend()) {
         std::advance(close_parenthese_position, 1);
      }

      // Both parentheses found and appear in the expected order:
      // e.g. "(FooBar)"
      if (open_parenthese_position != name.rend() &&
          close_parenthese_position != name.rend() &&
          std::distance(close_parenthese_position, open_parenthese_position) >
              0) {
         result = std::string(open_parenthese_position.base(), close_parenthese_position.base());
      }
      return result;
   };

   bool are_names_identical(extract_basic_name(lhs.name()) ==
                            extract_basic_name(rhs.name()));

   bool are_types_identical(extract_product_type(lhs.name()) ==
                            extract_product_type(rhs.name()));

   bool result(are_names_identical || are_types_identical);
   return result;
}

/**
 * Check two products for literal equality.
 *
 * @param lhs  First product
 * @param rhs  Second product
 *
 * @return True in case if products are equal
 */
bool operator==(const product &lhs, const product &rhs) {
   return (lhs.name() == rhs.name()) && (lhs.priority() == rhs.priority());
}
