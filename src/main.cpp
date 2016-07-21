#include <iostream>

#include <sgl/grocery_list.hh>

int main() {
   try {
      sgl::grocery_list list;
      list.load("products.txt");
      auto picked_list = list.generate(2);

      std::cout << "SPECIAL PRODUCTS FOR TODAY:" << std::endl;
      for (auto &product : picked_list) {
         std::cout << "[" << product.priority() << "]\t" << product.name()
                   << std::endl;
      }

   } catch (const std::exception &e) {
      std::cerr << "ERROR: " << e.what() << std::endl;
      return -1;
   } catch (...) {
      std::cerr << "ERROR: unknown error occur" << std::endl;
      return -2;
   }
   return 0;
}
