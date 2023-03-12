import turtle
import random
import math
import webbrowser, os.path

class Point: #used to compare guessed points with points generated on the plane
    def __init__(self,x,y):
        self.x = x
        self.y = y

    def __str__(self):
        return "("+str(round(self.x,4))+","+str(round(self.y,4))+")" 

    def distanceBetween(self,other):
        self.distance = math.sqrt((self.x-other.x)**2+(self.y-other.y)**2)
        return round(self.distance,4)

class Player: #keeps track of specific attributes to the logged-in player
    def __init__(self,name,tokens,shape,trail,prizes):
        self.username = name
        self.tokens = tokens #currency used for betting
        self.shape = shape #shape of the turtle
        self.trail = trail #trail color (or pen color) of the turtle
        self.memory = []  #keeps track of what happened in a session
        self.prizes = prizes #keeps track of prizes won on the account


    def __str__(self):
        return f"You are {self.username}. You have {self.tokens} to your name."

    def getName(self):
        return self.username

    def getShape(self): 
        return self.shape

    def changeShape(self,newShape):
        self.shape = newShape
        
    def getTrail(self):
        return self.trail

    def changeTrail(self,newTrail):
        self.trail = newTrail
        
    def getTokens(self):
        return int(self.tokens)

    def useTokens(self,amount):
        self.tokens = self.tokens - amount

    def getPrizes(self):
        return self.prizes

    def recordNewTotal(self,guess,outcome,change): #used to change tokens and add to memory based on outcome of the game
        self.tokens += change
        self.memory.append([guess,outcome,change,self.tokens])
        return int(self.tokens)

    def recordTransaction(self,change,reward): #used to change tokens and add to memory based on what was bought in the store
        self.tokens = self.tokens - change
        if reward != "a new trail color": #trail colors don't correpond to pictures on HTML pictures, so they are not added to prizes
            prizeFiles = {"a yo-yo":"yoYo.jpeg","a teddy bear":"teddyBear.jpeg","a grand piano":"grandPiano.jpeg"}
            self.prizes.append(prizeFiles[reward])
        self.memory.append([reward,change,self.tokens])
    
    def retrieveMemory(self): #used to show memory for HTML files
        lines = ''''''
        for i in self.memory:
            if len(i) == 4:
                lines = f'''<li>You guessed {i[0]} and the result was {i[1]}. You were given back {i[2]} tokens for a total of {i[3]} tokens.</li>''' + lines
            elif len(i) == 3:
                lines = f'''<li>You bought {i[0]} for {i[1]} tokens. Your balance became {i[2]} tokens.</li>''' + lines
        string = str(lines)
        string = string.strip(',')
        return string
                      
def determine(guess,bet,outcome,user): #decides how well the player did at guessing the point; guess somewhere close, the money betted multiplies; guess far off, it divides
    print("You guessed",guess,".")
    print("The turtle's ending point is",outcome,".")
    distance = guess.distanceBetween(outcome)
    if distance < 100:
        if distance < 50:
            if distance < 25:
                if distance < 10:
                    if distance < 5:
                        if distance < 1:
                            change = bet * 50
                        else:
                            change = bet * 10
                    else:
                        change = bet * 2
                else:
                    change = bet // 2
            else:
                change = bet // 4
        else:
            change = bet // 10
    else:
        change = 0
    print("Your guess was",distance,"units off!")
    print("Your curret total is",user.recordNewTotal(guess,outcome,change),"tokens. \n")

def playGame(t,user): #The turtle is given random lengths and directions until landing on a random point, which is returned to 'placeBet' to be sent to 'determine.'
    t.reset()
    t.pencolor(user.getTrail())
    t.shape(user.getShape())
    for i in range(random.randint(5,10)):
        t.left(random.randint(15,346))
        distance = random.randint(1,50)
        t.forward(distance)
        if t.xcor()<-100 or t.xcor()>100 or t.ycor()<-100 or t.ycor()>100:
            t.backward(2 * distance)
    outX,outY = t.pos()
    return Point(outX,outY)
 
def placeBet(t,user): #This is where the game actually starts. Players guess a point on the coordinate plane and bet a certain amount of their tokens on it.
    x = float(input("Pick an x-value from -100 to 100."))
    y = float(input("Pick a y-value from -100 to 100."))
    bet = float(input("How much are you willing to bet?"))
    if bet <= 0 or bet > user.getTokens():
        print("You can't use that amount! Try again when you have that kind of cash.")
        select(t,user)
    else:
        user.useTokens(bet)
        guess = Point(x,y)
        outcome = playGame(t,user)
        determine(guess,bet,outcome,user)

def editProfile(user): #allows player to change shape or trail color to their liking
    print(user)
    print("Your current shape is",user.getShape(),". Press 1 to edit.")
    print("Your current trail is",str(user.getTrail()),". Press 2 to edit.")
    print("Press 0 to go back to the selection screen.")
    x = int(input("Type a given number."))
    if x != 0:
        if x > 2:
            print("This is not an option. Please type one of the given numbers.")
        else:
            if x == 1:
                shape = str(input(f"What shape would you like? Your current one is {user.getShape()}. You can have a turtle, arrow, circle, square, triangle, or classic."))
                user.changeShape(shape)
            elif x == 2:
                trail = str(input(f"What kind of trail would you like? Your current one is {user.getTrail()}."))
                user.changeTrail(trail)
        editProfile(user)                           

def store(user): #lets each player exchange tokens for randomized trail colors or virtual prizes that can be seen on their HTML file
    storeValues = {1:50,2:250,3:500,4:1000}
    prizes = {1:"a new trail color",2:"a yo-yo",3:"a teddy bear",4:"a grand piano"}
    print(f"Let's see what we got today. Your current balance is {user.getTokens()} tokens.")
    print("For 50 tokens, you can get a code to try out a new trail color. (1)")
    print("For 250 tokens, you can get a virtual yo-yo that will show up on your earnings file! (2)")
    print("For 500 tokens, you can get a virtual teddy bear that will show up on your earnings file! (3)")
    print("For 1000 tokens, you can get a virtual grand piano that will show up on your earnings file! (4)")
    x = int(input("Pick a selected number to purchase. Press 0 to exit the store."))
    if x != 0:
        if storeValues[x] > user.getTokens():
            print("You can't use that amount! Try again when you have that amount of tokens.")
            store(user)
        elif x < 1 or x > 4:
            print("This is not an option. Please type one of the given numbers.")
            store(user)
        else:
            user.recordTransaction(storeValues[x],prizes[x])
            print("Thank you for your purchase! Your current balance is ",user.getTokens(),"tokens.")
            if x == 1:
                user.changeTrail((random.randint(0,255),random.randint(0,255),random.randint(0,255)))
                print("The new trail color will appear the next time you play!")
            elif x == 2 or x == 3 or x == 4:
                print("Your prize will appear on your HTML file")

def HTMLfile(user): #creates an HTML file for players to see their history, prizes, and various settings.
    
    contents = f'''<!DOCTYPE html>
    <html>
    <head>
        <title>The Hub of {user.getName()}</title>
    </head>
    <body>
        <h1 style='font-family:TimesNewRoman;'>{user.getName()}</h1>
        '''
    if type(user.getTrail()) != str:
        textColor = f'''rgb{user.getTrail()}'''
    else:
        textColor = f'''{user.getTrail()}'''
        
    contents += f'''
        <p style='color:{textColor};font-family:CenturyGothic;'>
        You currently have {user.getTokens()} tokens.
        Your current shape is {user.getShape()}.
        Your trail color is {user.getTrail()}.</p>
        '''
    for i in user.getPrizes():
        contents += f'''<img src={i} alt="" width="200" height="200">'''
        
    contents += f'''
    <p style='color:{textColor};font-family:CenturyGothic;'>
    Here's a list of your previous actions (from newest to oldest)!</p>
        <ul>{user.retrieveMemory()}</ul>
    </body>
    </html>'''
    filename = f"{user.getName()}.html"
    output = open(filename,"w")
    output.write(contents)
    output.close()
    webbrowser.open("file:///" + os.path.abspath(filename))

def earningsFile(user): #updates the text file every time the function is called (which is usually before the player is in the position to log out); allows save data to be carried over in future sessions
    W = open(user.getName()+"Profile.txt","w")
    W.write(user.getName()+"/")
    W.write(str(user.getTokens())+"/")
    W.write(user.getShape()+"/")
    W.write(str(user.getTrail())+"/")
    for i in user.getPrizes():   
        W.write(str(i)+"/")
    W.close()

def select(t,user): #main menu of the game
    earningsFile(user)
    choice = int(input('''What would you like to do?
    To place a bet, press 1
    To edit your profile settings, press 2
    To check out the store, press 3
    To create an HTML file of your earnings, press 4
    To sign out, press 0
        Type a number: '''))
    if choice == 0:
        startUp()
    else:
        if choice == 1:
            placeBet(t,user)
        elif choice == 2:
            editProfile(user)
        elif choice == 3:
            store(user)
        elif choice == 4:
            HTMLfile(user)
        else:
            print("This is not an option. Please type one of the given numbers.")
        select(t,user)
    
def startUp(): 
    wn = turtle.Screen() #initalizes screen
    wn.setworldcoordinates(-100,-100,100,100) #sets coordinate plane
    wn.colormode(255) #allows trail colors on rgb scale to be used on screen
    t = turtle.Turtle()
    name = str(input("Hi! What name would you like to go by?"))
    try:
        F = open(name+"Profile.txt","r") #if there's a text file with the given username, the player's data will be carried over
        for line in F:
            stats = line.split('/')
            links = []
            if '(' in stats[3]: #converts the rgb string in the text file to a tuple that can be used to change the turtle's pencolor
                rgb = stats[3]
                rgb = rgb[1:-1]
                rgb = rgb.split(',')
                colors = (int(rgb[0]),int(rgb[1]),int(rgb[2]))
                
            else:
                colors = stats[3] #if the profile's color is a string, it is taken as it is for the turtle's pencolor
            x = -1
            for i in stats: #accumulator used to make a list of the prizes the player has won in the past
                x += 1
                if x > 3:
                    if i != '':
                        links.append(i)
        user = Player(name,int(stats[1]),stats[2],colors,links) #brings over tokens, shape, trail color, and digital prizes
    except FileNotFoundError: 
        user = Player(name,500,"classic","blue",[]) #if there's no text file, player starts with the standard setting
    print(user)
    select(t,user)
    
startUp()
               
        



    

