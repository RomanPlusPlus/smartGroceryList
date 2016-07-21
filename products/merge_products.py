#!/usr/bin/env python

import sys

def read_lines(f):
   result = []
   with open(f) as f:
      result = f.readlines()
   return result

products_data = read_lines('products.txt')
importance_lines = read_lines('importance.txt')

if len(products_data) != len(importance_lines):
   raise Exception('Lines count do not match')

with open('products_merged.txt', 'w') as f:
   for i in range(0, len(products_data)):
      name = products_data[i].strip()
      importance = int(importance_lines[i].strip())
      print>>f, '%s,%d' % (name, importance)
