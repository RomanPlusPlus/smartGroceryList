#include "sgl/grocery_list.hh"

#include <fstream>
#include <stdexcept>
#include <string>
#include <map>
#include <numeric>
#include <random>
#include <algorithm>

using sgl::grocery_list;

/**
 * Load the products list from a file
 *
 * @param path Path to the file
 */
void grocery_list::load(std::string path) {
   // Load list
   std::ifstream file(path);
   if (!file.is_open()) {
      throw std::invalid_argument("File cannot be open: " + path);
   }

   std::string line;
   while (std::getline(file, line)) {
      products_.emplace_back(line);
   }
}

/**
 * Generate the given number of products.
 *
 * @param number Number of products to generate.
 *
 * @return List of products
 */
grocery_list::product_list_t grocery_list::generate(unsigned number) {
   // Divide into priorities
   std::map<product::priority_t, product_list_t> prioities;
   for (auto &product : products_) {
      prioities[product.priority()].push_back(product);
   }

   // Calculate a sum of all unique priorities
   // and prepare a weighted priorities map:
   // A map where key is an end of the probability range
   // and value is a list of all items with the same probability.
   std::uint32_t sum(0);
   using weighted_map_t = std::map<uint32_t, product_list_t *>;
   weighted_map_t weighted_priorities;
   for (auto &kv : prioities) {
      sum += kv.first;
      weighted_priorities[sum] = &kv.second;
   }

   std::random_device random;
   std::default_random_engine engine(random());
   std::uniform_int_distribution<std::uint32_t> weights_distribution(0, sum - 1);

   // Prepare the result list
   product_list_t result;
   while (result.size() != number) {
      // Find an approprate products range based on the weight
      std::uint32_t number(weights_distribution(engine));
      auto product_range_it =
          std::find_if(weighted_priorities.begin(), weighted_priorities.end(),
                       [number](const weighted_map_t::value_type &pair) {
                          return number < pair.first;
                       });
      if (product_range_it == weighted_priorities.end()) {
         throw std::range_error("Invalid product weight: " +
                                std::to_string(number));
      }

      // Get a random product within this range
      auto &product_range = *product_range_it->second;
      std::uniform_int_distribution<std::size_t> products_distribution(0, product_range.size() - 1);

      auto picked_product(product_range.at(products_distribution(engine)));

      // Check for similarities with the already picked products
      auto same_product_it =
          std::find_if(result.begin(), result.end(),
                       [&picked_product](const product &other) {
                          return is_similar_to(other, picked_product);
                       });

      // Already have the same product. Sckip it
      if (same_product_it != result.end()) {
         continue;
      }

      result.push_back(picked_product);
   }
   return result;
}
