import matplotlib.pyplot as plt
from matplotlib.offsetbox import OffsetImage, AnnotationBbox
from PIL import Image
import os
import time

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
input_file = os.path.join(BASE_DIR, "input_coordinate.txt")

# Lift X positions
LIFT_X = [0, 3, 6, 9]

# Floor mapping
floor_names = {
    -2: "B2", -1: "B1", 0: "G",
    1: "F1", 2: "F2", 3: "F3", 4: "F4",
    5: "F5", 6: "F6", 7: "F7", 8: "F8"
}

METERS_PER_FLOOR = 4

# --------------------------------
# Figure
# --------------------------------

fig, ax = plt.subplots(figsize=(7, 10))

ax.set_xlim(-2, 14)
ax.set_ylim(-10, 34)

# Floor lines
for floor in range(-2, 9):
    y = floor * METERS_PER_FLOOR
    ax.axhline(y, linewidth=1, alpha=0.3)

# --------------------------------
# Load images
# --------------------------------

open_image_path = os.path.join(
    BASE_DIR, "Images", "lift_open.png"
)

close_image_path = os.path.join(
    BASE_DIR, "Images", "lift_close.png"
)

lift_open = Image.open(open_image_path)
lift_close = Image.open(close_image_path)

# --------------------------------
# Create elevators
# --------------------------------

elevators = []

for i in range(4):

    image = OffsetImage(
        lift_close,
        zoom=0.06
    )

    annotation = AnnotationBbox(
        image,
        (LIFT_X[i], 0),
        frameon=False,
        xycoords="data"
    )

    ax.add_artist(annotation)
    elevators.append(annotation)

# --------------------------------
# Axis settings
# --------------------------------

ax.set_yticks(range(-8, 33, 1))

ax.set_yticklabels([
    floor_names[y // 4] if y % 4 == 0 else ""
    for y in range(-8, 33)
])

ax.set_xticks(LIFT_X)
ax.set_xticklabels(["L1", "L2", "L3", "L4"])

ax.set_title("Elevator Simulation", fontsize=10)

plt.tight_layout()

# Interactive mode
plt.ion()
plt.show()

# --------------------------------
# Continuously read C++ file
# --------------------------------

t = 0

while t < 100:

    t += 1

    try:
        with open(input_file, "r") as file:
            data = file.read().split()

        print(data)

        if len(data) >= 8:

            for i in range(4):

                pos = float(data[i * 2])
                state = int(data[i * 2 + 1])

                print("L", i + 1, ":", pos, state)

                # Select image according to state
                if state == 1:
                    current_image = lift_open
                else:
                    current_image = lift_close

                # Remove old elevator
                elevators[i].remove()

                # Create elevator at new position
                image = OffsetImage(
                    current_image,
                    zoom=0.06
                )

                annotation = AnnotationBbox(
                    image,
                    (LIFT_X[i], pos),
                    frameon=False,
                    xycoords="data"
                )

                ax.add_artist(annotation)

                # Store new elevator
                elevators[i] = annotation

        # Redraw
        fig.canvas.draw()
        fig.canvas.flush_events()

    except (FileNotFoundError, ValueError, IndexError):
        pass

    time.sleep(0.25)

plt.ioff()
plt.show()


