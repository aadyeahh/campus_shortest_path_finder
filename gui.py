import os
from PIL import Image, ImageTk

import tkinter as tk
from tkinter import ttk, messagebox

import subprocess

# Locations on each floor
floors = {

    "Basement": [
        "Basement Workshop"
    ],

    "Ground Floor": [
        "Entrance", "Staircase 0a", "Staircase 0b",
        "Staircase 0c", "Staircase 0d", "Staircase 0e",
        "Saraswati Murti", "Annapurna 1", "Annapurna 2",
        "LRC", "Admin Block", "BE Lab 1", "Phy Lab 1",
        "CL 1", "CL 2", "VM 1", "Ride Block",
        "Washroom 0a", "Washroom 0b", "MPH",
        "Main Ground", "Football Ground"
    ],

    "First Floor": [
        "Washroom 1a", "Washroom 1b",
        "Staircase 1a", "Staircase 1b",
        "Staircase 1c", "Staircase 1d",
        "Staircase 1e", "Staircase 1f",
        "Staircase 1g", "Printout Shop", "Gym Room",
        "EDD Lab", "Block 1A Entrance 1",
        "Block 1A Entrance 2", "Block 1B Entrance 1",
        "Faculty Block 1A", "Faculty Block 1B",
        "Block 1C", "Cafe", "BE Lab 2",
        "111", "113", "116", "117",
        "118A", "118B", "121", "123", "127",
        "138", "148", "153",
        "CR 60", "CL 4", "VLSI Lab", "CIC Lab"
    ],

    "Second Floor": [
        "Washroom 2a", "Washroom 2b",
        "Staircase 2a", "Staircase 2b",
        "Staircase 2c", "Staircase 2d",
        "Staircase 2e", "Block 2A Entrance 1",
        "Block 2A Entrance 2", "Block 2B Entrance 1",
        "Block 2B Entrance 2", "Block 2C",
        "Faculty Block 2A", "Faculty Block 2A1",
        "Faculty Block 2B", "Faculty Block 2B1",
        "Faculty Block 2C", "VM 2",
        "Phy Lab 2", "217", "225", "226",
        "228", "229", "230", "234",
        "Mobile Technology Lab",
        "Analogue and Digital Electronics Lab",
        "Electromagnetic Lab",
        "Embedded System and IoT Lab",
        "Language Lab 1", "Language Lab 2",
        "241A", "241B", "244A", "244B",
        "254", "259", "263", "DSP Lab",
        "Communication System Lab"
    ],

    "Third Floor": [
        "Third Floor Entrance 1",
        "Third Floor Entrance 2",
        "Third Floor Entrance 3"
    ]
}


# Main window
root = tk.Tk()

root.title("College Shortest Path Finder")
root.geometry("550x600")
root.configure(bg="#f2f4f7")
root.resizable(False, False)


# Heading
heading = tk.Label(
    root,
    text="College Shortest Path Finder",
    font=("Arial", 20, "bold"),
    bg="#f2f4f7",
    fg="#202b45"
)

heading.pack(pady=25)


# Function to update location dropdown
def update_location(floor_box, location_box):

    floor = floor_box.get()

    location_box["values"] = floors[floor]

    location_box.set("")


# Current location section
tk.Label(
    root,
    text="CURRENT LOCATION",
    font=("Arial", 11, "bold"),
    bg="#f2f4f7"
).pack(pady=8)


current_floor = ttk.Combobox(
    root,
    values=list(floors.keys()),
    state="readonly",
    width=35
)

current_floor.pack(pady=5)
current_floor.set("Ground Floor")


current_location = ttk.Combobox(
    root,
    state="readonly",
    width=35
)

current_location.pack(pady=8)

current_location["values"] = floors["Ground Floor"]


current_floor.bind(
    "<<ComboboxSelected>>",
    lambda event: update_location(
        current_floor,
        current_location
    )
)


# Function to display floor plans
def show_floor_plans():

    window = tk.Toplevel(root)

    window.title("College Floor Plans")
    window.geometry("1000x750")
    window.configure(bg="#f2f4f7")

    heading = tk.Label(
        window,
        text="COLLEGE FLOOR PLANS",
        font=("Arial", 18, "bold"),
        bg="#f2f4f7",
        fg="#202b45"
    )

    heading.pack(pady=15)

    notebook = ttk.Notebook(window)

    notebook.pack(
        fill="both",
        expand=True,
        padx=15,
        pady=10
    )

    plans = {
        "Ground Floor": "ground.png",
        "First Floor": "first.png",
        "Second Floor": "second.png"
    }

    window.images = []

    for floor, filename in plans.items():

        frame = ttk.Frame(notebook)

        notebook.add(frame, text=floor)

        image_path = os.path.join(
            os.path.dirname(os.path.abspath(__file__)),
            "floor_plans",
            filename
        )

        try:

            img = Image.open(image_path)

            img.thumbnail((950, 620))

            photo = ImageTk.PhotoImage(img)

            label = tk.Label(frame, image=photo)

            label.pack(expand=True)

            window.images.append(photo)

        except Exception as e:

            tk.Label(
                frame,
                text="Could not load floor plan:\n" + str(e),
                font=("Arial", 12)
            ).pack(expand=True)


# Floor plans button
plan_button = tk.Button(
    root,
    text="VIEW COLLEGE FLOOR PLANS",
    font=("Arial", 10, "bold"),
    bg="#e1e7f0",
    fg="#273c75",
    command=show_floor_plans,
    padx=15,
    pady=8
)

plan_button.pack(pady=5)


# Destination section
tk.Label(
    root,
    text="DESTINATION",
    font=("Arial", 11, "bold"),
    bg="#f2f4f7"
).pack(pady=20)


destination_floor = ttk.Combobox(
    root,
    values=list(floors.keys()),
    state="readonly",
    width=35
)

destination_floor.pack(pady=5)
destination_floor.set("First Floor")


destination_location = ttk.Combobox(
    root,
    state="readonly",
    width=35
)

destination_location.pack(pady=8)

destination_location["values"] = floors["First Floor"]


destination_floor.bind(
    "<<ComboboxSelected>>",
    lambda event: update_location(
        destination_floor,
        destination_location
    )
)


# Function to find shortest path
def find_path():

    src = current_location.get()
    dest = destination_location.get()

    if src == "" or dest == "":

        messagebox.showwarning(
            "Missing Selection",
            "Please select both locations."
        )

        return

    try:

        executable = os.path.join(
            os.path.dirname(os.path.abspath(__file__)),
            "code.exe"
        )

        result = subprocess.run(
            [executable, src, dest],
            capture_output=True,
            text=True,
            check=True
        )

        result_label.config(
            text=result.stdout,
            fg="#202b45"
        )

    except Exception as e:

        messagebox.showerror(
            "Error",
            "Could not run the C++ program.\n" + str(e)
        )


# Find shortest path button
find_button = tk.Button(
    root,
    text="FIND SHORTEST PATH",
    font=("Arial", 12, "bold"),
    bg="#273c75",
    fg="white",
    activebackground="#192a56",
    activeforeground="white",
    command=find_path,
    padx=20,
    pady=10
)

find_button.pack(pady=25)


# Result section
tk.Label(
    root,
    text="SHORTEST PATH RESULT",
    font=("Arial", 11, "bold"),
    bg="#f2f4f7"
).pack(pady=5)


result_label = tk.Label(
    root,
    text="Your route will appear here.",
    font=("Arial", 11),
    bg="white",
    fg="#555555",
    wraplength=450,
    justify="left",
    padx=15,
    pady=15
)

result_label.pack(padx=25, fill="x")


root.mainloop()
