import serial


def main():
    serialClient: serial.Serial = serial.Serial("COM4", 115200)

    while(True):
        i: int = int(input("Input a Number: "))
        print(i)
        serialClient.write(i)

    return 0


if __name__ == "__main__":
    main()
