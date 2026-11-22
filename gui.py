import tkinter as tk
from tkinter import ttk, messagebox
import subprocess

# Locations on each floor
floors = {
    "Basement": ["Basement Workshop"],

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
        "Staircase 1a", "Staircase 1b", "Staircase 1c",
        "Staircase 1d", "Staircase 1e", "Staircase 1f",
        "Staircase 1g", "Printout Shop", "Gym Room",
        "EDD Lab", "Block 1A Entrance 1",
        "Block 1A Entrance 2", "Block 1B Entrance 1",
        "Faculty Block 1B", "Block 1C", "Cafe", "BE Lab 2"
    ],

    "Second Floor": [
        "Washroom 2a", "Washroom 2b",
        "Staircase 2a", "Staircase 2b", "Staircase 2c",
        "Staircase 2d", "Staircase 2e",
        "Block 2A Entrance 1", "Block 2A Entrance 2",
        "VM 2", "Faculty Block 2A", "Faculty Block 2B",
        "Faculty Block 2C", "Block 2B Entrance 1",
        "Block 2B Entrance 2", "Block 2C", "Phy Lab 2"
    ],

    "Third Floor": ["Third Floor"]
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
    root, text="CURRENT LOCATION",
    font=("Arial", 11, "bold"),
    bg="#f2f4f7"
).pack(pady=8)

current_floor = ttk.Combobox(
    root, values=list(floors.keys()),
    state="readonly", width=35
)
current_floor.pack(pady=5)
current_floor.set("Ground Floor")

current_location = ttk.Combobox(
    root, state="readonly", width=35
)
current_location.pack(pady=8)

current_location["values"] = floors["Ground Floor"]


current_floor.bind(
    "<<ComboboxSelected>>",
    lambda event: update_location(current_floor, current_location)
)


# Destination section
tk.Label(
    root, text="DESTINATION",
    font=("Arial", 11, "bold"),
    bg="#f2f4f7"
).pack(pady=20)

destination_floor = ttk.Combobox(
    root, values=list(floors.keys()),
    state="readonly", width=35
)
destination_floor.pack(pady=5)
destination_floor.set("First Floor")

destination_location = ttk.Combobox(
    root, state="readonly", width=35
)
destination_location.pack(pady=8)

destination_location["values"] = floors["First Floor"]


destination_floor.bind(
    "<<ComboboxSelected>>",
    lambda event: update_location(destination_floor, destination_location)
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
        result = subprocess.run(
            ["code.exe", src, dest],
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


# Button
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
