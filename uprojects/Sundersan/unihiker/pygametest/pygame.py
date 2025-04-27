'''Add snake and food to the game window'''
import pygame # Import the pygame library
import time # Import the time library
 
pygame.init() # Initialize the game
W = 240 # Define the width
H = 320 # Define the height
size = (240, 320) # Define the size
window = pygame.display.set_mode(size) # Create the game window with a size of (240, 320)
bg_color = (255, 255, 255) # Define the background color as white 
 
# Divide the game window into small squares, each with a width and height of 15, totaling 24 rows and 18 columns
ROW=24 # Define the number of rows, 24 rows and 18 columns for each square of size 15x15
COL=18 # Define the number of columns
cell_width=W/COL # Define the width of each cell
cell_height=H/ROW # Define the height of each cell
 
# Define the Point class to represent the position of a square
class Point:
    row = 0 # Row
    col = 0 # Column
    def __init__(self,row,col): # Row, Column
        self.row=row 
        self.col=col
 
#Define the positions and colors of the snake head, body, and food
head = Point(row=int(ROW/2), col=int(COL/2)) # Define the position of the snake head in the 12th row, 9th column
snakes = [
    Point(row=head.row, col=head.col+1), # Define the position of snake body 1 in the 12th row, 10th column
    Point(row=head.row, col=head.col+2), # Define the position of snake body 2 in the 12th row, 11th column
    Point(row=head.row, col=head.col+3) # Define the position of snake body 3 in the 12th row, 12th column
]
food = Point(row=2, col=3) # Define the position of the food in the 2nd row, 3rd column
head_color = (65, 105, 225) # Define the color of the snake head
snake_color = (204, 204, 204) # Define the color of the snake body
food_color = (255, 10, 10) # Define the color of the food
 
# Define the drawing of each small square (takes two parameters: position and color)
def rect(point, color):
    left = point.col * cell_width # Define the distance of the small square from the left edge
    top = point.row * cell_height # Define the distance of the small square from the top edge
    pygame.draw.rect(window, color, (left, top, cell_width, cell_height)) # Draw a rectangle on the window with the given color
    
 
run = True # Define the initial running state as True, indicating the game is running
while run: # Game loop
    window.fill(bg_color) # Fill the window with the background color
 
# Define the snake body, snake head, and food using small squares
    for snake in snakes:
        rect(snake, snake_color)  # Create the snake body with the specified color
        rect(head, head_color)  # Create the snake head with the specified color
        rect(food, food_color)  # Create the food with the specified color
 
    pygame.display.flip()  # Update all pending displays to the window
    time.sleep(0.2)  # Delay for 0.2 seconds