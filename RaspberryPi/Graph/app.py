# Library imports

import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Code imports

from plot import run_plot

def run_app() :

  # Initialize tkinter

  root = tk.Tk()
  root.configure(bg="#9ACD32")

  # Set embed plot and game

  embed_plot = tk.Frame(root)
  embed_plot.pack(side=tk.LEFT)

  # Get the plot from the plot module

  ani = run_plot()

  # Create canvas

  canvas = FigureCanvasTkAgg(ani._fig, master=embed_plot)  
  canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH)
  
  canvas.draw()
  root.mainloop()

if __name__ == "__main__" :
  run_app()