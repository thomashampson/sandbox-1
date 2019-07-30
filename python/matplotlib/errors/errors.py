#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt

# example data
x = np.arange(0.1, 4, 0.5)
y = np.exp(-x)
# example variable error bar values
yerr = 0.1 + 0.2*np.sqrt(x)

# Now switch to a more OO interface to exercise more features.
fig, ax = plt.subplots(nrows=1, ncols=1)
#err_container = ax.errorbar(x, y, yerr=yerr, label='hello')
ax.plot(x, y, label='hello')
ax.set_title('Vert. symmetric')
ax.legend()

ax.clear()
#err_container[1][0].set_visible(False)
#err_container[1][1].set_visible(False)
#err_container[2][0].set_visible(False)

plt.show()
