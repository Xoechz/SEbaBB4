__doc__ = "Hello World!"

import matplotlib.pyplot as plt
import numpy as np


def hello_world():
    """
    Prints "Hello World!" to the console and plots a simple graph.
    """
    print("Hello World!")

    # Create a simple plot
    x = np.linspace(0, 10, 100)
    y = np.sin(x)

    plt.plot(x, y)
    plt.title("Hello World Plot")
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.grid()
    plt.show()


hello_world()
