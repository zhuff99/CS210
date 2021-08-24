import re
import string

#This python file was created to read data from a text file and loop through that data


# This method is used to open a text file and print the information listed

def printsomething():
    # Create our dictionary
    items = {'Product': 'Amount'}

    # Open our file
    x = open('ProjectThreeInput.txt', 'r')

   
    # counts number of times a word is used within a txt file

    for item in x:
        item = item.replace('\n', '')
        if item in items:
            items[item] += 1            # if found ++
        else:
            items.update({item:1})      # if not found add that item

    # close the file
    x.close()

    # Print items and corresponding values
    for key, value in items.items():
        print(key , value)



# Allows the user to search for a specific product

def PrintMe(v):
    value = 0
    items = {}
    x = open('ProjectThreeInput.txt', 'r')      #open our file

    for item in x:              # same loop used in other methods to loop through file
        item = item.replace('\n', '')
        if item in items:
            items[item] += 1
        else:
            items.update({item:1})
    
    #close file reader
    x.close()

    print("You entered: " + v)
    if v in items:
        value = items[v]
    else:
        print("Item not found!")        # if none are found

    print("Number of times found: ")
    return value;



# this file reads from the txt file then creates a new file 'frequency.dat' based off that information

def Histogram():
    items = {}
    x = open('ProjectThreeInput.txt', 'r')

    # loop through file

    for item in x:
        item = item.replace('\n', '')
        if item in items:
            items[item] += 1
        else:
            items.update({item:1})

    x.close()       # close scanner 

    with open("frequency.dat", 'w') as newFile:
        for key, value in items.items():
            newFile.write('%s:%s\n'%(key, value))           # add to python string

    newFile.close()
    


    