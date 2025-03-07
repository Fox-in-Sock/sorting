import tkinter as tk
import subprocess
import time
import os

def read_array_from_file(filename):
    if not os.path.exists(filename):
        return []
    with open(filename, 'r') as file:
        return list(map(int, file.readline().split()))

def update_canvas(canvas, array):
    canvas.delete("all")
    bar_width = 250 // max(len(array), 1)
    
    for i, value in enumerate(array):
        x0, y0 = i * bar_width, 280 - value * 10
        x1, y1 = (i + 1) * bar_width, 280
        canvas.create_rectangle(x0, y0, x1, y1, fill="yellow", outline="black")
        canvas.create_text((x0 + x1) / 2, y0 + 15, text=str(value), fill="black", font=('Arial', 8, 'bold'))
    
    canvas.update()  # Ensure immediate redraw

def visualize_sorting(sort_type):
    canvas = None  # Define before assignment to avoid reference issues

    if sort_type == "quick":
        subprocess.run(["./sofin", "quick"])  # Modify C program to accept sort type as an argument
        filename = "quic.txt"
        canvas = canvas_qs
    elif sort_type == "merge":
        subprocess.run(["./sofin", "merge"])
        filename = "merg.txt"
        canvas = canvas_ms
    elif sort_type == "heap":
        subprocess.run(["./sofin", "heap"])
        filename = "hea.txt"
        canvas = canvas_hs

    # Read sorted array from file
    sorted_array = read_array_from_file(filename)
    
    if sorted_array:
        update_canvas(canvas, sorted_array)
        timing_label.config(text=f"{sort_type.capitalize()} Sort Completed!")
    else:
        timing_label.config(text=f"Error: No data found for {sort_type} sort!")

root = tk.Tk()
root.title("Sorting Algorithm Visualization")

frame = tk.Frame(root)
frame.pack()

canvas_qs = tk.Canvas(frame, width=250, height=300, bg='white')
canvas_qs.grid(row=0, column=0)
canvas_qs.create_text(125, 20, text="Quick Sort", font=('Arial', 14, 'bold'))

canvas_ms = tk.Canvas(frame, width=250, height=300, bg='white')
canvas_ms.grid(row=0, column=1)
canvas_ms.create_text(125, 20, text="Merge Sort", font=('Arial', 14, 'bold'))

canvas_hs = tk.Canvas(frame, width=250, height=300, bg='white')
canvas_hs.grid(row=0, column=2)
canvas_hs.create_text(125, 20, text="Heap Sort", font=('Arial', 14, 'bold'))

btn_sort_qs = tk.Button(root, text="Start Quick Sort", command=lambda: visualize_sorting("quick"))
btn_sort_qs.pack()

btn_sort_ms = tk.Button(root, text="Start Merge Sort", command=lambda: visualize_sorting("merge"))
btn_sort_ms.pack()

btn_sort_hs = tk.Button(root, text="Start Heap Sort", command=lambda: visualize_sorting("heap"))
btn_sort_hs.pack()

timing_label = tk.Label(root, text="Sorting times will appear here.", fg="black")
timing_label.pack()

root.mainloop()
