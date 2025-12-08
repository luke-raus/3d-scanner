import serial


# Need to figure out port! Easiest way for now is via Arduino IDE.
# Just make sure you don't let the Arduino IDE connect & hog the connection...
# And make sure the baudrate matches what the Arduino code sets.

port = ''
baudrate = 9600

if port == '':
    print('!!! SET THE PORT !!!')

ser = serial.Serial(port, baudrate, timeout=None)


# Let's assume we get data from the Arduino that loops like ##,%%%\n
# where the ## is the number of steps turned and the %%% is distance measured

steps = []
dists = []

# Read lines until we receive the word 'start'
while True:
    data_str = ser.readline().decode()
    if 'start' in data_str:
        break

while True:                           # If we only wanted to read 50 lines, instead do: for i in range(50):
    data_bytes = ser.readline()       # Read from serial until newline character (\n)
    data_str = data_bytes.decode()    # Convert from 'bytes' object to a string
    data_str = data_str.strip()       # Strip off whitespace (e.g. newlines)

    # If this line contains 'done', exit the loop
    if 'done' in data_str:
        break

    # Otherwise (if we haven't received 'done'), we assume this line has numbers
    # This line of code on the string '25,6.7' will give the list of strings ['25', '6.7']
    numbers = data_str.split(',')

    # Convert this list of strings into actual numbers, so we can do math on them
    # TODO: Use a try/except statement to handle errors if we don't receive exactly what we expected
    step = int(   numbers[0] )
    dist = float( numbers[1] )

    print(step, dist)

    # Append this new data to our lists
    steps.append( step )
    dists.append( dist )

print('Full data received:')
print('Steps: ', steps)
print('Dists: ', dists)