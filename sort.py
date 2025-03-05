import tkinter as tk
import subprocess
import time

# Function to read an array from the file
def read_array_from_file(filename):
    with open(filename, 'r') as file:
        return list(map(int, file.readline().split()))

# Function to read timing information from the file
def read_timing_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    return lines

# Function to update the canvas with the array
def update_canvas(canvas, array):
    canvas.delete("all")  # Clear previous drawings
    bar_width = 800 // len(array)  # Width of each bar
    for i, value in enumerate(array):
        x0, y0 = i * bar_width, 400 - value * 10  # Y-coordinate for the height
        x1, y1 = (i + 1) * bar_width, 400
        # Draw each bar (rectangle)
        canvas.create_rectangle(x0, y0, x1, y1, fill="yellow", outline="black")
        # Draw the number inside the block
        text_x = (x0 + x1) / 2  # X position of text (center of the block)
        text_y = (y0 + y1) / 2  # Y position of text (center of the block)
        canvas.create_text(text_x, text_y, text=str(value), fill="black", font=('Helvetica', 10, 'bold'))  # Add text to the block
    canvas.update()  # Update the canvas to reflect changes
    time.sleep(0.5)  # Delay to create animation effect

# Function to run the C program and visualize sorting step by step
def visualize_sorting():
    subprocess.run(["./a.out"])  # Run the compiled C program

    # Read the steps and visualize each step
    with open("step_output.txt", "r") as file:
        for line in file:
            array = list(map(int, line.split()))  # Convert string of numbers to an array
            update_canvas(canvas, array)  # Update the canvas with the array state

    # Finally, read and show the sorted array
    sorted_array = read_array_from_file("sorted_output.txt")
    update_canvas(canvas, sorted_array)  # Show the final sorted array

    # Read timing information
    timing_lines = read_timing_from_file("timing_output.txt")
    timing_label.config(text='\n'.join(timing_lines))  # Update the label with the timing info

# Create the main window
root = tk.Tk()
root.title("Sorting Visualization")

# Create canvas for drawing the bars
canvas = tk.Canvas(root, width=800, height=400, bg='black')
canvas.pack()

# Add button to start sorting
btn_sort = tk.Button(root, text="Start Sorting", command=visualize_sorting)
btn_sort.pack()

# Add label to display the timing information
timing_label = tk.Label(root, text="Sorting times will appear here.", fg="white", bg="black")
timing_label.pack()

# Start the Tkinter event loop
root.mainloop()
