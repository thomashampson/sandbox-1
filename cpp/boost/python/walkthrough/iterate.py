#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'builds/debug/bin'))
import core

c = core.container()
for i in c:
  print i.index
