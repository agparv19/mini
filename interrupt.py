"""
A script that can't be killed with Ctrl + C !
"""
import signal
import time

def fancy_handler(signal, frame):
    print("\nPlease don't kill me\n")

# Set the custom handler for SIGINT
signal.signal(signal.SIGINT, fancy_handler)

def main():
    print("Running now...")
    while True:
        print("still running...")
        time.sleep(1)

if __name__ == "__main__":
    main()
