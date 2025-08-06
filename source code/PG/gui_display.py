# Plant Growth GUI with Camera, Sensor Display, and LED Control
import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import subprocess
import os
import time
import csv
from datetime import datetime, timedelta
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# --- Utility: Get CPU temperature ---
def get_cpu_temp():
    try:
        with open("/sys/class/thermal/thermal_zone0/temp", "r") as f:
            milli = int(f.read().strip())
            return milli / 1000.0
    except:
        return 0.0

# --- Main Window ---
root = tk.Tk()
root.title("Plant Growth GUI")
root.geometry("1000x800")

# --- Title Banner ---
tk.Label(root, text="PLANT GROWTH EXPERIMENT", font=('Helvetica', 20, 'bold')).pack(pady=10)

# --- Notebook Tabs ---
notebook = ttk.Notebook(root)
page1 = tk.Frame(notebook)
page2 = tk.Frame(notebook)
notebook.add(page1, text="Live Sensor View")
notebook.add(page2, text="24-Hour Telemetry")
notebook.pack(fill="both", expand=True)

# --- Top Left Control Buttons ---
top_control_frame = tk.Frame(page1)
top_control_frame.pack(anchor="nw", padx=20, pady=10)

tk.Button(top_control_frame, text="Start Program", command=lambda: print("Start"), width=15).pack(pady=2)
tk.Button(top_control_frame, text="Stop Program", command=lambda: print("Stop"), width=15).pack(pady=2)

# --- Center Layout for Page 1 ---
center_frame = tk.Frame(page1)
center_frame.pack(expand=True)

left_frame = tk.Frame(center_frame)
right_frame = tk.Frame(center_frame)
left_frame.pack(side="left", padx=40, pady=20)
right_frame.pack(side="right", padx=40, pady=20)

# --- Sensor Label Display ---
labels = [
    ("Time", tk.StringVar()),
    ("Radiation", tk.StringVar()),
    ("MS8607 Temp (degC)", tk.StringVar()),
    ("MS8607 Pressure (mbar)", tk.StringVar()),
    ("MS8607 Humidity (%)", tk.StringVar()),
    ("SCD41 CO2 (ppm)", tk.StringVar()),
    ("SCD41 Temp (degC)", tk.StringVar()),
    ("SCD41 Humidity (%)", tk.StringVar()),
    ("CPU Temp (degC)", tk.StringVar())
]

for i, (label_text, var) in enumerate(labels):
    tk.Label(left_frame, text=label_text, font=('Helvetica', 13, 'bold')).grid(row=i, column=0, sticky="w", padx=5, pady=3)
    tk.Label(left_frame, textvariable=var, font=('Helvetica', 13)).grid(row=i, column=1, sticky="w", padx=5, pady=3)

(ts_var, rad_var, ms_temp, ms_press, ms_hum, sc_co2, sc_temp, sc_hum, cpu_var) = [v for _, v in labels]

# --- Image Display Frame ---
image_box = tk.Frame(right_frame, width=320, height=240, bg="white", relief="solid", borderwidth=1)
image_box.pack(pady=10)
image_box.pack_propagate(False)
img_label = tk.Label(image_box)
img_label.pack()

# --- Capture Image Function ---
def capture_and_display():
    try:
        subprocess.run(["python3", "camera.py"], check=True)
        time.sleep(0.5)
        if os.path.exists("test.jpg"):
            img = Image.open("test.jpg").resize((320, 240))
            photo = ImageTk.PhotoImage(img)
            img_label.config(image=photo)
            img_label.image = photo
    except Exception as e:
        print(f"Error capturing image: {e}")

# --- Buttons for Camera and LEDs ---
button_frame = tk.Frame(right_frame)
button_frame.pack()

tk.Button(button_frame, text="Capture Image", command=capture_and_display, width=20).pack(pady=2)
tk.Button(button_frame, text="Activate UV LED", width=20).pack(pady=2)
tk.Button(button_frame, text="Stop UV LED", width=20).pack(pady=2)
tk.Button(button_frame, text="Activate White LED", width=20).pack(pady=2)
tk.Button(button_frame, text="Stop White LED", width=20).pack(pady=2)

# --- Sensor Update Loop ---
def read_sensor_data():
    try:
        with open("/tmp/sensor_data.txt", "r") as f:
            line = f.readline()
            parts = line.strip().split(',')
            if len(parts) == 8:
                ts_var.set(parts[0])
                rad_var.set(f"{int(parts[1])} counts/min")
                ms_temp.set(f"{float(parts[2]):.2f}")
                ms_press.set(f"{float(parts[3]):.2f}")
                ms_hum.set(f"{float(parts[4]):.2f}")
                sc_co2.set(f"{int(parts[5])}")
                sc_temp.set(f"{float(parts[6]):.2f}")
                sc_hum.set(f"{float(parts[7]):.2f}")
                cpu_var.set(f"{get_cpu_temp():.1f}")
    except:
        pass
    root.after(1000, read_sensor_data)

read_sensor_data()

# --- Page 2: Scrollable Historical Graphs ---
scroll_canvas = tk.Canvas(page2)
scrollbar = tk.Scrollbar(page2, orient="vertical", command=scroll_canvas.yview)
scroll_frame = tk.Frame(scroll_canvas)

scroll_frame.bind("<Configure>", lambda e: scroll_canvas.configure(scrollregion=scroll_canvas.bbox("all")))
scroll_window = scroll_canvas.create_window((0, 0), window=scroll_frame, anchor="n")
scroll_canvas.configure(yscrollcommand=scrollbar.set)
scroll_canvas.pack(side="left", fill="both", expand=True)
scrollbar.pack(side="right", fill="y")

# --- Mouse Wheel Scroll Bindings ---
def _on_mousewheel(event):
    scroll_canvas.yview_scroll(int(-1 * (event.delta / 120)), "units")
scroll_canvas.bind_all("<MouseWheel>", _on_mousewheel)
scroll_canvas.bind_all("<Button-4>", lambda e: scroll_canvas.yview_scroll(-1, "units"))
scroll_canvas.bind_all("<Button-5>", lambda e: scroll_canvas.yview_scroll(1, "units"))

# --- Sensor Plot Setup ---
sensor_labels = [
    ("Radiation (counts/min)", 1),
    ("MS8607 Temperature (degC)", 2),
    ("MS8607 Pressure (mbar)", 3),
    ("MS8607 Humidity (%)", 4),
    ("SCD41 CO2 (ppm)", 5),
    ("SCD41 Temperature (degC)", 6),
    ("SCD41 Humidity (%)", 7),
]

figs, canvases = [], []
for label, _ in sensor_labels:
    fig, ax = plt.subplots(figsize=(8, 2.5))
    canvas = FigureCanvasTkAgg(fig, master=scroll_frame)
    widget = canvas.get_tk_widget()
    widget.pack(pady=10)
    widget.pack_configure(anchor="center")
    figs.append((fig, ax))
    canvases.append(canvas)

# --- Plot Update Function ---
def update_all_plots():
    try:
        times = []
        data_cols = [[] for _ in range(8)]
        with open("sensor_data.csv", "r") as f:
            reader = csv.reader(f)
            for row in reader:
                if len(row) != 8:
                    continue
                t = datetime.strptime(row[0], "%Y-%m-%d %H:%M:%S")
                if t >= datetime.now() - timedelta(hours=24):
                    times.append(t)
                    for i in range(1, 8):
                        data_cols[i].append(float(row[i]) if i != 5 else int(row[i]))
        for i, (label, col_index) in enumerate(sensor_labels):
            fig, ax = figs[i]
            ax.clear()
            ax.plot(times, data_cols[col_index], label=label)
            ax.set_ylabel(label)
            ax.grid(True)
            ax.legend()
            fig.autofmt_xdate()
            canvases[i].draw()
    except Exception as e:
        print(f"Plot error: {e}")

# --- Start Plot Update Timer ---
def periodic_plot_update():
    update_all_plots()
    root.after(60000, periodic_plot_update)

periodic_plot_update()
root.mainloop()


