import time
import threading
from pynput.mouse import Controller, Button
from pynput.keyboard import Controller as KeyController, Listener, KeyCode

TOGGLE_KEY = KeyCode(char='t')   # Key to toggle the auto-clicker/presser
PRESS_KEY = 'a'                  # Keyboard key you want to auto-press
DELAY = 0.002                    # Delay between actions

clicking = False
mouse = Controller()
keyboard = KeyController()

# #                   --- AUTO KEY PRESSER ---
# def key_presser():
#     while True:
#         if clicking:
#             keyboard.press(PRESS_KEY)
#             keyboard.release(PRESS_KEY)
#         time.sleep(DELAY)

# press_thread = threading.Thread(target=key_presser, daemon=True)
# press_thread.start()
# #                   --- AUTO KEY PRESSER ---

#                     --- AUTO MOUSE CLICKER ---
def clicker():
    while True:
        if clicking:
            mouse.click(Button.left)
        time.sleep(DELAY)

click_thread = threading.Thread(target=clicker, daemon=True)
click_thread.start()
#                     --- AUTO MOUSE CLICKER ---


# --- TOGGLE HANDLER ---
def toggle_event(key):
    global clicking
    if key == TOGGLE_KEY:
        clicking = not clicking
        print(f"[{'ON' if clicking else 'OFF'}] Auto action running...")
    elif key == KeyCode(char='q'):  # optional quick exit
        print("Quitting...")
        raise SystemExit

# --- LISTEN FOR HOTKEYS ---
print("Press 'T' to toggle ON/OFF.  Press 'Q' to quit.")
with Listener(on_press=toggle_event) as listener:
    listener.join()

