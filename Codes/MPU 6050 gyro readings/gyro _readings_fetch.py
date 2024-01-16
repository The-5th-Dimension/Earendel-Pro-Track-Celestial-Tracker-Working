import pygame
import serial

# Initialize Pygame
pygame.init()

# Pygame window dimensions
window_width = 800
window_height = 600

# Colors
white = (0, 255, 0)
black = (0, 0, 0)
red = (255, 0, 0)

# Font setup
font = pygame.font.Font(None, 36)

# Set up the Pygame window
screen = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption("Real-time Visualization")

# COM port and baud rate
com_port = 'COM12'
baud_rate = 115200

try:
    ser = serial.Serial(com_port, baud_rate)
    print(f"Reading from {com_port}. Press Ctrl+C to stop.")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        # Read data from the serial port
        raw_data = ser.readline()

        try:
            # Decode the data using utf-8 encoding with error handling
            decoded_data = raw_data.decode('utf-8', errors='replace').strip()
            # print(f"Received data: {decoded_data}")

            # Extract values of Rotation X and Rotation Y
            if "Rotation X" in decoded_data and "Y" in decoded_data:
                # Split the string to extract the numerical values
                values = decoded_data.split(",")

                # Extract Rotation X and Rotation Y values
                rotation_y = float(values[0].split(":")[1].strip())
                rotation_x = float(values[1].split(":")[1].strip())

                print(f"Rotation X: {rotation_x}, Rotation Y: {rotation_y}")

                # Clear the screen
                screen.fill(black)

                # Map the values to screen coordinates
                mapped_x = int((rotation_x + 90) / 180 * window_width)
                mapped_y = int((rotation_y + 90) / 180 * window_height)

                # Draw a circle representing rotation_x and rotation_y on the screen
                pygame.draw.circle(screen, white, (mapped_x, mapped_y), 10)

                # Render text to display the numeric values
                text_x = font.render(f"Rotation X: {rotation_x:.2f}", True, white)
                text_y = font.render(f"Rotation Y: {rotation_y:.2f}", True, white)

                # Blit the text onto the screen
                screen.blit(text_x, (20, 20))
                screen.blit(text_y, (20, 60))

                # Update the display
                pygame.display.update()

        except UnicodeDecodeError as e:
            print(f"Unicode Decode Error: {e}")

except serial.SerialException as e:
    print(f"Serial exception occurred: {e}")

except KeyboardInterrupt:
    print("Keyboard Interrupt: Stopping reading from the serial port.")

finally:
    if ser.is_open:
        ser.close()
