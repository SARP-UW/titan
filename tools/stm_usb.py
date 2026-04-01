import sys
import usb.core
found = False
for dev in usb.core.find(find_all=True):  # type: ignore
    if dev.manufacturer == "STMicroelectronics":  # pyright: ignore[reportAttributeAccessIssue]
        try:
            dev.reset()  # type: ignore
            print("STM found and reset")
            sys.exit(0)  # success
        except Exception as e:
            print("STM found, USB reset failed:", e)
            sys.exit(1)  # reset failed
print("STM not found")
sys.exit(2)  # device not found