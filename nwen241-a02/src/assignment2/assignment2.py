from test.test_typechecks import Integer
from lib2to3.fixer_util import String
import os.path

def add_vectors(vector_1, vector_2):
    """Returns a list object representing the result of adding two vectors together.

       Arguments:
       vector_1 -- list representing first vector
       vector_2 -- list representing second vector

       Error checking:
       Both arguments must be of type list.
       Both vectors must of the same length.
       Only vector elements of type int can be added together.
    """
    addList = []
    
    if not isinstance(vector_1, list) and not isinstance(vector_2, list):
        print("Error: first argument is not a list")
        print("Error: second argument is not a list")
        return None
    if not isinstance(vector_1, list):
        print("Error: first argument is not a list")
        return None
    if not isinstance(vector_2, list):
        print("Error: second argument is not a list")
        return None 
    if len(vector_1) != len(vector_2):
        print("Error: lengths of the two vectors are different")
        return None
    for i in range(0, len(vector_1)):
        if (not isinstance(vector_1[i], int) or not isinstance(vector_2[i], int)):
            print("Error: attempted to add incompatible {} to {}".format(vector_1[i], vector_2[i]))
            return None
        else:
            addList.append(vector_1[i] + vector_2[i])
    return addList

def print_frequency(some_text):
    """Prints a table of letter frequencies within a string. 
       Non-letter characters are ignored.
       Table is sorted alphabetically.
       Letter case is ignored.
       Two blank spaces will separate the letter from its count.

       Returns None in all cases.

       Argument:
       some_text -- string containing the text to be analysed.

       Error checking:
       The argument must be a string object.
    """
    
    # check if we have a string
    if not isinstance(some_text, str):
        print("Error: only accepts strings")
        return
    #check if char is in string
    allLetters = "qwertyuiopasdfghjklzxcvbnm"
    cleanText = []
    for letter in list(some_text):
        if letter.lower() in allLetters:
            cleanText.append(letter.lower())
    # makes a new dictionary with clean entries and sorts it
    d = dict((i,cleanText.count(i)) for i in list(cleanText))
    dSorted = sorted(d.keys())    
    for key in dSorted :
        print("{}  {}".format(key, d[key]))
    
def verbing(some_text):
    """Returns a string where the each word has ing added to it if it is 3 or more characters or length and 
       ly to shorter words.

       Argument:
       some_text -- string containing the text to be analysed.

       Error checking:
       The argument must be a string object.
    """
    
    # check if is a string
    if not isinstance(some_text, str):
        print("Error: only accepts strings")
        return None
    
    # initialise list and return string
    modText = []
    
    for entry in some_text.split():
        if (len(entry) < 3):
            modText.append(entry+"ly")
        else:
            modText.append(entry+"ing")
            
    modStringText = " ".join(modText)
    #print("{}".format(modStringText))
    return modStringText

def verbing_file(file_name):
    """Returns the contents of a given file after applying the verbing function to each
       line in the file.

       Argument:
       file_name -- name of the file (assumed to exist in same directory from where the 
                    python script is executed.

       Error checking:
       The argument must be a string object.
       File must exist and be readable (note no need to distinguish these cases).    
    """
    # check if file 
    if not isinstance(file_name, str):
        print("Error: only accepts strings")
        return None
        
    # check if file exists
    if not os.path.exists(file_name):
        print("Error reading from file {}".format(file_name))
        return None
    
    modText = []
    fin = open(file_name, "r")
    for line in fin:
        verbText = verbing(line)
        modText.append(verbText+"\n")
        
    fin.close()
    modStringText = "".join(modText)
    #print(modStringText, end="") # suppress end of line
    return modStringText
